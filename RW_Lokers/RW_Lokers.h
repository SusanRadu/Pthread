/*
 * @file:    RW_Lokers.h
 * @author:  Mihai-Daniel Surcea
 * @date:    19.12.2019
 * @Subject: Operating Systems
 * @University of Bucharest, Faculty of Mathematics and Computer Science
 * compile command: gcc -o executable -pthread fileUsingLibrary.c RW_Lokers.c
 */

#ifndef RW_LOKERS_H
#define RW_LOKERS_H
#include <pthread.h>

typedef struct RW_Lokers {
	pthread_mutex_t check;
	pthread_cond_t  wakeNext, wakeWriter;
	int people; // 0 - no one, -1 - one writer, n (> 0) - number of readers
	int writersWaiting; // number of writers waiting
	int readersWaiting; // number of readers waiting
} RW_Lokers;

void RW_Lokers_Init         (RW_Lokers*);
void RW_Lokers_Destroy      (RW_Lokers*);
int  RW_Lokers_LockWriter   (RW_Lokers*);
int  RW_Lokers_LockReader   (RW_Lokers*);
int  RW_Lokers_UnlockWriter (RW_Lokers*);
int  RW_Lokers_UnlockReader (RW_Lokers*);

#endif // RW_LOKERS_H
