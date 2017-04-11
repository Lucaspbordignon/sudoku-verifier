#include <stdio.h>

/* grid size = 9x9 */
#define SIZE 9
/* sum of numbers, from 1 to 9 */
#define SUDOKU_SUM 45

/* Funcao que le um grid do arquivo "filename" e o armazena em uma matriz */
int load_grid(int grid[][SIZE], char *filename) {
	FILE *input_file = fopen(filename, "r");

	if (input_file != NULL) {
		for(int i = 0; i < SIZE; i++)
			for(int j = 0; j < SIZE; j++)
				fscanf(input_file, "%d", &grid[i][j]);
		fclose(input_file);
		return 1;
	}

	return 0;
}

/* Verifica a existencia de erros nas linhas de uma matriz do sudoku */
int check_line(int height, int width, int grid[height][width]) {
	int errors_found = 0;
	int sum;
	for (int i = 0; i < height; i++) {
		sum = 0;
		for (int j = 0; j < width; j++)
			sum += grid[i][j];

		if (sum != SUDOKU_SUM) {
			errors_found++;
			printf("erro na linha %d.\n", (i + 1));
		}
	}
	return errors_found;
}

/* Verifica a existencia de erros nas colunas de uma matriz do sudoku */
int check_col(int height, int width, int grid[height][width]) {
	int errors_found = 0;
	int sum;
	for (int i = 0; i < width; i++) {
		sum = 0;
		for (int j = 0; j < height; j++)
			sum += grid[j][i];

		if (sum != SUDOKU_SUM) {
			errors_found++;
			printf("erro na coluna %d.\n", (i + 1));
		}
	}
	return errors_found;
}

/* Verifica a existencia de erros em todas as regioes de uma matriz do sudoku */
int check_region(int height, int width, int grid[height][width]) {
	int reg_size = 3;
	int reg_id, errors_found = 0;
	int sum;
	for (int i = 0; i < height; i += reg_size) {
		for (int j = 0; j < width; j += reg_size) {
			sum = 0;

			for (int k = i; k < (i + reg_size); k++)
				for (int w = j; w < (j + reg_size); w++)
					sum += grid[k][w];

			if (sum != SUDOKU_SUM) {
				errors_found++;
				printf("erro na região %d.\n", reg_id);
			}
			reg_id++;
		}
	}

	return errors_found;
}


int main(int argc, char *argv[]) {

	if(argc != 2) {
		printf("Erro: informe o arquivo de entrada!\n");
		printf("Uso: %s <arquivo de entrada>\n\n", argv[0]);
		return 1;
	}

	/* Le o grid do arquivo, armazena na matriz grid e imprime */
	int errors = 0;
	int size = 9;
	int grid[size][size];
	if(load_grid(grid, argv[1])) {
		printf("Quebra-cabecas fornecido:\n");
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size; j++)
				printf("%d ", grid[i][j]);
			printf("\n");
		}
		printf("\n");
	}

	errors += check_col(size, size, grid);
	errors += check_line(size, size, grid);
	errors += check_region(size, size, grid);

	printf("Erros encontrados: %d.\n", errors);
	return 0;
}


