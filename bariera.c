#include <stdatomic.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include "mutex.h"

int n=5;
int nmax=5;
my_mux *mux;
sem_t sem;

void barrier_point()
{
 sem_wait(&sem);

 my_mux_lock(&mux);
 n--;
 my_mux_unlock(&mux);

 while(n!=0) sem_post(&sem);

}

void *
tfun(void *v)
{
 int *tid=(int*)v;
 printf("%d reached the barrier\n", *tid);
 barrier_point();
 printf("%d passed the barrier\n", *tid);

 free(tid);
 return NULL;
}

int main(int argc, char *argv[])
{
 int i;
 sem_init(&sem,0,5);
 my_mux_init(&mux); 

 pthread_t thr[100];
 for(i=0;i<nmax;i++)
{
  int *v=malloc(sizeof(int));
  v[0]=i;
  pthread_create(&thr[i],NULL,tfun,v);
}
  for(i=0;i<nmax;i++)
    pthread_join(thr[i],NULL);

 return 0;

}
