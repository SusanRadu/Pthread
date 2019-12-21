/*
 * @file:    test-RW_Lokers.c
 * @author:  Mihai-Daniel Surcea
 * @date:    19.12.2019
 * @Subject: Operating Systems
 * @University of Bucharest, Faculty of Mathematics and Computer Science
 * compile command:  gcc -o test-RW_Lokers -pthread test-RW_Lokers.c RW_Lokers.c
 */
 
#include "RW_Lokers.h"
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

RW_Lokers lock;

typedef struct RW_arg {
	int sleepTime, counter;
} RW_arg;

static void * reader (void *arg) {
	int sleepTime = ((RW_arg*) arg)->sleepTime,
		counter   = ((RW_arg*) arg)->counter;
	printf ("READER %d added\n", counter);
	RW_Lokers_LockReader (&lock);
	sleep(sleepTime);
	RW_Lokers_UnlockReader (&lock);
	printf ("READER %d eliminated\n", counter);
}

static void * writer (void *arg) {
	int sleepTime = ((RW_arg*) arg)->sleepTime,
		counter   = ((RW_arg*) arg)->counter;
	printf ("WRITER %d added\n", counter);
	RW_Lokers_LockWriter (&lock);
	sleep(sleepTime);
	RW_Lokers_UnlockWriter  (&lock);
	printf ("WRITER %d eliminated\n", counter);
	
}
 
int main () {
	
	int n, nr, rw, t, waitAfter;
	RW_arg arg;
	FILE *in = fopen ("test-RW_Lokers.in", "r");
	
	if (in < 0) {printf ("Coudn't open the read file\n"); return 0;}
	
	fscanf (in, "%d", &n);
	pthread_t thr[n];
	RW_Lokers_Init (&lock);
	
	for (nr = 0; nr < n; nr++) {
		fscanf (in, "%d%d%d", &rw, &arg.sleepTime, &waitAfter);
		arg.counter = nr + 1;
		pthread_create (&thr[nr], NULL, ((rw) ? reader : writer), &arg);
		sleep (waitAfter);
	}
	fclose(in);
	
	
	while (nr > 0) {
		pthread_join (thr[--nr], NULL);
	}
	printf ("done\n");
	RW_Lokers_Destroy (&lock);
    return 0;
}
