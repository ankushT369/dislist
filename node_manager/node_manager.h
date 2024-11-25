#ifndef NODE_MANAGER_H
#define NODE_MANAGER_H

#include <stdint.h>

#define PORT 8080
#define BUFFER_SIZE 1024

/* node information track */
typedef struct node_info_track {

    int32_t memory;

    int32_t nodes_count;

    char* process_name;

} n_info;

typedef struct server_info {

    int sfd;

    int cfd;

} s_info;

typedef struct machine_info {

    char* ip_address;

    char* process_name;

} m_info;

typedef struct machine_list {

    struct machine_info;

} m_list;

/* Active the Node manager server */
void activate_server();


#endif // NODE_MANAGER_H
