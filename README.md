# Dislist
**Dislist** stands for **Distributed list** or **Distributed linked-list** aims to implement a linked-list using one or more remote or local machines this is a small thought experiment of mine. The main problem I am solving here is to implement a *linked-list* under memory constraint and also make my list as long as possible.

This code is not meant to contribution because its too much unreadable and If you want to contribute then let me help you.

`$ git clone https://github.com/ankushT369/dislist.git`

Clone it if you have Rust and gcc installed otherwise you have to setup by yourself.

![My Photo](images/dislist.png)


```
.
├── Cargo.lock
├── Cargo.toml
├── images
│   └── dislist.png
├── node_manager
│   ├── error_codes.c
│   ├── error_codes.h
│   ├── Makefile
│   ├── node_manager.c
│   └── node_manager.h
├── README.md
└── src
    ├── client.rs
    ├── main.rs
    ├── parser.rs
    └── utility.rs

3 directories, 13 files
```
