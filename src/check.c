#include <check.h>
#include <stdbool.h>
#include <stdio.h>

#include <utils.h>
#include <job.h>

uint8_t check_line_or_col(uint8_t pos, const uint8_t grid[SIZE][SIZE],
		unsigned int thread_id, job_type t) {

	uint8_t errors_found = 0;
	bool already_checked[SIZE] = {false};

	for (uint8_t i = 0; i < SIZE; i++) {

		uint8_t v = (t == line ? grid[pos][i] : grid[i][pos]) - 1;

		if (already_checked[v]) {
			errors_found++;
			printf("Thread %u: erro na %s %u.\n", thread_id,
					t == line ? "linha" : "coluna", pos + 1);
		} else {
			already_checked[v] = true;
		}

	}

	return errors_found;

}

uint8_t check_region(uint8_t region, const uint8_t grid[SIZE][SIZE],
		unsigned int thread_id) {

	uint8_t errors_found = 0;
	bool already_checked[SIZE] = {false};

	uint8_t start_i = (region / 3) * 3;
	uint8_t start_j = (region % 3) * 3;

	for (uint8_t i = start_i; i < start_i + 3; i++) {
		for (uint8_t j = start_j; j < start_j + 3; j++) {

			if (already_checked[grid[i][j] - 1]) {
				errors_found++;
				printf("Thread %u: erro na regiao %u.\n",
						thread_id, region + 1);
			} else {
				already_checked[grid[i][j] - 1] = true;
			}

		}
	}

	return errors_found;

}
