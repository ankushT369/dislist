use std::io::{self, Read, Write};
use std::net::TcpStream;
use std::str::from_utf8;

fn main() {
    let mut stream = TcpStream::connect("127.0.0.1:8080").expect("Could not connect to server");

    let data = "Node Count = 23, Size = 3.4kB, Node Overloaded = NO";
    stream.write(data.as_bytes()).expect("Failed to send data");

    let mut buffer = [0; 512];
    stream.read(&mut buffer).expect("Failed to read response");

    println!("Response from server: {}", from_utf8(&buffer).unwrap());
}
