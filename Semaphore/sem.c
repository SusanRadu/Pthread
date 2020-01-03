/*
* - Library: Semaphore
* - author: Radu Dilirici
* - date: 03.01.2020
* - Subject: Operating Systems
* - University of Bucharest, Faculty of Mathematics and Computer Science
*/

#include "sem.h"

void my_sem_init(my_sem_t *sem, unsigned int starting_value) {
	sem->sem_value = starting_value;
	pthread_mutex_init(&sem->mtx, NULL);
}

void my_sem_destroy(my_sem_t *sem) {
	pthread_mutex_destroy(&sem->mtx);
}

void my_sem_post(my_sem_t *sem) {
	pthread_mutex_lock(&sem->mtx);
	sem->sem_value++; 
	pthread_mutex_unlock(&sem->mtx);
}

// returns 1 on success,  and 0 on failure
int my_sem_wait(my_sem_t *sem) {
	while (1) {
		if (sem->sem_value > 0){ // busy waiting. wait until there is a free spot
			pthread_mutex_lock(&sem->mtx); // make sure you are the only one changing the semaphore counter
			if (sem->sem_value > 0){ // check again if there is room for you. maybe another thread took your spot
				                     // (you both passed the if statement with the sem_value being 1 and the other one locked the mutex first)
				sem->sem_value--;
				pthread_mutex_unlock(&sem->mtx);
				return 1;
			}
			else {
				pthread_mutex_unlock(&sem->mtx);
			}
		}
	}
	return 0;
}