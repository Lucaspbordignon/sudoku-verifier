#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <utils.h>

/* Verifica a existencia de erros nas linhas de uma matriz do sudoku */
uint8_t check_line(uint8_t height, uint8_t width, uint8_t grid[height][width]) {
	uint8_t errors_found = 0;
	bool already_checked[width];

	for (uint8_t i = 0; i < height; i++) {
		for (uint8_t j = 0; j < width; j++)
			already_checked[j] = false;

		for (uint8_t j = 0; j < width; j++)
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
uint8_t check_col(uint8_t height, uint8_t width, uint8_t grid[height][width]) {
	uint8_t errors_found = 0;
	bool already_checked[height];

	for (uint8_t i = 0; i < width; i++) {
		for (uint8_t j = 0; j < height; j++)
			already_checked[j] = false;

		for (uint8_t j = 0; j < height; j++)
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
uint8_t check_region(uint8_t height, uint8_t width, uint8_t grid[height][width]) {
	uint8_t reg_size = 3;
	uint8_t reg_id = 0, errors_found = 0;
	bool already_checked[height];

	for (uint8_t i = 0; i < height; i += reg_size) {
		for (uint8_t j = 0; j < width; j += reg_size) {

			for (uint8_t k = 0; k < height; k++)
				already_checked[k] = false;

			for (uint8_t k = i; k < (i + reg_size); k++)
				for (uint8_t w = j; w < (j + reg_size); w++){
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
		printf("Erro: informe o arquivo de entrada!\n"
				"Uso: %s <arquivo de entrada>\n\n", argv[0]);
		return 1;
	}

	/* Le o grid do arquivo, armazena na matriz grid e imprime */
	uint8_t errors = 0;
	uint8_t grid[SIZE][SIZE];
	if(load_grid(grid, argv[1])) {
		printf("Quebra-cabecas fornecido:\n");
		print_grid(grid);
	}

	errors += check_col(SIZE, SIZE, grid);
	errors += check_line(SIZE, SIZE, grid);
	errors += check_region(SIZE, SIZE, grid);

	printf("Erros encontrados: %u.\n", errors);
	return 0;
}
