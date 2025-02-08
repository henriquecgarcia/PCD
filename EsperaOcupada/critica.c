#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

int request = 0, respond = 0;
long int SOMA = 0;

void server() {
	while (omp_get_num_threads() > 1) {
		while (request == 0); // Waiting for request != 0
		if (request < 0) {
			printf("Server is shutting down\n");
			break;
		}
		respond = request;
		while (respond != 0); // Waiting for respond = 0
		request = 0;
	}
}

void critical_section(int tid) {
	printf("Thread %d is in critical section\n", tid);
	int local = SOMA;
	sleep(rand() % 2);
	SOMA = local + 1;
}

void client(int tid) {
	int i;
	for (i = 0; i < tid * 2; i++) {
	// while (1) {
		while (respond != tid)
			request = tid;
		critical_section(tid);
		respond = 0;
	}
}

int main() {

	int threads_num = 5, threads_acabadas = 0;

	printf("NCLIENTS = %d\n", threads_num - 1);

	omp_set_num_threads(threads_num);
	#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		if (tid == 0)
			server();
		else {
			client(tid);
			threads_acabadas++;
		}
		if (threads_acabadas == threads_num - 1)
			request = -1;
	}
	printf("SOMA = %ld\n", SOMA);
	return 0;
}