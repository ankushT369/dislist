use std::io::{Read, Write};
use std::net::TcpStream;

/* Structure of the client machine information*/
struct ClientEventData {
    memory_size: i32,       // size of the linkedlist memory
    node_count: u32,        // count of the linkedlist node
    limit: bool,            // ensures out of bound memory
}

pub fn activate_client() {
    let mut client_stream = match TcpStream::connect("127.0.0.1:8080") {
        Ok(stream) => {
            println!("Connection established!");
            stream // Return the stream to the client_stream variable
        }
        Err(e) => {
            println!("Failed to connect: {}", e);
            return; // Exit the function if the connection fails
        }
    };

    //let data = b"Hello!!";

    client_stream.write(data)
        .expect("Failed to send data");

    let mut buffer = [0; 512];
    client_stream.read(&mut buffer)
        .expect("Failed to read response");

}
