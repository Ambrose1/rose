# GCD 浅析

[toc]

## 一. 概述

GCD，Grand Central Dispatch。GCD是苹果公司开发的一种多线程技术，它提供了一种方便、高效的方法编写并发代码。

设计GCD的主要目标是为了简化多线程编程，GCD把所有要执行的多线程任务都封装成Block的形式添加到队列中来管理并发操作。

本文将从GCD的一般用法、GCD底层实现、在业务中的应用、同类对比四个方面展开。



## 二. GCD的使用

GCD给我们提供了一些简单方便的api方法，我们可以通过调用这些api方法来快速的实现一个多线程操作，同时保证代码的简洁和线程安全。

### 2.1 为什么要用GCD

第一，以一个前端开发的视角来看，我们的工作核心是为用户呈现一个流畅、美观的UI和交互。

流畅，意味着交互不卡顿，任务不会阻塞。美观，意味着主线程绘制UI不会被阻塞，帧缓存及时。因为这些操作都是在主线程上执行的，所以我们的耗时操作，比如网络请求、IO操作(读取文件)、图片下载、播放语音、处理大量数据，需要在非主线程执行，才能保证我们的UI流畅、美观。

第二，从性能的角度上考虑，多线程操作能够更快的处理事务。比如多个网络请求，我们可以开启多线程并发请求，以达到更快的响应的目标；大量图片的下载，使用多线程进行下载，提高页面渲染效率等。

### 2.2 怎么用？

先看下这段代码：

```objective-c
dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    // 在子线程中发送网络请求
    NSURL *url = [NSURL URLWithString:@"http://example.com/api/data"];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    NSURLSessionDataTask *task = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
        // 处理网络请求结果
        if (error) {
            NSLog(@"网络请求失败：%@", error);
        } else {
            NSLog(@"网络请求成功，返回数据：%@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
        }
    }];
    [task resume];
});
```

上述代码使用GCD的api(dispatch_async) 开启一个子线程，去执行一个网络请求。

![图1](/Users/ambrose/Library/Application Support/typora-user-images/image-20230617200702683.png)

​																		图2.2.1 dispathch_async 代码结构

如图2.2.1，dispatch_async 是GCD的一个最常用的api， 表示一个异步的操作。它需要两个参数，第一个参数是一个队列，第二个参数是一个block，block体里面是子线程希望执行的Source Code。

#### 2.2.1 队列

当我们希望去使用GCD执行一个异步任务的时候，需要先创建一个队列作为容器去承载我们要执行的任务，GCD给我们提供了几种可以选择的队列。

| 队列名称                | 特点                                                         |
| :---------------------- | :----------------------------------------------------------- |
| Main Queue              | 在主线程上执行的串行队列，处理UI事件和其他需要在主线程上执行的任务。 |
| Global Queue            | 在后台线程上执行的并发队列，提供了四种优先级：高、默认、低和后台。 |
| Custom Serial Queue     | 用户自定义的串行队列，可以用于在后台线程上执行一系列任务，但是只会使用一个线程。 |
| Custom Concurrent Queue | 用户自定义的并发队列，可以用于在后台线程上执行一系列任务，可以使用多个线程。 |

​                                                                       表2.2.1 GCD队列的种类

如表2.2.1所示，我们可以把我们的任务放在以上四种队列中执行。

**主队列**。在iOS程序中，所有与页面有关的任务都必须在主线程上执行，因此，如果子线程的任务需要更新UI时，必须切换到主线程中执行，在小猪自营司机端听单检测需求开发过程中，需要调用系统api跳转到设置页面打开定位权限等，用户从系统页面返回听单检测页面时需要重新触发听单检测并刷新UI，因为系统api是在子线程执行的，所以此时必须要切换回主线程刷新ui,否则会产生崩溃。

```
NSURL *settingsURL = [NSURL URLWithString:UIApplicationOpenSettingsURLString];
if ([[UIApplication sharedApplication] canOpenURL:settingsURL]) {
    [[UIApplication sharedApplication] openURL:settingsURL options:@{} completionHandler:^(BOOL success) {
        if (success) {
            // 在用户打开网络开关后执行回调处理
            NSLog(@"用户已打开网络开关");
            
            // 在主线程上更新UI
            dispatch_async(dispatch_get_main_queue(), ^{
                // 更新UI的代码
                self.networkStatusLabel.text = @"网络已开启";
            });
        } else {
            // 打开设置页失败，执行错误处理
            NSLog(@"打开设置页失败");
        }
    }];
}
```

**全局队列**也是并发队列，但与自定义的并发队列不同的是，全局队列是系统提供的，它可以方便的将任务分配给系统管理的线程池，从而实现并发执行。同时，使用全局对立也可以简化代码实现，不需要我们自己管理队列。

全局队列一般适用于执行一些比较耗时的任务，比如网络请求、文件读写、图片下载等。

全局队列相比并发队列并不能控制任务的执行顺序，但是可以设置任务的优先级。下面是全局队列可以设置的四种优先级。

```objective-c
DISPATCH_QUEUE_PRIORITY_HIGH：高优先级
DISPATCH_QUEUE_PRIORITY_DEFAULT：默认优先级
DISPATCH_QUEUE_PRIORITY_LOW：低优先级
DISPATCH_QUEUE_PRIORITY_BACKGROUND：后台优先级
```

**并发队列** 是GCD为我们提供的可以自定义操作的队列，我们可以使用dispatch_queue_create函数创建，同时指定队列的名称和类型，队列的类型包括DISPATCH_QUEUE_SERIAL(串行队列) 或DISPATCH_QUEUE_CONCURREN  T(并发队列)。

```objective-c
dispatch_queue_t imageQueue = dispatch_queue_create("com.example.app.image", DISPATCH_QUEUE_CONCURRENT);
```

创建好队列之后，我们需要把任务放到队列里面，我们可以调用dispatch_async（异步）或者dispatch_sync（同步）函数，并指定要执行的任务和队列。

```objective-c
dispatch_async(imageQueue, ^{
    // 执行任务
});
```

我们自定义并发队列可以通过控制并发数量来限制同时执行的任务数。可以使用dispatch_semaphore_t信号量来实现控制并发数量的功能。

例如，限制队列中最多只能同时执行2个任务：

```objective-c
dispatch_semaphore_t semaphore = dispatch_semaphore_create(2);
dispatch_async(imageQueue, ^{
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    // 执行任务
    dispatch_semaphore_signal(semaphore);
});
```

此处使用了信号量dispatch_semaphore_t ， 它也是GCD提供的一种api，用于线程同步。上述方法也可以用于控制任务的执行顺序。

除此之外，我们还可以使用dispatch_barrier_async 控制任务的执行顺序。这个函数可以让我们在并发队列中添加一个栅栏，等待前面的任务执行完之后再执行后面的任务，注意这个函数只能在并发队列中使用。

例如，控制队列中的前3个任务并发执行，第4个任务等待前面的任务执行完成后再执行：

```objective-c
dispatch_async(imageQueue, ^{
    // 执行任务1
});

dispatch_async(imageQueue, ^{
    // 执行任务2
});

dispatch_async(imageQueue, ^{
    // 执行任务3
});

dispatch_barrier_async(imageQueue, ^{
    // 等待前面的任务执行完成后再执行任务4
});

dispatch_async(imageQueue, ^{
    // 执行任务5
});
```

dispatch_group也可以用来等待多个任务执行完之后再执行下一步操作。我们可以使用dispatch_group_async将多个任务添加到group中，然后使用dispatch_group_notify等待任务执行完成后再执行下一步操作。

例如，以下代码演示了如何使用Dispatch Group来控制任务的执行顺序：

```objective-c
dispatch_group_t group = dispatch_group_create();

dispatch_group_async(group, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
    // 执行任务1
});

dispatch_group_async(group, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
    // 执行任务2
});

dispatch_group_notify(group, dispatch_get_main_queue(), ^{
    // 任务1和任务2都执行完成后，在主线程执行下一步操作
});

dispatch_release(group);
```

队列的释放。自定义队列在不再需要时需要手动释放，可以使用dispatch_release函数来释放队列。

```objective-c
dispatch_release(imageQueue);
```

串行队列与并发队列的使用形式类似，需要创建一个串行队列，然后向串行队列里面增加任务，不同的是，串行队列的任务在一个线程上执行，所有任务会顺序执行。

#### 2.2.2 任务的取消

GCD也为我们提供了一个api来取消尚未执行的异步任务，dispatch_block_cancel，需要注意的是，这个函数需要把任务回调作为参数传进去，如下所示：

```objective-c
dispatch_block_t block = dispatch_block_create(0, ^{
    // 执行任务
});
dispatch_async(queue, block);
dispatch_block_cancel(block);
//注意，取消任务后，任务代码可能已经开始执行，但是GCD会在适当的时机（例如任务执行完成后）检查任务是否被取消，并且不会再执行已经取消的任务。
dispatch_release(block);
```

需要注意的是，取消任务会带来一定的性能开销，因此只有在必要的情况下才应该使用。此外，取消任务也可能导致应用程序的状态不一致，因此在使用取消任务时需要仔细考虑应用程序的业务逻辑和用户体验。



## 三. GCD源码浅析

![image](https://www.planttext.com/api/plantuml/png/ZPHDReCm48NtFiKqUzeRL8aIAQhKAgsQNSJ2CQDWyMCqs0jKzUwbG0esDdI7_PxdyxonsDQQapP5pXvqYWM2u7HLPNGZtZ0jTOvmt1_WKnaI27kL8En8f5AZq8QGiOgBZDyGDhcy9hAkk1Rf1huOmEKmBE73eC7OskeBsdj7KgPoR5ZmAbNaE5-UJlR66nQA6dWdh6lZki-oG8hPjttP3AaSBdfE2NdI7NfL8ki-TbeLKi2fGk9QghBk2bmcNJucJRkA8OgUvxsk6-y9h3k7NFvHSanhtTnbk6wR9Rj-PCWxQ1p2ZziudTXw_JuElzfFoAzvXiPcYOSWbknIB74PquyhH9cgBcIghRJoD-bWDuvZrf2ZB_D-7qk8D6ekOrIMgxjlB4Jo-rogtxLyW_x9XhXJrQLDDHzZYsNI_bv_0000)

​                                                                                   图3.1  GCD源码架构

如图3.1 所示，是GCD的源码架构，GCD底层是C语言实现的libdispatch库，阅读源码可以更好的了解多线程的执行方式。

###  3.1 源码阅读顺序

1. 了解GCD的基本概念和术语，包括任务、队列、同步和异步、串行队列和并发队列等。
2. 了解GCD的API，包括dispatch_async、dispatch_sync、dispatch_barrier_async、dispatch_group_async、dispatch_apply和dispatch_after等。
3. 深入了解GCD的核心数据结构，包括dispatch_queue_t、dispatch_object_t等。
4. 了解GCD的架构和实现方式，包括线程池、任务调度和队列管理等。
5. 阅读libdispatch的头文件和源代码，了解其基本结构和实现方式。
6. 从dispatch_queue_t开始，逐步深入到libdispatch的实现细节，包括队列的创建和销毁、任务的提交和执行、线程池的管理和优化等。
7. 阅读libdispatch的内部数据结构和数据流，包括dispatch_object、dispatch_continuation、dispatch_thread等。
8. 了解libdispatch的核心算法和优化策略，包括任务调度算法、队列合并、线程重用、任务优先级等。
9. 阅读libdispatch的单元测试代码，了解其测试方法和覆盖率。
10. 研究libdispatch的性能和调试工具，包括Instruments、DTrace、lldb等，了解如何分析和优化libdispatch的性能问题。



### 3.2 











![img](http://cdn-0.plantuml.com/plantuml/png/VPFTQjmm48Nlvob4xfUyGSbsKvP0Ir8sBw1eLLiWMuf-8ANatIlFU5QgiPgBSCxnqIJ-v7c8IOQK9mkGJB9Qd4-FuXZKQ99MAGSD48gGyr2UtHszjqR9PDny9sGKqllsSJcByQ2kuW-8yjCyV3JHowH6R5nNizOsrOiEHjhxavjL3a7FIVpCEkk8HzzHxXtx8SrCJInEnRxlzSxMlKdRpXmmsIsVSankQiiAaztoyUM9EjARY8NFBORNCMXvZUB5EOjLNyG-XcyVMkM5jIWaalv8wzydqvdFcCKvkEpfxHRLxLtq9Fte0a6BxBhzhp84emEstqXtky-peh6kY6vh-Qf-4xP5xHCxNEGlBIx91JdGp1JZ_wfqoviJG-_8TwUsPHlxp5mEQWM6ijjyDPCEaGQYx3QVxf-nPXny0XGIud3uigmIGFc5XhU60_nssD0riwiNoGbV5dky4pP4dXsYhNfeZAsQtfmjlnvRum3u_rq2tjisenNzDw9Lt8IyScr8EmOB0khmMW22s42ugGOLh4Jgj0L9TO1G60WxHbAY6v8IL0C4fiuXCjKRLpKywFcQ9_iN)









