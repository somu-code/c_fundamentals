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

static void get_timestamp(char timestamp[TIMESTAMP_BUFFER_SIZE],
                          size_t buffer_size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(timestamp, buffer_size, "%Y-%m-%d %H:%M:%S", tm_info);
}

static FILE *open_logger(const char *log_file_path) {
    FILE *log_file = fopen(log_file_path, "a");
    if (log_file == NULL) {
        fprintf(stderr, "Failed to open log file %s: %s\n", log_file_path,
                strerror(errno));
        return NULL;
    }
    fprintf(stdout, "Log file %s opened for writing\n", log_file_path);
    return log_file;
}

int setup_logger() {
    logger.access_log_path = "../logs/access_log";
    logger.error_log_path = "../logs/error_log";
    logger.access_log = open_logger(logger.access_log_path);
    if (logger.access_log == NULL) {
        return EXIT_FAILURE;
    }
    logger.error_log = open_logger(logger.error_log_path);
    if (logger.error_log == NULL) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void error_log_message(const char *message) {
    char error_timestamp_buffer[TIMESTAMP_BUFFER_SIZE];
    get_timestamp(error_timestamp_buffer, sizeof(error_timestamp_buffer));
    fprintf(logger.error_log, "[%s] [pid %d] %s\n", error_timestamp_buffer,
            getpid(), message);
    fflush(logger.error_log);
}

void access_log_message(const char *message) {
    char access_timestamp_buffer[TIMESTAMP_BUFFER_SIZE];
    get_timestamp(access_timestamp_buffer, sizeof(access_timestamp_buffer));
    fprintf(logger.access_log, "[%s] %s\n", access_timestamp_buffer, message);
    fflush(logger.access_log);
}

void close_logger(void) {
    fclose(logger.access_log);
    fclose(logger.error_log);
}
