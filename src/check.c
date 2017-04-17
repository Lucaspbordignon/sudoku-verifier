#include <check.h>
#include <stdbool.h>
#include <stdio.h>

#include <utils.h>

uint8_t check_line(uint8_t line, uint8_t grid[SIZE][SIZE]) {
	uint8_t errors_found = 0;
	bool already_checked[SIZE] = {false};

	for (uint8_t i = 0; i < SIZE; i++) {
		if (already_checked[grid[line][i] - 1]) {
			errors_found++;
			printf("erro na linha %u.\n", line + 1);
		} else {
			already_checked[grid[line][i] - 1] = true;
		}
	}

	return errors_found;
}

uint8_t check_col(uint8_t col, uint8_t grid[SIZE][SIZE]) {
	uint8_t errors_found = 0;
	bool already_checked[SIZE] = {false};

	for (uint8_t i = 0; i < SIZE; i++) {
		if (already_checked[grid[i][col] - 1]) {
			errors_found++;
			printf("erro na coluna %u.\n", col + 1);
		} else {
			already_checked[grid[i][col] - 1] = true;
		}
	}

	return errors_found;
}

uint8_t check_region(uint8_t region, uint8_t grid[][SIZE]) {
	uint8_t x = region % 3;
	uint8_t y = region / 3;

	uint8_t errors_found = 0;
	bool already_checked[SIZE] = {false};

	for (uint8_t i = y*3; i < (y*3)+3; i++) {
		for (uint8_t j = x*3; j < (x*3)+3; j++) {
			if (already_checked[grid[i][j] - 1]) {
				errors_found++;
				printf("erro na regiao %u.\n", region + 1);
			} else {
				already_checked[grid[i][j] - 1] = true;
			}
		}
	}

	return errors_found;
}