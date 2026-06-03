/*
The three things in interpreter
1. The tape - an array of cells(memory)
2. The data pointer - tracks the current cell, where i am at
3. The instruction pointer - tracks which command currently executing
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc == 2) {
        FILE *input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            perror("Failed to open file");
            return EXIT_FAILURE;
        }
        fseek(input_file, 0, SEEK_END);
        long input_file_size = ftell(input_file);
        fseek(input_file, 0, SEEK_SET);
        char input_array[input_file_size];
        int input_array_index = 0;
        int c;
        while ((c = fgetc(input_file)) != EOF) {
            input_array[input_array_index] = c;
            input_array_index++;
        }
        fclose(input_file);
        input_array[input_array_index - 1] = '\0';
        unsigned char tape[30000] = {0};
        int data_pointer = 0;
        int index = 0;
        while (input_array[index] != '\0') {
            switch (input_array[index]) {
                case '>':
                    data_pointer++;
                    break;
                case '<':
                    data_pointer--;
                    break;
                case '+':
                    tape[data_pointer]++;
                    break;
                case '-':
                    tape[data_pointer]--;
                    break;
                case '.':
                    putchar(tape[data_pointer]);
                    break;
                case ',':
                    tape[data_pointer] = getchar();
                    break;
                case '[':
                    if (tape[data_pointer] == 0) {
                        int depth = 1;
                        int matching_index = 1;
                        while (depth != 0) {
                            if (input_array[index + matching_index] == '[') {
                                depth++;
                            } else if (input_array[index + matching_index] ==
                                       ']') {
                                depth--;
                            }
                            matching_index++;
                        }
                        index = index + matching_index - 1;
                    }
                    break;
                case ']':
                    if (tape[data_pointer] != 0) {
                        int depth = 1;
                        int matching_index = -1;
                        while (depth != 0) {
                            if (input_array[index + matching_index] == ']') {
                                depth++;
                            } else if (input_array[index + matching_index] ==
                                       '[') {
                                depth--;
                            }
                            matching_index--;
                        }
                        index = index + matching_index + 1;
                    }
                    break;
                default:
                    printf("Something going wrong ther\n");
                    break;
            }
            index++;
        }
    } else {
        printf("Please give a input file\n");
    }
}
