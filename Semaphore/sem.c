/*
* - Library: Semaphore
* - author: Radu Dilirici
* - date: 03.01.2020
* - Subject: Operating Systems
* - University of Bucharest, Faculty of Mathematics and Computer Science
*/

#include "sem.h"

// returns 1 on success and 0 on failure
int my_sem_init(my_sem_t *sem, int starting_value) {
	if (starting_value < 0){
		return 0;
	}
	atomic_store(&sem->sem_value, starting_value);
	return 1;
}

void my_sem_post(my_sem_t *sem) {
	sem->sem_value++;  // sem_value is of type atomic_int so this will execute atomically
}

// returns 1 on success and 0 on failure
int my_sem_wait(my_sem_t *sem) {
	while (1) {
		if (atomic_dec_if_positive(&sem->sem_value)){  // even though the variabile is atomic,
			return 1;                                  // I need to [check if it is greater than 0 and substract 1 if so] atomically
		}
	}
	return 0;
}