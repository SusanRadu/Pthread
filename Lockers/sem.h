/*
* - Library: semaphore
* - author: Radu Dilirici
* - date: 04.01.2020
* - Subject: Operating Systems
* - University of Bucharest, Faculty of Mathematics and Computer Science
*/

#ifndef _SEM_H_
#define _SEM_H_

#include "atomic.h"

typedef struct _my_sem_t {
	atomic_int sem_value;
} my_sem_t;

int my_sem_init(my_sem_t *sem, int starting_value);

void my_sem_post(my_sem_t *sem);

int my_sem_wait(my_sem_t *sem);

#endif//_SEM_H_