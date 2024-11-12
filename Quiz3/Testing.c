#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define ARRAY_SIZE 1000000000

int exponential(int base, int exp) {
	int result = 1;
	for (int i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
}

int main() {
	clock_t start;
	struct timeval inicio, final2;
	int tmili;

	int NUM_THREADS = 0;
	printf("Enter the number of threads: ");
	scanf("%d", &NUM_THREADS);

	start = clock();
	gettimeofday(&inicio, NULL);

	int i = 0, tid = 0;

	int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));
	if (array == NULL) {
		printf("Erro ao alocar memória\n");
		return 1;
	}

	for (i = 0; i < ARRAY_SIZE; i++) {
		array[i] = i;
	}

	printf("Running with %d threads\n", NUM_THREADS);

	#pragma omp parallel num_threads(NUM_THREADS) shared(array) private(i, tid)
	{
		tid = omp_get_thread_num();
		clock_t clock_start = clock();
		
		#pragma omp for
		for (i = 0; i < ARRAY_SIZE; i++) {
			array[i] = exponential(array[i], 5);
		}

		clock_t clock_end = clock();
		double thread_time_used = ((double)(clock_end - clock_start)) / CLOCKS_PER_SEC;
		printf("Thread #%d Time: %f\n", tid, thread_time_used);
	}

	gettimeofday(&final2, NULL);
	tmili = (int) (1000 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000);

	printf("Time elapsed: %f\n", ((double)clock() - start)/ CLOCKS_PER_SEC);
	printf("tempo decorrido: %d milisegundos\n", tmili);

	free(array);
	return 0;
}