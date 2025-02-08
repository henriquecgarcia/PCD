#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define N 10

int escritores_ativos = 0;
int leitores_ativos = 0;

void ler(int id) {
	sleep(1);
	if (escritores_ativos > 0) {
		printf("Leitor %d está esperando\n", id); fflush(stdout);
	}
	leitores_ativos++;
	printf("Leitor %d está lendo\n", id); fflush(stdout);
	leitores_ativos--;
}

void escrever(int id) {
	sleep(1);
	if (leitores_ativos > 0 || escritores_ativos > 0) {
		printf("Escritor %d está esperando\n", id); fflush(stdout);
		return;
	}
	escritores_ativos++;
	printf("Escritor %d está escrevendo\n", id); fflush(stdout);
	escritores_ativos--;
}

void leitor(int id) {
	while (1) {
		ler(id);
		usleep(1000);
	}
}

void escritor(int id) {
	while (1) {
		#pragma omp critical
		escrever(id);
		usleep(1000);
	}
}

int main(int argc, char *argv[]) {
	#pragma omp parallel num_threads(N)
	{
		if (omp_get_thread_num() % 2 == 0) {
			leitor(omp_get_thread_num());
		} else {
			escritor(omp_get_thread_num());
		}
	}
	return 0;
}