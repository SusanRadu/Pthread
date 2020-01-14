/*
* - Test for the function "atomic_dec_if_positive"
* - author: Radu Dilirici
* - date: 15.01.2020
* - Subject: Operating Systems
* - University of Bucharest, Faculty of Mathematics and Computer Science
*/
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_int cnt;

static inline int atomic_dec_if_positive(atomic_int* x) {

    atomic_int old, new;
    for (;;) {
        old = atomic_load(x);
        new = old - 1;
        if (old <= 0){
            break;
        }
        int worked = atomic_compare_exchange_strong(x, &old, new);
        if (worked) {
            break;
        }
    }
    return new;
}
 
void* f(void* thr_data)
{
    for(int n = 0; n < 10; ++n) {
        atomic_dec_if_positive(&cnt);
    }
    return 0;
}
 
int main(void)
{
    for (int i = 0; i < 100000; i++){
        cnt = 100;
        pthread_t thr[10];
        for(int n = 0; n < 10; ++n)
            pthread_create(&thr[n], NULL, f, NULL);
        for(int n = 0; n < 10; ++n)
            pthread_join(thr[n], NULL);
        if (cnt != 0){
            printf("PANICA!!!! %d\n", cnt);
        }
    }
}
