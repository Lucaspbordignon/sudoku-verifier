#include <stdio.h>
#include <stdlib.h>

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
	int entire_line[width];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			entire_line[j] = grid[i][j];

		qsort(entire_line, width, sizeof(int), comparator);
		for (int j = 0; j < width; j++)
			if ((j + 1) != entire_line[j]) {
				errors_found++;
				printf("erro na linha %d.\n", (i + 1));
				break;
			}
	}
	return errors_found;
}

/* Verifica a existencia de erros nas colunas de uma matriz do sudoku */
int check_col(int height, int width, int grid[height][width]) {
	int errors_found = 0;
	int entire_col[height];

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++)
			entire_col[j] = grid[j][i];

		qsort(entire_col, height, sizeof(int), comparator);
		for (int j = 0; j < height; j++)
			if ((j + 1) != entire_col[j]) {
				errors_found++;
				printf("erro na coluna %d.\n", (i + 1));
				break;
			}
	}
	return errors_found;
}

/* Verifica a existencia de erros em todas as regioes de uma matriz do sudoku */
int check_region(int height, int width, int grid[height][width]) {
	int reg_size = 3;
	int reg_id, errors_found = 0;
	int entire_region[reg_size * reg_size];

	for (int i = 0; i < height; i += reg_size) {
		for (int j = 0; j < width; j += reg_size) {

			int aux_counter = 0;
			for (int k = i; k < (i + reg_size); k++)
				for (int w = j; w < (j + reg_size); w++){
					entire_region[aux_counter] = grid[k][w];
					aux_counter++;
				}

			qsort(entire_region, (reg_size * reg_size), sizeof(int), comparator);
			for (int k = 0; k < (reg_size * reg_size); k++)
				if ((k + 1) != entire_region[k]) {
					errors_found++;
					printf("erro na regiao %d.\n", reg_id);
					break;
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


