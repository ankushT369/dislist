pub const MEMORY: usize = 1024 * 1024;

/* LinkList Node Structure */
pub struct ListNode {
    data: i32,                     // value defines a 32 bit signed integer
    next: Option<Box<ListNode>>,    // next defines a pointer to the next element
}

/* Implementation of constructor */ 
impl ListNode {
     
    // Constructor to create a new node
    pub fn new_node(data: i32) -> Self {
        ListNode { data, next: None }
    }

}

pub struct LinkedList {
    pub head: Option<Box<ListNode>>,
    pub tail: Option<*mut ListNode>,
}

impl LinkedList {
    
    //Constructor to create an empty linked list
    pub fn new() -> Self {
        LinkedList { head: None, tail: None }
    }

    // Append a new node to the end of the list
    pub fn append(&mut self, data: i32) {
        let new_node = Box::new(ListNode::new_node(data));

        let new_node_ptr: *mut ListNode = Box::into_raw(new_node);

        unsafe {
            if let Some(tail) = self.tail {

                (*tail).next = Some(Box::from_raw(new_node_ptr));
            } else {

                self.head = Some(Box::from_raw(new_node_ptr));
            }

            self.tail = Some(new_node_ptr);
        }
    }

    // Display the linked list
    pub fn display(&self) {
        let mut current = &self.head;
        while let Some(node) = current {
            print!("{} -> ", node.data);
            current = &node.next;
        }
        println!("None");
    }

}

