#include <stdlib.h>

#include "logger.h"

struct logger_type logger = {0};

void setup_logger(void) {
    logger.access_log_path = "../logs/access_log";
    logger.error_log_path = "../logs/error_log";

    logger.access_log = init_logger(logger.access_log_path);
    logger.error_log = init_logger(logger.error_log_path);
}

FILE *init_logger(const char *log_file_path) {
    FILE *log_file_pointer = fopen(log_file_path, "a");
    if (log_file_pointer == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return log_file_pointer;
}

void log_message(FILE *log_file, const char *message) {
    fprintf(log_file, "%s\n", message);
}
