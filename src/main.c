#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <utils.h>
#include <check.h>

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

	for (uint8_t i = 0; i < SIZE; i++) {
		errors += check_col(i, grid);
		errors += check_line(i, grid);
		errors += check_region(i, grid);
	}

	printf("Erros encontrados: %u.\n", errors);
	return 0;

}
