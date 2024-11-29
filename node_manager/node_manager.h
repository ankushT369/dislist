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

typedef struct node_info_track {
    int32_t memory;
    uint32_t nodes_count;
    bool limit;
    uint32_t status_code; 

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
    DELETE,
    TRAVERSE,
    INVALID,
} c_ops;

enum ip_addr {
    IP4,
    IP6,
};

typedef struct machine_info {
    char* ip_address;
    enum ip_addr ip_type;
    bool assigned;
    bool now_node;
    uint8_t client_socket;
} m_list;


/* Active the Node manager server */
void activate_server();
void event_loop(s_info, s_addr);
void new_client_connection(s_info, fd_set, s_addr);
void client_server_interaction(fd_set);
void client_message(fd_set);
void connected_client_details();
int check_free_client();


#endif // NODE_MANAGER_H
