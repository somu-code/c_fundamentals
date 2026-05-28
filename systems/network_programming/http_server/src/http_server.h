#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#define BUFFER_SIZE 1024
#define PORT 8080

struct http_request {
    char *method;
    char *path;
    char *version;
    struct header {
        char *key;
        char *value;
    } headers[20];
    int header_count;
};

#endif
