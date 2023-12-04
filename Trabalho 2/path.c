#include <stdio.h>
#include <stdlib.h>

#include "path.h"

/**
 * Função criada para construir o vetor que guarda os nós com o valor 
 * para o antecessor e qual o antecessor
 * Ela cria os nós problema com a origem e custo = 0, no algoritmo
 * de djikstra eu vou apenas atualizando eles
 * @param size tamanho do vetor 
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
 * Função criada para printar os caminhos e o custo total deles
 * Cria um vetor auxiliar chamado print_list onde vai sendo adicionado
 * cada nó e seu nó de origem até que chegue no nó 0
 * depois vai removendo do final e printando 
 * @param paths vetor de caminhos 
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