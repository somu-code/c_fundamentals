#include <arpa/inet.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    const uint16_t PORT = 8080;
    const char *http_request =
        "GET / HTTP/1.1\r\n"
        "HOST: 127.0.0.1:8080\r\n"
        "User-Agent: my_custom_client\r\n"
        "Accept: */*\r\n";
    int socket_file_discriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_discriptor < 0) {
        perror("Error creating socket");
        return EXIT_FAILURE;
    }
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    if (connect(socket_file_discriptor, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("Failed to connect");
        return EXIT_FAILURE;
    }
    if (write(socket_file_discriptor, http_request, strlen(http_request)) < 0) {
        perror("Failed to write");
        return EXIT_FAILURE;
    }
    if (close(socket_file_discriptor) < 0) {
        perror("Failed to close the socket");
        return EXIT_FAILURE;
    }
}
