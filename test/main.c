#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

// Define the Color enum
typedef enum {
    RED = 0,
    GREEN = 1,
    BLUE = 2
} Color;

// Define the DataPacket struct
typedef struct {
    int32_t value_i32;   // 4 bytes
    uint32_t value_u32;  // 4 bytes
    bool flag;           // 1 byte
    Color color;         // 1 byte (enum fits here)
} DataPacket;

// Deserialize the buffer into a DataPacket
DataPacket deserialize_data_packet(const unsigned char *buffer) {
    DataPacket packet;

    // Deserialize value_i32
    memcpy(&packet.value_i32, buffer, sizeof(int32_t));

    // Deserialize value_u32
    memcpy(&packet.value_u32, buffer + sizeof(int32_t), sizeof(uint32_t));

    // Deserialize flag
    packet.flag = *(buffer + sizeof(int32_t) + sizeof(uint32_t));

    // Deserialize color
    packet.color = *(buffer + sizeof(int32_t) + sizeof(uint32_t) + sizeof(bool));

    return packet;
}

// Print the deserialized DataPacket
void print_data_packet(const DataPacket *packet) {
    printf("DataPacket:\n");
    printf("  value_i32: %d\n", packet->value_i32);
    printf("  value_u32: %u\n", packet->value_u32);
    printf("  flag: %s\n", packet->flag ? "true" : "false");

    printf("  color: ");
    switch (packet->color) {
        case RED: printf("Red\n"); break;
        case GREEN: printf("Green\n"); break;
        case BLUE: printf("Blue\n"); break;
        default: printf("Unknown\n"); break;
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 1) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 8080...\n");

    // Accept a client connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("Client accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    // Buffer to store received data
    unsigned char buffer[512];
    ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        perror("Receive failed");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Received %ld bytes from client.\n", bytes_received);

    // Deserialize the data
    DataPacket packet = deserialize_data_packet(buffer);

    // Print the deserialized data
    print_data_packet(&packet);

    // Send a response back to the client
    const char *response = "Data received successfully!";
    send(client_fd, response, strlen(response), 0);

    // Close connections
    close(client_fd);
    close(server_fd);

    return 0;
}

