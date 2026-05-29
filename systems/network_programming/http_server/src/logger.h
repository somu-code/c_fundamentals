#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define TIMESTAMP_BUFFER_SIZE 26

struct logger_type {
    FILE *access_log;
    FILE *error_log;
    const char *access_log_path;
    const char *error_log_path;
};

int setup_logger();
void error_log_message(const char *message);
void access_log_message(const char *message);
void close_logger(void);

#endif
