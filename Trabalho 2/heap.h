#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void *data_type;

typedef struct Heap Heap;

Heap *heap_construct();

void heap_push(Heap *h, void *data, int priority);

bool heap_empty(Heap *h);

void *heap_pop(Heap *h);

void heap_destroy(Heap* h);

#endif
