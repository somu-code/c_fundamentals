#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

struct logger_type {
    FILE *access_log;
    FILE *error_log;
    char *access_log_path;
    char *error_log_path;
};

int init_logger(FILE *log_file, char *log_file_path);
void log_message();

#endif
