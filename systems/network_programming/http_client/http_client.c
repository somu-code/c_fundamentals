/*
Stuff that curl do
1. Chunked response.
2. Redirects.
3. TLS.
4. Presistent connections.
5. State machines.
6. A custom async event loop. (lib/multi.c)
7. Platform abstraction layer.
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Provide a valid url\n");
		return EXIT_FAILURE;
	}
	const size_t BUFFER_SIZE = 1024;
	const uint16_t PORT = 80;
	const char *http_request = "GET / HTTP/1.1\r\n"
				   "Host: example.com\r\n"
				   "User-Agent: my_custom_client\r\n"
				   "Accept: */*\r\n"
				   "\r\n";
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		perror("Error creating socket");
		return EXIT_FAILURE;
	}
	struct sockaddr_in server_addr = { 0 };
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	int network_address_conversion_status =
		inet_pton(AF_INET, "104.20.23.154", &server_addr.sin_addr);
	if (network_address_conversion_status < 0) {
		close(socket_fd);
		perror("Failed to convert netwrok address");
		return EXIT_FAILURE;
	}
	if (network_address_conversion_status < 1) {
		fprintf(stderr,
			"inet_pton: src does not contain a character string representhing a valid network address in the specified address family\n");
		close(socket_fd);
		return EXIT_FAILURE;
	}
	if (connect(socket_fd, (struct sockaddr *)&server_addr,
		    sizeof(server_addr)) < 0) {
		perror("Failed to connect");
		close(socket_fd);
		return EXIT_FAILURE;
	}
	if (write(socket_fd, http_request, strlen(http_request)) < 0) {
		perror("Failed to write");
		close(socket_fd);
		return EXIT_FAILURE;
	}
	char *http_response = malloc(BUFFER_SIZE);
	if (http_response == NULL) {
		perror("Failed to allocte buffer");
		close(socket_fd);
		return EXIT_FAILURE;
	}
	ssize_t bytes_read = read(socket_fd, http_response, BUFFER_SIZE);
	if (bytes_read < 0) {
		perror("Failed to read");
		close(socket_fd);
		free(http_response);
		return EXIT_FAILURE;
	}
	printf("%s", http_response);
	if (close(socket_fd) < 0) {
		perror("Failed to close the socket");
		free(http_response);
		return EXIT_FAILURE;
	}
	free(http_response);
}
