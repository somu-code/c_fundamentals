#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

struct logger_type {
    FILE *access_log;
    FILE *error_log;
    const char *access_log_path;
    const char *error_log_path;
};

FILE *init_logger(const char *log_file_path);
void log_message();

#endif
