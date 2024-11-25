/*
 * This code managers the nodes of the remote machines
 * it tracks the nodes of the individual machines when
 * it crosses the threshold it starts a new process in 
 * new remote machine for continuing the Linked List
 *
 */

#include "node_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, sizeof(buffer));

    //if (strncmp(buffer, "INSERT", 6) == 0) {
        printf("Received data: %s\n", buffer); 
    //}

    const char *response = "Data received, insertion successful.";
    write(client_socket, response, strlen(response));
}

void activate_server() {
    s_info server;

    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address);

    if ((server.sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    
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

    printf("========Server Started Monitoring Linked List=======\n");
    printf("Port : %d\n", PORT);

    if ((server.cfd= accept(server.sfd, (struct sockaddr *)&address, &addr_len)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    handle_client(server.cfd);
    close(server.cfd);
    close(server.sfd);
}


int main(int argc, char* argv[]) {
    activate_server(); 
    return 0;
}
