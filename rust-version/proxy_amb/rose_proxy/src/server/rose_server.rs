use std::net::SocketAddr;
use tokio::net::TcpListener;
use tokio::net::TcpStream;
use tokio::io;
use tokio::io::{AsyncReadExt, AsyncWriteExt};

pub struct RoseServer {

}

impl RoseServer {

    #[tokio::main]
    pub async fn start_up_server() -> Result<(), Box<dyn std::error::Error>> {
        let addr = "127.0.0.1:8000".parse::<SocketAddr>().unwrap();
        let listener = TcpListener::bind(&addr).await?;

        println!("Proxy server listening on {}", addr);

        loop {
            let (client_socket, client_addr) = listener.accept().await?;
            tokio::spawn(Self::handle_client(client_socket, client_addr));
        }

        
    }

    async fn handle_client(mut client_socket: TcpStream, client_addr: SocketAddr) -> io::Result<()> {
        println!("Accepted client connection from {}", client_addr);
    
        let mut server_socket = TcpStream::connect("www.baidu.com:80").await?;
        println!("Connected to server");
    
        // 从客户端读取数据，并转发给服务器
        let (mut client_reader, mut client_writer) = client_socket.split();
        let (mut server_reader, mut server_writer) = server_socket.split();

        let mut buffer = vec![0; 10024]; // 创建一个缓冲区来存储读取的数据，大小为 1024 字节

        // 从客户端读取数据，并存储在缓冲区中
        let bytes_read = client_reader.read(&mut buffer).await?;

        // 如果 buffer 中的数据是有效的 UTF-8 编码，则可以直接将其转换为 str 类型
        if let Ok(utf8_str) = std::str::from_utf8(&mut buffer) {
            println!("UTF-8 str: {}", utf8_str);
        } else {
            println!("Buffer contains invalid UTF-8 data");
        }

        // 从服务器读取数据，并存储在缓冲区中
        // let bytes_read = server_reader.read(&mut buffer).await?;
        // println!("Read {} bytes from server: {:?}", bytes_read, buffer);

    
        // 将客户端发送的数据写入目标服务器
        // server_writer.write_all(&buffer[..bytes_read]).await?;

        server_socket.write_all(&buffer[..bytes_read]).await?;
        println!("Sent data to server");
    
        // 从目标服务器读取响应数据
        let mut server_response = Vec::new();
        server_socket.read_to_end(&mut server_response).await?;
        println!("Received {} bytes from server", server_response.len());
    
        // 将服务器响应写入到客户端
        client_socket.write_all(&server_response).await?;
        println!("Sent response to client");
     
        // let client_to_server_result = io::copy(&mut client_reader, &mut server_writer).await;
        // let server_to_client_result = io::copy(&mut server_reader, &mut client_writer).await;
    
        // println!("执行到 copy 后面");

        // match client_to_server_result {
        //     Ok(bytes) => println!("Copied {} bytes from client to server", bytes),
        //     Err(err) => eprintln!("Error copying from client to server: {}", err),
        // }
    
        // match server_to_client_result {
        //     Ok(bytes) => println!("Copied {} bytes from server to client", bytes),
        //     Err(err) => eprintln!("Error copying from server to client: {}", err),
        // }
    
        println!("执行到 match 后面");
        Ok(())
    }
}