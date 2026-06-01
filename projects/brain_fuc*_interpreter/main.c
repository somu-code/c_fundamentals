/*
The three things in interpreter
1. The tape - an array of cells(memory)
2. The data pointer - tracks the current cell, where i am at
3. The instruction pointer - tracks which command currently executing
*/

#include <stdio.h>

int main(int argc, char **argv) {
    if (argc == 2) {
        FILE *input_file = fopen(argv[1], "r");
        fseek(input_file, 0, SEEK_END);
        long input_file_size = ftell(input_file);
        fseek(input_file, 0, SEEK_SET);
        input_file_size++;
        char input_array[input_file_size];
        int input_array_index = 0;
        int c;
        while ((c = fgetc(input_file)) != EOF) {
            input_array[input_array_index] = c;
            input_array_index++;
        }
        input_array[input_file_size] = '\0';
        unsigned char tape[30000] = {0};
        int data_pointer = 0;
        int instruction_pointer;
        int counter = 0;
        int index = 0;
        while ((instruction_pointer = input_array[index]) != '\0') {
            switch (instruction_pointer) {
                case '>':
                    data_pointer++;
                    counter = 0;
                    break;
                case '<':
                    data_pointer--;
                    counter = 0;
                    break;
                case '+':
                    counter++;
                    tape[data_pointer] = counter;
                    break;
                case '-':
                    counter--;
                    tape[data_pointer] = counter;
                    break;
                case '.':
                    putchar(tape[data_pointer]);
                    break;
                case ',':
                    tape[data_pointer] = getchar();
                    break;
                case '[':
                    break;
                case ']':
                    break;
            }
            index++;
        }
    } else {
        printf("Please give a input file\n");
    }
}
