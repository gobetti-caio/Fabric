#ifndef _PATH_H_
#define _PATH_H_

#include "problem.h"
#include "vector.h"


Vector *paths_construct(int size);

void paths_destroy(Vector *p);

void paths_print(Vector *paths);


#endif
