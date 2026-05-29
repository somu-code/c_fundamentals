#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define TIMESTAMP_BUFFER_SIZE 20

struct logger_type {
    FILE *access_log;
    FILE *error_log;
    const char *access_log_path;
    const char *error_log_path;
};

void setup_logger(void);
void get_timestamp(char timestamp[TIMESTAMP_BUFFER_SIZE], size_t buffer_size);
FILE *init_logger(const char *log_file_path);
void stdout_log_message(const char *message);
void error_log_message(const char *message);

#endif
