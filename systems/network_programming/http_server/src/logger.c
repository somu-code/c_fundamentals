// example access log
// 127.0.0.1 - - [28/May/2026:14:35:22 +0530] "GET /index.html HTTP/1.1" 200 512

// example error log
// [Thu May 28 14:40:01.123456 2026] [core:error] [pid 1234] File does not
// exist: /var/www/favicon.ico

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "logger.h"

struct logger_type logger = {0};

void setup_logger(void) {
    logger.access_log_path = "../logs/access_log";
    logger.error_log_path = "../logs/error_log";

    logger.access_log = init_logger(logger.access_log_path);
    logger.error_log = init_logger(logger.error_log_path);
}

void get_timestamp(char timestamp[TIMESTAMP_BUFFER_SIZE], size_t buffer_size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(timestamp, buffer_size, "%Y-%m-%d %H:%M:%S", tm_info);
}

FILE *init_logger(const char *log_file_path) {
    FILE *log_file_pointer = fopen(log_file_path, "a");
    if (log_file_pointer == NULL) {
        log_message(stdout, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return log_file_pointer;
}

void log_message(FILE *log_file, const char *message) {
    char timestamp[TIMESTAMP_BUFFER_SIZE];
    get_timestamp(timestamp, sizeof(timestamp));
    fprintf(log_file, "[%s] [pid %d] %s\n", timestamp, getpid(), message);
}
