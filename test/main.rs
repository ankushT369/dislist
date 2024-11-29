use std::io::{Write, Read};
use std::net::TcpStream;

#[repr(u8)]
#[derive(Copy, Clone)]  // Derive Copy and Clone
pub enum Color {
    Red = 0,
    Green = 1,
    Blue = 2,
}

pub struct DataPacket {
    pub value_i32: i32,
    pub value_u32: u32,
    pub flag: bool,
    pub color: Color,
}

impl DataPacket {
    pub fn serialize(&self) -> Vec<u8> {
        let mut vector = Vec::new();
        vector.extend(&self.value_i32.to_le_bytes());
        vector.extend(&self.value_u32.to_le_bytes());
        vector.push(self.flag as u8);
        vector.push(self.color as u8); // Directly cast the enum to u8
        vector
    }
}

fn main() {
    let packet = DataPacket {
        value_i32: -12345,
        value_u32: 67890,
        flag: true,
        color: Color::Red,
    };

    let serialized_data = packet.serialize();

    let mut stream = TcpStream::connect("127.0.0.1:8080").expect("Could not connect to server");
    stream.write_all(&serialized_data).expect("Failed to send data");

    let mut buffer = [0; 512];
    let bytes_read = stream.read(&mut buffer).expect("Failed to read response");
    println!(
        "Response from server: {}",
        String::from_utf8_lossy(&buffer[..bytes_read])
    );
}

