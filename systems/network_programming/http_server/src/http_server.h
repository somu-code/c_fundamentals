#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <stddef.h>
#include <stdint.h>

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
const size_t BUFFER_SIZE = 1024;
const uint16_t PORT = 8080;

#endif
