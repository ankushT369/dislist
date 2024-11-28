pub fn array_to_str(buffer: [u8; 512]) -> String {
    match String::from_utf8(buffer.to_vec()) {
        Ok(data) => {
            println!("Received data: {}", data);
            data
        },
        Err(_) => {
            println!("Failed to convert buffer to valid UTF-8.");
            String::new()
        }
    }

}

