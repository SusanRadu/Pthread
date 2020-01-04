/*
* - Library: atomic
* - author: Radu Dilirici
* - date: 04.01.2020
* - Subject: Operating Systems
* - University of Bucharest, Faculty of Mathematics and Computer Science
*/

#ifndef _ATOMIC_H_
#define _ATOMIC_H_

#include <stdatomic.h>

int atomic_dec_if_positive(atomic_int* x);

#endif//_ATOMIC_H_