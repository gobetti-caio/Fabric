#include <stdio.h>
#include <stdlib.h>

#include "path.h"


/**
 * *
It creates the path and initializated its @param PossiBlePaths
with the origin_distance equal to 0 what will be useful in the function
visited_check on dijkstra.c
 * @param size - vector size
*/
Vector *paths_construct(int size)
{
    Vector *paths = vector_construct();

    for (int i = 0; i < size; i++)
    {
        PossiblePaths *pn = possible_paths_construct(0, i, 0);
        vector_push_back(paths, pn);
    }
    return paths;
};


/**
 *  Function that prints the path
 * @param paths - vector with the shortests paths 
*/
void paths_print(Vector *paths)
{
    Vector *p = paths;
    Vector *print_list = vector_construct();
    PossiblePaths *aux;
    int total_cost;
    int size = vector_size(p);

    for (int i = 1; i < size; i++)
    {
        aux = vector_get(p, i);
        total_cost = aux->origin_distance;
        while (aux->index != 0)
        {
            vector_push_back(print_list, aux);
            aux = vector_get(p, aux->previous);
        }
    	
        int size_print_list = vector_size(print_list);
        
        printf("0->");
        for (int j = 0; j < size_print_list; j++)
        {
            aux = vector_pop_back(print_list);
            if (j == size_print_list-1)
            {
                printf("%d", aux->index);
            }
            else 
            {
                printf("%d->", aux->index);
            }
        }
        printf(":%d\n", total_cost);
    }
    vector_destroy(print_list);
};


void paths_destroy(Vector *p)
{
    for (int i = 0; i < vector_size(p); i++)
    {
        PossiblePaths *pn = vector_get(p, i);
        free(pn);
    }

    vector_destroy(p);
};
