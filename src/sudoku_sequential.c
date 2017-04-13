#include <stdio.h>
#include <stdlib.h>

/* grid size = 9x9 */
#define SIZE 9
/* just to facilitate */
#define true 1
#define false 0

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

/* Comparador para a funcao qsort() */
int comparator(const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

/* Verifica a existencia de erros nas linhas de uma matriz do sudoku */
int check_line(int height, int width, int grid[height][width]) {
	int errors_found = 0;
	int already_checked[width];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			already_checked[j] = false;

		for (int j = 0; j < width; j++)
			if (already_checked[grid[i][j] - 1]) {
				errors_found++;
				printf("erro na linha %d.\n", (i + 1));
				break;
			} else {
				already_checked[grid[i][j] - 1] = true;
			}
	}
	return errors_found;
}

/* Verifica a existencia de erros nas colunas de uma matriz do sudoku */
int check_col(int height, int width, int grid[height][width]) {
	int errors_found = 0;
	int already_checked[height];

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++)
			already_checked[j] = false;

		for (int j = 0; j < height; j++)
			if (already_checked[grid[j][i] - 1]) {
				errors_found++;
				printf("erro na coluna %d.\n", (i + 1));
				break;
			} else {
				already_checked[grid[j][i] - 1] = true;
			}
	}
	return errors_found;
}

/* Verifica a existencia de erros em todas as regioes de uma matriz do sudoku */
int check_region(int height, int width, int grid[height][width]) {
	int reg_size = 3;
	int reg_id, errors_found = 0;
	int already_checked[height];

	for (int i = 0; i < height; i += reg_size) {
		for (int j = 0; j < width; j += reg_size) {

			for (int k = 0; k < height; k++)
				already_checked[k] = false;

			for (int k = i; k < (i + reg_size); k++)
				for (int w = j; w < (j + reg_size); w++){
					if (already_checked[grid[k][w] - 1]) {
						errors_found++;
						printf("erro na regiao %d.\n", reg_id);
						break;
					} else {
						already_checked[grid[k][w] - 1] = true;
					}
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


