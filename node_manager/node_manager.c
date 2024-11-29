/*
 * This code managers the nodes of the remote machines
 * it tracks the nodes of the individual machines when
 * it crosses the threshold it starts a new process in 
 * new remote machine for continuing the Linked List
 *
 */

#include "node_manager.h"
#include "error_codes.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

uint32_t client_count_track = 0;
uint8_t client_connection_flag = 0;
m_list list[MAX_CONNECTIONS];
char log_buffer[1024];
bool control_flag = true;
//enum ip_addr ip;

int check_free_client() {
    for(int i = 0; i < MAX_CONNECTIONS; i++) {
        if((list[i].assigned == false) && (list[i].now_node == false)) {
            return i; 
        }
    }

    //printf("All machines are assigned");
    strcpy(log_buffer, "All machines are assigned");
    return -1;
}

void new_client_connection(s_info server, fd_set readfds, s_addr server_addr) {
        if (FD_ISSET(server.sfd, &readfds)) {
        server.cfd = accept(server.sfd, (struct sockaddr *)&(server_addr.caddr), &(server_addr.caddr_len));
        if (server.cfd < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        FILE *log_file = fopen("client_info.log", "a"); // Open file in append mode
        if (log_file == NULL) {
            perror("Error opening log file");
            return;
        }

        // Write the formatted message to the file
        fprintf(log_file, "New client connected: socket FD %d, IP: %s, PORT: %d\n",
                server.cfd, inet_ntoa(server_addr.caddr.sin_addr), ntohs(server_addr.caddr.sin_port));

        client_connection_flag = 1;
        fclose(log_file);

        // Add new client to the client array
        for (int i = 0; i < MAX_CONNECTIONS; i++) {
            if (list[i].client_socket == 0) {
                list[i].ip_type = IP4;
                list[i].client_socket = server.cfd;
                list[i].ip_address = inet_ntoa(server_addr.caddr.sin_addr);
                list[i].now_node = false;
                list[i].assigned = false;
                
                client_count_track++;
                // printf("Adding client to list at index %d\n", i);
                break;
            }
        }
    }
}

void client_server_interaction(fd_set readfds) {
    char server_message[BUFFER_SIZE];
    int target_client = -1;
    int code = -1;

    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        //printf("in the client_server_interaction\n");
        fgets(server_message, sizeof(server_message), stdin);

        // Check input
        if(sscanf(server_message, "%d", &code) == 1) {
            if(code == 145) {
                connected_client_details();
            }
            else if(code == 245) {
                target_client = check_free_client();

                if (target_client >= 0 && target_client < MAX_CONNECTIONS) {
                    if (list[target_client].client_socket > 0) {
                        printf("Enter message to send to client %d: ", list[target_client].client_socket);
                        fgets(server_message, sizeof(server_message), stdin);
                        server_message[strcspn(server_message, "\n")] = '\0'; // Remove newline
                        send(list[target_client].client_socket, server_message, strlen(server_message), 0);
                        //printf("Message sent to client %d: %s\n", target_client, server_message);
                        sprintf(log_buffer, "Message sent to client index : %d and socket : %d", target_client, 
                                list[target_client].client_socket);
                    } else {
                        strcpy(log_buffer, "Client is not connected.");
                        //printf("Client %d is not connected.\n", target_client);
                    }
                }
                else {
                    strcpy(log_buffer, "No valid number selected");
                    //printf("No valid client selected.\n");
                }
            }
            else if(code == 345) {
                control_flag = false;
                //exit(EXIT_SUCCESS);
            }
            else {
                strcpy(log_buffer, "No valid number selected");
                //printf("No valid number selected.\n");
            }
            /*
            if (sscanf(server_message, "%d", &code) == 1 && target_client >= 0 && target_client < MAX_CONNECTIONS) {
                if (client_socket[target_client] > 0) {
                    printf("Enter message to send to client %d: ", target_client);
                    fgets(server_message, sizeof(server_message), stdin);
                    server_message[strcspn(server_message, "\n")] = '\0'; // Remove newline
                    send(client_socket[target_client], server_message, strlen(server_message), 0);
                    printf("Message sent to client %d: %s\n", target_client, server_message);
                } else {
                    printf("Client %d is not connected.\n", target_client);
                }
            } else {

            }
            */
        }
    }
}


void client_message(fd_set readfds) {
    char buffer[BUFFER_SIZE];
    FILE *log_file = fopen("client_info.log", "a"); // Open file in append mode
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        //sd = client_socket[i];

        sd = list[i].client_socket;

        if (FD_ISSET(sd, &readfds)) {
            if(sd != 0) {
                int bytes_read = read(sd, buffer, sizeof(buffer));
                if (bytes_read == 0) {
                    // Client disconnected
                    client_count_track--;
                    // printf("Client disconnected: socket FD %d\n", sd);
                    fprintf(log_file, "Client disconnected: socket FD %d\n", sd);

                    client_connection_flag = 1;

                    fclose(log_file);
                    close(sd);
                    list[i].client_socket = 0;
                    break;
                } 
                else {
                    // Print message from client
                    buffer[bytes_read] = '\0'; // Null-terminate the string
                    //handle_response_code(200, log_buffer);
                    //printf("Message from client %d: %s", sd, buffer);
                    break;
                }
            }
        }
    }

}

void connected_client_details() {
    uint8_t input = 1;
    system("clear");

    while(input) {
        if(client_connection_flag == 0) {
            // printf("No Client Connected..\n");
        }
        else {
            FILE *file = fopen("client_info.log", "r"); // Open file in read mode
            if (file == NULL) {
                perror("Error opening file");
                return;
            }

            char line[256]; // Buffer to store each line of the file
            while (fgets(line, sizeof(line), file) != NULL) {
                printf("%s", line); // Print each line to the console
            }

            fclose(file); // Close the file
        }

        printf("[0] Back to previous page\n");
        scanf("%hhd", &input);
    }

}

void event_loop(s_info server, s_addr server_addr) {
    fd_set readfds;

    while(control_flag) {
        system("clear");
        printf("========Server Started Monitoring Linked List=======\n");
        /*
        printf("Server hosted in : socket FD%d\n", PORT);
        socket FD %d, IP: %s, PORT: %d\n
        */
        printf("Server Connected : socket FD %d, IP: %s, PORT: %d\n",
               server.sfd, inet_ntoa(server_addr.addr.sin_addr), ntohs(server_addr.addr.sin_port));

        if(client_count_track == 0) {
            printf("\033[1;31m");  // Set the color to red
            printf("● ");  // Print the red circle
            printf("\033[0m");
        }
        else {
            printf("\033[1;32m");  // Set the color to green
            printf("● ");  // Print the green circle
            printf("\033[0m");
        }
        printf("Client Connected : %d\n", client_count_track);
        printf("Log : %s\n", log_buffer);
        printf("[145] Display Connected info.\n");
        printf("[245] Opeation on linkedlist.\n");
        printf("[345] Exit or Quit Server\n");

        FD_ZERO(&readfds);
        // Add the server socket to the set
        FD_SET(server.sfd, &readfds);
        max_fd = server.sfd;

        // Add client sockets to the set
        for (int i = 0; i < MAX_CONNECTIONS; i++) {
            sd = list[i].client_socket;
            if (sd > 0) {
                FD_SET(sd, &readfds);
            }
            if (sd > max_fd) {
                max_fd = sd;
            }
        }

        // Add stdin (server input) to the set
        FD_SET(STDIN_FILENO, &readfds);
        if (STDIN_FILENO > max_fd) {
            max_fd = STDIN_FILENO;
        }

        // Wait for activity on one of the sockets
        activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR)) {
            perror("Select error");
        }

        new_client_connection(server, readfds, server_addr);

        client_server_interaction(readfds);

        client_message(readfds);
    }

}

void activate_server() {
    s_info server;
    s_addr server_addr;
    int opt = 1;

    /*
    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address);
    */

    if ((server.sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    
    if (setsockopt(server.sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt failed");
        close(server.sfd);
        exit(EXIT_FAILURE);
    }
    
    server_addr.addr.sin_family = AF_INET;
    server_addr.addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.addr.sin_port = htons(PORT);

    if (bind(server.sfd, (struct sockaddr *)&(server_addr.addr), sizeof(server_addr.addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server.sfd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }


    /* Event-loop starts */
    event_loop(server, server_addr);

    printf("Quiting Server...\n");

    // close(server.cfd);
    close(server.sfd);
}


int main(int argc, char* argv[]) {
    activate_server(); 
    return 0;
}
