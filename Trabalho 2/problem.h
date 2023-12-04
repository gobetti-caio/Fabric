#include "vector.h"

typedef struct PossiblePaths
{
    int index;
    int previous;
    int previous_distance;
    int origin_distance;
}PossiblePaths;


typedef struct Problem
{
    Vector *possible_paths_nodes;
    int size;
}Problem;


Problem *read_file(FILE *arq);

PossiblePaths *possible_paths_construct(int index, int previous, int previous_distance);

void problem_destroy(Problem *p);



