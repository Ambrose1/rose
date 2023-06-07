// use lazy_static::lazy_static;
// use std::sync::Once

// struct Singleton {

// }

// impl  Singleton {
// 	// add code here
// 	fn new() -> Self {
// 		Self {

// 		}
// 	}
// }

// lazy_static! {
// 	static ref INSTANCE: Singleton = Singleton::new();
// }

// fn get_instance() -> &'static Singleton {
// 	&INSTANCE
// }

// fn get_safe_instance() -> &'static Singleton {
// 	static mut INSTANCE: *const  Singleton = std::ptr::null();
// 	static ONCE: Once = Once::new()
// 	unsafe {
// 		ONCE.call_once(|| {
// 			INSTANCE = Box::into_raw(Box::new(Singleton::new()))
// 		});
// 		&*INSTANCE
// 	}
// }

use lazy_static::lazy_static;
use std::sync::Once;

struct Singleton {
    // 单例的属性
}

impl Singleton {
    fn new() -> Self {
        // 初始化单例的属性
        Self {
            // ...
        }
    }
}

lazy_static! {
    static ref INSTANCE: Singleton = Singleton::new();
    static ref ONCE: Once = Once::new();
}

fn get_instance() -> &'static Singleton {
    ONCE.call_once(|| {});
    &*INSTANCE
}
