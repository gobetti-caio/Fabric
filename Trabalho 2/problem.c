#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "problem.h"

PossiblePaths *possible_paths_construct(int index, int previous, int previous_distance)
{
    PossiblePaths *pp = (PossiblePaths *)calloc(1, sizeof(PossiblePaths));
    pp->index = index;
    pp->previous = previous;
    pp->previous_distance = previous_distance;
    pp->origin_distance = 0;

    return pp;
}

Problem *problem_construct()
{
    Problem *p = (Problem *)calloc(1, sizeof(Problem));
    p->possible_paths_nodes = vector_construct();
    p->size = 0;

    return p;
}

Problem *read_file(FILE *arq)
{
    Problem *p = problem_construct();
    int qtd_nodes;
    int index, prev_distance;
    char last_char;

    fscanf(arq, "%d\n", &qtd_nodes);
    p->size = qtd_nodes + 1;

    for (int i = 0; i < qtd_nodes; i++)
    {
        while (1)
        {
            fscanf(arq, "%d%d%c", &index, &prev_distance, &last_char);

            PossiblePaths *n = possible_paths_construct(i, index, prev_distance);
            vector_push_back(p->possible_paths_nodes, n);

            if (last_char == '\n' || last_char == '\r')
            {
                break;
            }
        }
    }
    return p;
}

void problem_destroy(Problem *p)
{
    int size = vector_size(p->possible_paths_nodes);

    for (int i = 0; i < size; i++)
    {
        PossiblePaths *n = vector_get(p->possible_paths_nodes, i);
        free(n);
    }
    
    vector_destroy(p->possible_paths_nodes);
    free(p);
}