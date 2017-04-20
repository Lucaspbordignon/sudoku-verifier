#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

#include <utils.h>
#include <check.h>
#include <job.h>

#define N_JOBS 27

void* worker(void*);

uint8_t grid[SIZE][SIZE]; // The sudoku grid itself
uint8_t errors = 0; // Errors found in the grid

/*
 * This is basically a queue that holds the 'jobs' that need to be done to
 * verify the sudoku grid, each job is to verify a line, column or 'region'
 */
job jobs[N_JOBS];
uint8_t next = 0;

pthread_mutex_t queue_lock;
pthread_mutex_t errors_lock;

int main(int argc, char *argv[]) {

	if(argc != 3) {
		printf("Uso: %s <arquivo de entrada> <numero de threads>\n\n",
				argv[0]);
		return 1;
	}

	// Reads the grid from a file, and prints it
	if(load_grid(grid, argv[1])) {
		printf("Quebra-cabecas fornecido:\n");
		print_grid(grid);
	}

	// Creates queue of jobs
	for (uint8_t i = 0; i < N_JOBS/3; i++) {
		jobs[i].pos = i;
		jobs[i+9].pos = i;
		jobs[i+18].pos = i;

		jobs[i].t = line;
		jobs[i+9].t = column;
		jobs[i+18].t = region;
	}

	unsigned int n_threads = atoi(argv[2]);
	pthread_t* threads = malloc(n_threads*sizeof(pthread_t));

	pthread_mutex_init(&queue_lock, NULL);
	pthread_mutex_init(&errors_lock, NULL);

	// Create threads
	unsigned int thread_ids[n_threads];
	for (unsigned int i = 0; i < n_threads; i++) {
		thread_ids[i] = i + 1;
		pthread_create(&threads[i], NULL, worker, (void*) &thread_ids[i]);
	}

	// Join threads
	for (unsigned int i = 0; i < n_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&queue_lock);
	pthread_mutex_destroy(&errors_lock);

	free(threads);

	printf("Erros encontrados: %u.\n", errors);
	return 0;

}

void* worker(void* arg) {
	unsigned int thread_id = *((unsigned int*) arg);
	uint8_t e;
	job* j = NULL;

	while (1) {
		pthread_mutex_lock(&queue_lock);
		if (next < N_JOBS) {
			// Gets the next job on the queue
			j = jobs + next;
			next++;
			pthread_mutex_unlock(&queue_lock);
		} else {
			// All jobs are done
			pthread_mutex_unlock(&queue_lock);
			break;
		}

		// Do the check correspondent to the acquired job
		e = j->t == region ?
			check_region(j->pos, grid, thread_id) :
			check_line_or_col(j->pos, grid, thread_id, j->t);

		if (e > 0) {
			// if found errors, update `errors`
			pthread_mutex_lock(&errors_lock);
			errors += e;
			pthread_mutex_unlock(&errors_lock);
		}
	}

	return NULL;
}
