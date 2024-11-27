mod dislist_structure;
mod client;

use dislist_structure::LinkedList;

fn main() {
    println!("{}", dislist_structure::MEMORY);

    let mut list = LinkedList::new();
    list.append(10);
    list.append(20);
    list.append(30);
    list.append(40);

    println!("Linked List:");
    list.display();

    client::activate_client();
}
