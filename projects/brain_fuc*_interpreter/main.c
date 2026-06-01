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
        unsigned char tape[30000] = {0};
        int data_pointer = 0;
        int instruction_pointer;
        int counter = 0;
        while ((instruction_pointer = fgetc(input_file)) != EOF) {
            switch (instruction_pointer) {
                case '>':
                    data_pointer++;
                    break;
                case '<':
                    data_pointer--;
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
        }
    } else {
        printf("Please give a input file\n");
    }
}
