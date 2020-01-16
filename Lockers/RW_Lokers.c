/*
 * @file:    RW_Lokers.c
 * @author:  Mihai-Daniel Surcea
 * @date:    19.12.2019
 * @Subject: Operating Systems
 * @University of Bucharest, Faculty of Mathematics and Computer Science
 * compile command: gcc -o executable -pthread fileUsingLibrary.c RW_Lokers.c
 */

#include "RW_Lokers.h"
#include <stdio.h>

 void RW_Lokers_Init (RW_Lokers* lock){
	lock->people         = 0;
	lock->writersWaiting = 0;
	lock->readersWaiting = 0;
	pthread_mutex_init (&lock->check,      NULL);
	pthread_cond_init  (&lock->wakeNext,   NULL);
	pthread_cond_init  (&lock->wakeWriter, NULL);
}

void RW_Lokers_Destroy (RW_Lokers* lock) {
	pthread_mutex_destroy (&lock->check);
	pthread_cond_destroy  (&lock->wakeNext);
	pthread_cond_destroy  (&lock->wakeWriter);
}

// return 1 if the access was granted or 0 if there was an error
int RW_Lokers_LockWriter (RW_Lokers* lock) {
	pthread_mutex_lock (&lock->check);
	if (lock->people == 0) {// you are the first one :D
		lock->people = -1;  // access to write granted
		pthread_mutex_unlock (&lock->check);
		return 1;
	}
	lock->writersWaiting += 1; // you are in the waiting list
	
	if (lock->writersWaiting > 1) { // you are not the first one waiting to w
		pthread_mutex_unlock (&lock->check);
		pthread_cond_wait (&lock->wakeNext, &lock->check); // wait for the one before you to wake you
		
		if (lock->people == 0) {       // if a writer woke up you, you are the next one :)
			lock->people = -1;         // access to write granted
			lock->writersWaiting -= 1; // you are not in the waiting list anymore
			pthread_mutex_unlock (&lock->check);
			return 1;
		}
	}
	pthread_mutex_unlock (&lock->check);
	
	pthread_cond_wait (&lock->wakeWriter, &lock->check); // you have to wait for all the readers to finish :(
	
	lock->writersWaiting -= 1; // you are not in the waiting list anymore
	if (lock->people == 0) {   // there should be nobody reading/writing the document
		lock->people = -1;     // access to write granted
		pthread_mutex_unlock (&lock->check);
		return 1;
	}
	pthread_mutex_unlock (&lock->check);
	return 0; // it should never return false
}

// return 1 if the access was granted or 0 if there was an error
int RW_Lokers_LockReader (RW_Lokers* lock) {
	pthread_mutex_lock (&lock->check);
	if (lock->people != -1 && lock->writersWaiting == 0) { // no one is writing or waiting to wirte before you
		lock->people += 1;                           // access to read granted
		pthread_mutex_unlock (&lock->check);
		return 1;
	}
	lock->readersWaiting += 1; // one more reader in the queue
	pthread_mutex_unlock (&lock->check);
	
	pthread_cond_wait (&lock->wakeNext, &lock->check); // wait for all the writers before you to finish
	
	lock->readersWaiting -= 1; // you are not waiting anymore
	if (lock->people >= 0) {   // there are only readers before you
		lock->people += 1;     // access to read granted
		pthread_mutex_unlock (&lock->check); // ------------------------------------------------------------- do it after
		if (lock->readersWaiting + lock->writersWaiting != 0) {
			pthread_cond_signal (&lock->wakeNext); // try to notify the next person in queue
		}
		return 1;
	}
	pthread_mutex_unlock (&lock->check);
	return 0; // it should never return false
}

// return true if the unlock has finished successfully or false if there was an error
int RW_Lokers_UnlockWriter (RW_Lokers* lock) {
	int status = 1;
	pthread_mutex_lock (&lock->check);
	if (lock->people == -1) {lock->people = 0;}
	else {status = 0;} // only occures if this function was called without calling first the AddWriter function
	if ((lock->writersWaiting + lock->readersWaiting != 0) && status) {
		pthread_cond_signal (&lock->wakeNext);
	}
	pthread_mutex_unlock (&lock->check); 
	return status;
}

// return true if the unlock has finished successfully or false if there was an error
int RW_Lokers_UnlockReader (RW_Lokers* lock) {
	int status = 1;
	pthread_mutex_lock (&lock->check);
	if (lock->people > 0) {lock->people -= 1;}
	else {status = 0;} // only occures if this function was called without calling first the AddReader function
	if (lock->people == 0 && lock->writersWaiting != 0 && status) {
		pthread_cond_signal (&lock->wakeWriter);
	}
	pthread_mutex_unlock (&lock->check);
	return status;
}
