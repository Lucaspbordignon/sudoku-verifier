#ifndef CHECK_H
#define CHECK_H

#include <stdint.h>

#include <utils.h>
#include <job.h>

uint8_t check_line_or_col(uint8_t, const uint8_t[SIZE][SIZE], unsigned int,
		job_type);
uint8_t check_region(uint8_t, const uint8_t[SIZE][SIZE], unsigned int);

#endif
