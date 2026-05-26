#include <errno.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "http_server.h"

// [timestamp] [Module and severity] [process and thread id] [client address]
// [message]

int main(void) {
    int server_socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_file_descriptor < 0) {
        fprintf(stdout, "hello there");
        return EXIT_FAILURE;
    }
    printf("%d socket created\n", server_socket_file_descriptor);
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_socket_file_descriptor, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("bind failed");
        return EXIT_FAILURE;
    }
    printf("bind successful\n");
    if (listen(server_socket_file_descriptor, SOMAXCONN) < 0) {
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
        int client_file_discriptor =
            accept(server_socket_file_descriptor, NULL, NULL);
        if (client_file_discriptor < 0) {
            perror("accept failed");
            continue;
        }
        printf("client connected\n");
        if (read(client_file_discriptor, request_buffer, BUFFER_SIZE) < 0) {
            perror("read failed");
            continue;
        }
        struct http_request http_request_parsed = {0};
        http_request_parsed.method = strtok(request_buffer, " ");
        http_request_parsed.path = strtok(NULL, " ");
        http_request_parsed.version = strtok(NULL, "\r\n");
        char *line = NULL;
        size_t counter = 0;
        while ((line = strtok(NULL, "\r\n")) != NULL) {
            char *separator = strstr(line, ": ");
            *separator = '\0';
            http_request_parsed.headers[counter].key = line;
            http_request_parsed.headers[counter].value = separator + 2;
            counter++;
        }
        http_request_parsed.header_count = counter - 1;
        if ((strncmp(http_request_parsed.method, "GET", 3) == 0) &&
            (strncmp(http_request_parsed.path, "/", 1) == 0)) {
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
                continue;
            }
        } else if ((strncmp(http_request_parsed.path, "/", 1) == 0) &&
                   (strncmp(http_request_parsed.method, "GET", 3) != 0)) {
            snprintf(response_buffer, BUFFER_SIZE,
                     "HTTP/1.1 405 Method Not Allowed\r\n"
                     "Content-Length: 0\r\n"
                     "Allow: GET\r\n"
                     "\r\n");
            if (write(client_file_discriptor, response_buffer,
                      strlen(response_buffer)) < 0) {
                perror("write failed");
                continue;
            }
        } else {
            snprintf(response_buffer, BUFFER_SIZE,
                     "HTTP/1.1 404 Not Found\r\n"
                     "Content-Type: text/html; charset=UTF-8\r\n"
                     "\r\n");
            if (write(client_file_discriptor, response_buffer,
                      strlen(response_buffer)) < 0) {
                perror("write failed");
                continue;
            }
        }
        if (close(client_file_discriptor) < 0) {
            perror("Failed to close the socket");
        }
    }
}
