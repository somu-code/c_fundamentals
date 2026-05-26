#include <stdlib.h>

#include "logger.h"

FILE *init_logger(const char *log_file_path) {
    FILE *log_file_pointer = fopen(log_file_path, "a");
    if (log_file_pointer == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return log_file_pointer;
}

int main(void) {
    struct logger_type logger = {0};
    logger.access_log_path = "../logs/access_log";
    logger.error_log_path = "../logs/error_log";
    logger.access_log = init_logger(logger.access_log_path);
    logger.error_log = init_logger(logger.error_log_path);
}
