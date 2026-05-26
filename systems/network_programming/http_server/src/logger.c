#include <stdlib.h>

#include "logger.h"

int init_logger(FILE *log_file, char *log_file_path) {
    log_file = fopen(log_file_path, "a");
    if (log_file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    return 0;
}

int main(void) {
    struct logger_type logger = {0};
    logger.access_log_path = "../logs/access_log";
    logger.error_log_path = "../logs/error_log";
    init_logger(logger.access_log, logger.access_log_path);
    init_logger(logger.error_log, logger.error_log_path);
}
