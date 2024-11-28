mod dislist_structure;
mod client;
mod parser;
mod utility;

use dislist_structure::LinkedList;

fn main() {
    let mut list = LinkedList::new();

    if let Some(stream) = client::activate_client() {
        loop {
            let mut data = client::get_data(stream.try_clone().expect("Failed to clone stream !!"));

            let _data: &str = &utility::array_to_str(data);

            parser::parse(&_data);

            client::send_data(stream.try_clone().expect("Failed to clone stream !!"), &data);
        }
    }
    else {
        println!("Unable to connect to the server.");
    }

    // println!("{}", dislist_structure::MEMORY);

    /*
    list.append(10);
    list.append(20);
    list.append(30);
    list.append(40);

    println!("Linked List:");
    list.display();
    */
}
