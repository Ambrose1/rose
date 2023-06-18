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

如图3.1 所示，是GCD的源码架构，GCD底层是C语言实现的libdispatch库，阅读源码可以更好的了解多线程的执行方式。本文将节选dispatch_queue_t 的创建和dispatch_source 两部分源码进行分析讲解。

###  3.1 源码阅读思路和注意点

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

在阅读libdispatch源码时，需要注意以下几点：

- 理解每个函数的作用和使用方法，包括参数和返回值等。
- 注意源码中的注释和文档，了解函数的实现原理和设计思路。
- 熟悉C语言和多线程编程的基本知识，包括指针、内存管理、锁和条件变量等。
- 熟悉UNIX系统编程的基本知识，包括进程、线程、信号和文件等。
- 注意代码的风格和规范，包括缩进、命名、注释和错误处理等。

### 3.2 dispatch_queue_t

​         队列是GCD库的核心，GCD的队列是通过libdispatch创建的，在queue.c文件中，同时dispatch_async 和dispatch_sync 都在queue.c文件内。

#### 3.2.1 队列和线程的关系

在 GCD 中，队列和线程是密切相关的，可以说队列是线程的管理者，而线程则是任务的执行者。

在串行队列中，GCD 会为每个队列创建一个单独的线程，该线程会按照队列中任务的顺序依次执行任务。每个任务执行完毕后，线程会等待下一个任务的到来。由于串行队列中只有一个线程，因此任务是依次执行的，不会出现资源竞争的问题。

在并发队列中，GCD 会为每个队列创建一个线程池，线程池中的线程可以同时执行多个任务。GCD 会根据系统的负载情况动态地增加或减少线程的数量，以保持系统的性能和稳定性。由于并发队列中的任务可以并发执行，因此需要考虑资源竞争的问题，开发者需要合理地控制任务的并发度，以避免出现线程安全问题。

在 GCD 中，线程池的创建和销毁以及线程的管理都是由 GCD 内部完成的，开发者只需要将任务提交到队列中即可。GCD 会自动将任务分配到对应的队列中，并选择合适的线程来执行任务，从而实现任务的并发执行和线程的高效利用。

总之，队列是 GCD 管理任务的单位，线程是 GCD 执行任务的单位。通过合理地创建和使用队列，开发者可以实现任务的并发执行和线程的高效利用，从而提高应用程序的性能和响应速度。

![](https://upload-images.jianshu.io/upload_images/1966287-8d380e40b868382b.image?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

​                                                                          图3.2 GCD线程和队列的关系

#### 3.2.2 队列的结构体

**dispatch_queue_s**是队列的结构体，libdispatch源码中使用了一些宏，下面使用对应结构替换对应的宏。

```c
struct dispatch_queue_s {
    // 第一部分：DISPATCH_STRUCT_HEADER(dispatch_queue_s, dispatch_queue_vtable_s)
    const struct dispatch_queue_vtable_s *do_vtable; // 该类型的结构体包含了对dispatch_queue_s的操作函数
    struct dispatch_queue_s *volatile do_next; //链表的next volatile保证线程安全
    unsigned int do_ref_cnt; // 引用计数
    unsigned int do_xref_cnt; // 外部引用计数
    unsigned int do_suspend_cnt; // 暂停标志，比如延时处理中，在任务到时后，计时器处理将会将该标志位修改，然后唤醒队列调度
    struct dispatch_queue_s *do_targetq; // 目标队列，GCD允许我们将一个队列放在另一个队列里执行任务
    void *do_ctxt; // 上下文，用来存储线程池相关数据，比如用于线程挂起和唤醒的信号量、线程池尺寸等
    void *do_finalizer;
    
    // 第二部分：DISPATCH_QUEUE_HEADER
    uint32_t volatile dq_running; // 队列运行的任务数量
    uint32_t dq_width; // 最大并发数：主队列/串行队列的最大并发数为1
    struct dispatch_object_s *volatile dq_items_tail; // 队列尾结点
    struct dispatch_object_s *volatile dq_items_head; // 队列头结点
    unsigned long dq_serialnum; // 队列序列号
    dispatch_queue_t dq_specific_q; // specific队列
    
    char dq_label[DISPATCH_QUEUE_MIN_LABEL_SIZE]; // 队列名，队列名要少于64个字符    
    char _dq_pad[DISPATCH_QUEUE_CACHELINE_PAD]; // for static queues only
};
```

如上述代码所示，GCD的队列是一个线程安全的链表实现。结构体中包含了对应的操作函数、引用计数、状态标志、上下文、并发数，队列名等许多属性。其中操作函数结构体中，声明了一些函数用于操作dispatch_queue_s结构体，如下所示：

```c
// dispatch_queue_vtable_s结构体，声明了一些函数用于操作dispatch_queue_s结构体
struct dispatch_queue_vtable_s {
    // DISPATCH_VTABLE_HEADER(dispatch_queue_s);
    unsigned long const do_type;
    const char *const do_kind;
    size_t (*const do_debug)(struct dispatch_queue_s *, char *, size_t);
    // 唤醒队列的方法，全局队列和主队列此项为NULL
    struct dispatch_queue_s *(*const do_invoke)(struct dispatch_queue_s); 
    // 用于检测传入对象中的一些值是否满足条件
    bool (*const do_probe)(struct dispatch_queue_s *);
    // 销毁队列的方法，通常内部会调用这个对象的finalizer函数
    void (*const do_dispose)(struct dispatch_queue_s *)
};
```

在queue.c代码中，定义了三个关于`dispatch_queue_vtable_s`的静态常量，分别是：

```
// 用于主队列和自定义队列
const struct dispatch_queue_vtable_s _dispatch_queue_vtable = {
    .do_type = DISPATCH_QUEUE_TYPE,
    .do_kind = "queue",
    .do_dispose = _dispatch_queue_dispose,
    .do_invoke = NULL,
    .do_probe = (void *)dummy_function_r0,
    .do_debug = dispatch_queue_debug,
};

// 用于全局队列
static const struct dispatch_queue_vtable_s _dispatch_queue_root_vtable = {
    .do_type = DISPATCH_QUEUE_GLOBAL_TYPE,
    .do_kind = "global-queue",
    .do_debug = dispatch_queue_debug,
    .do_probe = _dispatch_queue_wakeup_global,
};

// 用于管理队列
static const struct dispatch_queue_vtable_s _dispatch_queue_mgr_vtable = {
    .do_type = DISPATCH_QUEUE_MGR_TYPE,
    .do_kind = "mgr-queue",
    .do_invoke = _dispatch_mgr_thread,
    .do_debug = dispatch_queue_debug,
    .do_probe = _dispatch_mgr_wakeup,
};
```

#### 3.2.3 队列的创建过程

![](https://www.planttext.com/api/plantuml/png/bL91SiCW3Bpx5VH6P_o2zfAVC39MRJN242II-lV5iTj9flQXDv1sLxk8aoXaBO6R5nqne0cGfMdkrUQj9qcWVdINWWMTpmYAbg53RWsevjVt0v2xaOwkgWoeZuJMhBKTuj9s0SuRznB5UGOH-tjgJKO6fIkwb2bcqdb7Hr0VoKkjDV_Ks4BG17w17aO6ZO5yTVr50PXd1qp3XBrBccrQmNLox3xHQsroz7QzjEQ3OP0djI77aXp8F7bxFrVVg_sk4iyxM9mKyuhTIP6AZFPGOVDETTWLkE2EF2FKy7_bDsgFnzGRaFw4K0eOo_FEwnOG1BVNg2tHc9hcX5DVV-Ct)

```
== 方法解释 ==
dispatch_queue_create(label, attr)：创建并发队列，其中 label 参数是队列的标签，用于调试和区分不同的队列；attr 参数是队列的属性，用于设置队列的服务质量等级等参数。
dispatch_queue_create_with_target(label, attr, target)：创建并发队列，并指定队列的目标派发队列，以便 GCD 在执行任务时可以更加高效地利用系统资源。
dispatch_queue_attr_make_with_qos_class(qos_class, relative_priority)：创建一个包含指定服务质量等级和相对优先级的队列属性对象，用于设置队列的服务质量等级等参数。
dispatch_queue_set_qos_class(queue, qos_class, relative_priority)：设置队列的服务质量等级和相对优先级。
dispatch_queue_create_inactive(label, attr)：创建一个新的未激活的并发队列，其中 label 参数是队列的标签，用于调试和区分不同的队列；attr 参数是队列的属性，用于设置队列的服务质量等级等参数。
dispatch_atomic_maximally_aligned_ptr(ptr)：返回最大对齐的指针地址，用于确保指针的对齐方式和硬件平台的要求一致。
os_object_alloc(object, flags)：分配一个新的对象，用于存储队列、任务等数据结构。
dispatch_group_async(group, queue, block)：将一个块添加到指定分组和队列中，其中 group 参数是分组对象，用于跟踪任务的执行状态；queue 参数是要添加任务的队列对象；block 参数是要执行的块对象。
dispatch_group_enter(group)：告诉分组对象该任务已经开始执行，以便分组对象可以跟踪任务的执行状态。
dispatch_queue_push(queue, block)：将一个块添加到指定队列中，其中 queue 参数是要添加任务的队列对象；block 参数是要执行的块对象。
dispatch_atomic_inc(value)：原子性地增加指定计数器的值，以确保计数器的值正确无误。
dispatch_group_leave(group)：告诉分组对象该任务已经执行完成，以便分组对象可以跟踪任务的执行状态。
dispatch_atomic_dec(value)：原子性地减少指定计数器的值，以确保计数器的值正确无误。
dispatch_group_wait(group, timeout)：等待指定分组中的任务执行完成，直到所有任务执行完成或超时。
dispatch_release(object)：释放指定对象的引用计数，以便系统可以回收该对象的内存空间，防止内存泄漏。
```





## 四. 总结&应用

![img](http://cdn-0.plantuml.com/plantuml/png/VPFTQjmm48Nlvob4xfUyGSbsKvP0Ir8sBw1eLLiWMuf-8ANatIlFU5QgiPgBSCxnqIJ-v7c8IOQK9mkGJB9Qd4-FuXZKQ99MAGSD48gGyr2UtHszjqR9PDny9sGKqllsSJcByQ2kuW-8yjCyV3JHowH6R5nNizOsrOiEHjhxavjL3a7FIVpCEkk8HzzHxXtx8SrCJInEnRxlzSxMlKdRpXmmsIsVSankQiiAaztoyUM9EjARY8NFBORNCMXvZUB5EOjLNyG-XcyVMkM5jIWaalv8wzydqvdFcCKvkEpfxHRLxLtq9Fte0a6BxBhzhp84emEstqXtky-peh6kY6vh-Qf-4xP5xHCxNEGlBIx91JdGp1JZ_wfqoviJG-_8TwUsPHlxp5mEQWM6ijjyDPCEaGQYx3QVxf-nPXny0XGIud3uigmIGFc5XhU60_nssD0riwiNoGbV5dky4pP4dXsYhNfeZAsQtfmjlnvRum3u_rq2tjisenNzDw9Lt8IyScr8EmOB0khmMW22s42ugGOLh4Jgj0L9TO1G60WxHbAY6v8IL0C4fiuXCjKRLpKywFcQ9_iN)

​                                                                              图4.1 GCD的整体架构图

如图4.1所示，GCD的架构图中核心就是dispatch里面的四种队列以及对外的api，我们使用GCD的多线程方式就是直接将要执行的任务放在这几个队列里面。





