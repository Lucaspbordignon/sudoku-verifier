#include <stdio.h>
#include <stdint.h>

#include <utils.h>

/* Funcao que le um grid do arquivo "filename" e o armazena em uma matriz */
int load_grid(uint8_t grid[SIZE][SIZE], char *filename) {
	FILE *input_file = fopen(filename, "r");

	if (input_file != NULL) {
		for(uint8_t i = 0; i < SIZE; i++) {
			for(uint8_t j = 0; j < SIZE; j++) {
				size_t n;
				if (fscanf(input_file, "%u", &n) == -1 || n - 1 >= SIZE) {
					// reached EOF or number out of range (1..9)
					fclose(input_file);
					return 2;
				} else {
					grid[i][j] = n;
				}
			}
		}
		fclose(input_file);
		return 0;
	} else {
		return 1;
	}
}

void print_grid(const uint8_t grid[SIZE][SIZE]) {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++)
			printf("%u ", grid[i][j]);
		printf("\n");
	}
}
