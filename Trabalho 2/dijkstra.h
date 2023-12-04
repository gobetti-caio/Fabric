#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "vector.h"
#include "heap.h"
#include "problem.h"


Vector *solve_dijkstra(Problem *problem);
void update_path(Vector *paths, PossiblePaths *node_removed);
void update_heap(PossiblePaths *node_removed, Vector *paths, Problem *p, Heap *not_visited);


#endif