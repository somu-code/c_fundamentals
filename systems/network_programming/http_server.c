#include <netinet/in.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    const size_t BUFFER_SIZE = 1024;
    const size_t PORT = 8080;
    int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor < 0) {
        perror("Error creating socket");
        return EXIT_FAILURE;
    }
    printf("%d socket created\n", socket_file_descriptor);
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket_file_descriptor, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("bind failed");
        return EXIT_FAILURE;
    }
    printf("bind successful\n");
    if (listen(socket_file_descriptor, SOMAXCONN) < 0) {
        perror("listen failed");
        return EXIT_FAILURE;
    }
    printf("socket is at listening state\n");
    char *request_buffer = malloc(BUFFER_SIZE);
    if (request_buffer == NULL) {
        perror("Failed to allocate buffer");
        return EXIT_FAILURE;
    }
    char *response_buffer = malloc(BUFFER_SIZE);
    if (response_buffer == NULL) {
        perror("Failed to allocate buffer");
        return EXIT_FAILURE;
    }
    while (true) {
        memset(request_buffer, 0, BUFFER_SIZE);
        memset(response_buffer, 0, BUFFER_SIZE);
        printf("waiting for client to connect\n");
        int client_file_discriptor = accept(socket_file_descriptor, NULL, NULL);
        if (client_file_discriptor < 0) {
            perror("accept failed");
        }
        printf("client connected\n");
        if (read(client_file_discriptor, request_buffer, BUFFER_SIZE) < 0) {
            perror("read failed");
        }
        snprintf(response_buffer, BUFFER_SIZE,
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "Content-Length: 1024\r\n"
                 "\r\n"
                 "<!DOCTYPE html>"
                 "<html>"
                 "<head>"
                 "<title>Example page</title>"
                 "</head>"
                 "<body>"
                 "<h1>Hello, world!</h1>"
                 "</body>"
                 "</html>\n");
        if (write(client_file_discriptor, response_buffer,
                  strlen(response_buffer)) < 0) {
            perror("write failed");
        }
        close(client_file_discriptor);
    }
}
