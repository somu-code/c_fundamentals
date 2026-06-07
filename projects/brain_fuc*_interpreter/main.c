/*
The three things in interpreter
1. The tape - an array of cells(memory)
2. The data pointer - tracks the current cell, where i am at
3. The instruction pointer - tracks which command currently executing
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr,
			"Provide a valid brain fuc* source file as a argument\n");
		return EXIT_FAILURE;
	} else if (argc > 2) {
		fprintf(stderr, "Too many files to handle\n");
		return EXIT_FAILURE;
	}
	FILE *input_file = fopen(argv[1], "r");
	if (input_file == NULL) {
		perror("Failed to open file");
		return EXIT_FAILURE;
	}
	fseek(input_file, 0, SEEK_END);
	long input_file_size = ftell(input_file);
	if (input_file_size == 0) {
		fclose(input_file);
		fprintf(stderr, "Nothing to interpret\n");
		return EXIT_FAILURE;
	} else if (input_file_size > 30000) {
		fclose(input_file);
		fprintf(stderr, "File is too large to handle\n");
		return EXIT_FAILURE;
	}
	fseek(input_file, 0, SEEK_SET);
	char *input_array = malloc(input_file_size);
	if (input_array == NULL) {
		fclose(input_file);
		perror("Failed to allocate memory");
		return EXIT_FAILURE;
	}
	long input_array_index = 0;
	int c;
	while ((c = fgetc(input_file)) != EOF) {
		input_array[input_array_index] = c;
		input_array_index++;
	}
	fclose(input_file);
	unsigned char tape[30000] = { 0 };
	int data_pointer = 0;
	long index = 0;
	while (index < input_file_size) {
		switch (input_array[index]) {
		case '>':
			data_pointer++;
			if (data_pointer > 29999) {
				free(input_array);
				fprintf(stderr, "Tape out of bound\n");
				return EXIT_FAILURE;
			}
			break;
		case '<':
			data_pointer--;
			if (data_pointer < 0) {
				free(input_array);
				fprintf(stderr, "Tape out of bound\n");
				return EXIT_FAILURE;
			}
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
				long matching_index = 1;
				while (depth != 0) {
					if (index + matching_index >
					    input_file_size - 1) {
						free(input_array);
						fprintf(stderr,
							"Input file has one or more unmatched [\n");
						return EXIT_FAILURE;
					} else if (input_array[index +
							       matching_index] ==
						   '[') {
						depth++;
					} else if (input_array[index +
							       matching_index] ==
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
				long matching_index = -1;
				while (depth != 0) {
					if (index + matching_index < 0) {
						free(input_array);
						fprintf(stderr,
							"Input file has one or more unmatched ]\n");
						return EXIT_FAILURE;
					} else if (input_array[index +
							       matching_index] ==
						   ']') {
						depth++;
					} else if (input_array[index +
							       matching_index] ==
						   '[') {
						depth--;
					}
					matching_index--;
				}
				index = index + matching_index + 1;
			}
			break;
		}
		index++;
	}
	if (tape[data_pointer] != 10) {
		printf("\n");
	}
	free(input_array);
	return EXIT_SUCCESS;
}
