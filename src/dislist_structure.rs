pub const MEMORY: usize = 1024 * 1024;

/* LinkList Node Structure */
struct ListNode {
    data: i32,                     // value defines a 32 bit signed integer
    next: Option<Box<ListNode>>,    // next defines a pointer to the next element
}


/* Implementation of constructor */ 
impl ListNode {

    /* 
     * Constructor to create a new node and initialize 
     * its data as signed 32-bit integet 
     */
    fn new_node(data: i32) -> Self {
        ListNode {
            data,
            next: None,
        }
    }

}

