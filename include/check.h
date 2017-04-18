#ifndef CHECK_H
#define CHECK_H

#include <stdint.h>

#include <utils.h>

uint8_t check_line(uint8_t, uint8_t[][SIZE], unsigned int);
uint8_t check_col(uint8_t, uint8_t[][SIZE], unsigned int);
uint8_t check_region(uint8_t, uint8_t[][SIZE], unsigned int);

#endif
