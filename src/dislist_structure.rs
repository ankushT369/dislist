pub const MEMORY: usize = 1024 * 1024;

/* LinkList Node Structure */
struct ListNode {
    value: i32,                     // value defines a 32 bit signed integer
    next: Option<Box<ListNode>>,    // next defines a pointer to the next element
}


/* Implementation of constructor */ 


