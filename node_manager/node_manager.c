/*
 * This code managers the nodes of the remote machines
 * it tracks the nodes of the individual machines when
 * its cross the threshold it starts a new process in 
 * new remote machine for continuing the Linked List
 *
 */

#include "node_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void activate_server() {
    s_info server;

    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address);

    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server.sfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server.sfd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("========Server Started Monitoring List=======\n");
    printf("Port : %d\n", PORT);

    if ((server.cfd= accept(server.sfd, (struct sockaddr *)&address, &addr_len)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }


}


int main(int argc, char* argv[]) {
    activate_server(); 
}
