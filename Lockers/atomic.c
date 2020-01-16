/*
* - Library: atomic
* - authors: Radu Dilirici, Radu Susan
* - date: 16.01.2020
* - Subject: Operating Systems
* - University of Bucharest, Faculty of Mathematics and Computer Science
*/

#include "atomic.h"

//atomic function to check and lock the mutex
int atomic_lock(atomic_int *x)
{
 atomic_int exp,new;
 for(;;)
 {
  exp = 0;
  new = 1;

  int worked = atomic_compare_exchange_weak(x,&exp,new);
  if(worked)
    return 1;
 }

 return 0;
}

/*
* atomically decrease the x if it is greater than 0
* returns 1 on success and 0 on failure
*/
int atomic_dec_if_positive(atomic_int* x) {

    atomic_int old, new;
    for (;;) {
        old = atomic_load(x);
        new = old - 1;
        if (old <= 0) {
            return 0;
        }
        int worked = atomic_compare_exchange_weak(x, &old, new);
        if (worked) {
            return 1;
        }
    }
    return 0;
}
