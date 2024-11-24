#ifndef NODE_MANAGER_H
#define NODE_MANAGER_H

#include <stdint.h>

#define PORT 7878

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


/* Active the Node manager server */
void activate_server();


#endif // NODE_MANAGER_H
