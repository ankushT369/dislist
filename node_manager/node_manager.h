#ifndef NODE_MANAGER_H
#define NODE_MANAGER_H

#include <stdint.h>
#include <stdbool.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CONNECTIONS 3

int max_fd = 0, activity = -1, sd = -1;

/*
 * n_info stands for node information
 * Description for n_info :
 *
 *
 * s_info stands for server information
 * Description for s_info : 
 *
 *
 * c_ops stands for client operations
 * Description for c_ops : 
 *
 *
 * m_info stands for machine_info
 * Description for m_info :
 *
 *
 * m_list stands for machine_list
 * Description for m_list :
 *
 *
 */

//int client_socket[MAX_CONNECTIONS] = {0};

/*
typedef struct node_info_track {
    int32_t memory_size;
    uint32_t node_count;
    bool limit;
    uint32_t status_code; 

} n_info;
*/
typedef struct __attribute__((__packed__)) {
    int32_t memory_size;    // 4 bytes
    uint32_t node_count;    // 4 bytes
    bool limit;             // 1 byte
    int32_t status_code;    // 4 bytes
} n_info;


typedef struct server_info {
    int sfd;
    int cfd;

} s_info;

typedef struct server_addr {
    struct sockaddr_in addr;
    struct sockaddr_in caddr;
    socklen_t addr_len;
    socklen_t caddr_len;

} s_addr;

typedef enum operations {
    INSERT,
    REMOVE,
    TRAVERSE,
    INVALID,
} c_ops;

typedef struct machine_info {
    char* ip_address;
    bool assigned;
    bool now_node;
    uint8_t client_socket;
    uint8_t nodes_number;
    c_ops cannot_perform;
} m_list;


/* Active the Node manager server */
void activate_server();
void event_loop(s_info, s_addr);
void new_client_connection(s_info, fd_set, s_addr);
void client_server_interaction(fd_set);
void client_message(fd_set);
void connected_client_details();
int check_free_client();
n_info deserialize_node_info(unsigned char*);
void update_list(n_info);
void traverse_clients();

/* For Debugging purposes */
void print(n_info);

#endif // NODE_MANAGER_H
