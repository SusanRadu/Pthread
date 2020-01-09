#include "mutex.h"

int my_mux_init(my_mux *mux)
{
 atomic_store(&mux->mux_value,0);
}

int my_mux_lock(my_mux *mux)
{
  while(1)
 {
  
  if(atomic_lock(&mux->mux_value))
    return 1;
 }
 
 return 0;

}

int my_mux_unlock(my_mux *mux)
{
 mux->mux_value=0;
 return 1;
}
