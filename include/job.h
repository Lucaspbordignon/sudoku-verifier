#ifndef JOBS_H
#define JOBS_H

typedef enum {
	line,
	column,
	region
} job_type;

typedef struct {
	job_type t;
	uint8_t pos;
} job;

#endif
