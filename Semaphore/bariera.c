#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "sem.h"
#include <unistd.h>

pthread_mutex_t mtx;
my_sem_t sem;
int mx;
int crt = 0;

void barrier_point(){
	pthread_mutex_lock(&mtx);
	crt++;
	if (crt == mx){
		for (int i = 0; i < crt - 1; i++) {
			my_sem_post(&sem);
		}
		crt = 0;
		pthread_mutex_unlock(&mtx);
		return;
	}
	pthread_mutex_unlock(&mtx);
	my_sem_wait(&sem);
}

void *tfun(void *v){
	int tid = *(int*)v;
	printf("%d reached the barrier\n", tid);
	barrier_point();
	printf("%d passed the barrier\n", tid);
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Wrong number of arguments. Please specify the number of threads.\n");
		return 1;
	}
	mx = atoi(argv[1]);
	
	my_sem_init(&sem, 0);
	if (pthread_mutex_init(&mtx, NULL)){
		perror(NULL);
		return errno;
	}

	int nr_threads = mx;
	pthread_t *threads = calloc(nr_threads, sizeof(pthread_t));
	int *ids = malloc(nr_threads * sizeof(int));

	for (int i = 0; i < nr_threads; i++){
		ids[i] = i;
		if (pthread_create(&threads[i], NULL, tfun, &ids[i])){
			perror(NULL);
			return errno;
		}
	}

	for (int i = 0; i < nr_threads; i++){
		if (pthread_join(threads[i], NULL)){
			perror(NULL);
			return errno;
		}
	}

	pthread_mutex_destroy(&mtx);
	my_sem_destroy(&sem);
	free(threads);
	free(ids);
}