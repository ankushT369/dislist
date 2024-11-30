use std::collections::LinkedList;
use crate::client::ClientEventData;
use crate::parser::Instruction;
use crate::parser::Status;

mod client;
mod parser;
mod utility;

pub const MEMORY: usize = 20;

fn main() {
    let mut list = LinkedList::new();

    let mut client_data_instance = ClientEventData {
        memory_size: 0,
        node_count: 0,
        limit: false,
        status: Status::UnknownCommand,
    };

    if let Some(stream) = client::activate_client() {
        loop {
            let data = client::get_data(stream.try_clone().expect("Failed to clone stream !!"));

            let _data: &str = &utility::array_to_str(data);

            match parser::parse(&_data) {
                Ok(info) => {
                    //println!("Parsed instruction: {:?}", info);

                    if info.ins_type == Instruction::INSERT {
                        if info.has_value == true {
                            list.push_back(info.value);
                        }

                    }
                    else if info.ins_type == Instruction::REMOVE {
                        list.pop_back();
                    }
                    else {
                        /* Implementation for TRAVERSE */
                       

                    }
                
                    client_data_instance.memory_size = 4 * list.len() as i32;
                    client_data_instance.node_count = list.len() as u32;

                    if client_data_instance.memory_size < MEMORY.try_into().unwrap() {
                        client_data_instance.limit = false;
                        client_data_instance.status = Status::Success;
                    }
                    else {
                        client_data_instance.limit = true;
                        client_data_instance.status = Status::Success;
                    }

                }
                Err(stat) => {
                    client_data_instance.memory_size =  0;
                    client_data_instance.node_count = 0;

                    if client_data_instance.memory_size < MEMORY.try_into().unwrap() {
                        client_data_instance.limit = false;
                        client_data_instance.status = stat;
                    }
                    else {
                        client_data_instance.limit = true;
                        client_data_instance.status = stat;
                    }
                    //println!("Failed to parse command. Error: {:?}", stat);
                }
            }

            println!("event data : {:?}", client_data_instance);

            let event_data = client_data_instance.serialize();
            client::send_data(
                stream
                .try_clone()
                .expect("Failed to clone stream !!"),
                &event_data,
            );

        }
    }
    else {
        println!("Unable to connect to the server.");
    }

}
