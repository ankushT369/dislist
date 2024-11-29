use std::io::{Read, Write};
use std::net::TcpStream;
use crate::parser::{Status}; 


/* Structure of the client machine information*/
#[derive(Debug)]
pub struct ClientEventData {
    pub memory_size: i32,       // size of the linkedlist memory
    pub node_count: u32,        // count of the linkedlist node
    pub limit: bool,            // ensures out of bound memory
    pub status: Status,         // return status code
}

impl ClientEventData {
    pub fn serialize(&self) -> Vec<u8> {
        let mut vector = Vec::new();
        vector.extend(&self.memory_size.to_le_bytes());
        vector.extend(&self.node_count.to_le_bytes());
        vector.push(self.limit as u8);
        vector.push(self.status as u8);
        vector
    }
}

pub fn activate_client() -> Option<TcpStream> {
    match TcpStream::connect("127.0.0.1:8080") {
        Ok(stream) => {
            println!("Connection established!");
            Some(stream)
        }
        Err(e) => {
            println!("Failed to connect: {}", e);
            None
        }
    }
}

pub fn get_data(mut stream: TcpStream) -> [u8; 512] {
    let mut buffer = [0; 512];
    stream.read(&mut buffer)
        .expect("Failed to read response");

    buffer
}

pub fn send_data(mut stream: TcpStream, data: &[u8]) {
    stream.write(&data)
        .expect("Failed to send data");
}
