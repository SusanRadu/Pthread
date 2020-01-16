#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "atomic.h"

typedef struct _my_mux{
   atomic_int mux_value;
} my_mux;

int my_mux_init(my_mux *mux);

int my_mux_lock(my_mux *mux);

int my_mux_unlock(my_mux *mux);


#endif//_MUTEX_H_
