mod server;
use server::{rose_server};


fn main() {
    println!("Hello, world!");

    if let Err(e) = rose_server::RoseServer::start_up_server() {
        eprintln!("Error : {}", e);
    }
}
