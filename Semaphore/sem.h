/*
* - Library: Semaphore
* - author: Radu Dilirici
* - date: 03.01.2020
* - Subject: Operating Systems
* - University of Bucharest, Faculty of Mathematics and Computer Science
*/

#ifndef _SEM_H_
#define _SEM_H_
#include <pthread.h>

typedef struct _my_sem_t {
	unsigned int sem_value;
	pthread_mutex_t mtx;
} my_sem_t;

void my_sem_init(my_sem_t *sem, unsigned int starting_value);

void my_sem_destroy(my_sem_t *sem);

void my_sem_post(my_sem_t *sem);

int my_sem_wait(my_sem_t *sem);

#endif//_SEM_H_