
#include "atomic.h"

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
