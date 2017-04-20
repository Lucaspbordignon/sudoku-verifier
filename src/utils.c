#include <stdio.h>
#include <stdint.h>

#include <utils.h>

/* Funcao que le um grid do arquivo "filename" e o armazena em uma matriz */
int load_grid(uint8_t grid[SIZE][SIZE], char *filename) {
	FILE *input_file = fopen(filename, "r");

	if (input_file != NULL) {
		for(int i = 0; i < SIZE; i++)
			for(int j = 0; j < SIZE; j++)
				fscanf(input_file, "%u", &grid[i][j]);
		fclose(input_file);
		return 1;
	}

	return 0;
}

void print_grid(const uint8_t grid[SIZE][SIZE]) {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++)
			printf("%u ", grid[i][j]);
		printf("\n");
	}
}
