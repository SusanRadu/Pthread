/*
* - Library: atomic
* - author: Radu Susan
* - date: 08.01.2020
* - Subject: Operating Systems
* - University of Bucharest, Faculty of Mathematics and Computer Science
*/

#include "atomic.h"
#include <stdatomic.h>
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
