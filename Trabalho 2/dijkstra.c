#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"
#include "path.h"

/**
Função que identifica qual dos vizinhos do nó analizado
ja foram adicionados ao path para assim determinar
quais ainda são possiveis caminhos a serem analizados
   @param paths - vetor com o caminho ja construido
 * @param possible_paths vetor de nós que talvez possam ser visitados
 * @param source valor do nó de origem
 */

/* Recebe os lugares ja adicionados no path, os possiveis luga res a serem visitados e o index do local atual
controi um vetor para guardar os vizinhos, checa se os possiveis locais a serem visitados são vizinhos
do local atual e se ja foram adionados no path, em caso positivo e negatibo respectivamente o lugar
analisado é adicionado como vizinho e é retornardo para ser adicionado na heap */ 

Vector *find_neighbors(Vector *paths, Vector *possible_paths, int prev) //check
{
    Vector *neighbors = vector_construct();
    int size = vector_size(possible_paths);

    for (int i = 0; i < size; i++)
    {
        PossiblePaths *aux = vector_get(possible_paths, i);
        PossiblePaths *was_visited = vector_get(paths, aux->index);

        if (aux->previous == prev && was_visited->origin_distance == 0 &&was_visited->index != 0)
        {
            vector_push_back(neighbors, aux);
        }
    }

    return neighbors;
}

/**
Checa se todos os caminhos do path ja foram cosntruidos
 * @param paths vetor de visitados
 */
bool visited_check(Vector *paths) // check
{
    int size = vector_size(paths);
    PossiblePaths *pp;

    for (int i = 0; i < size; i++)
    {
        pp = vector_get(paths, i);
        if (pp->index == 0)
        {
            return false;
        }
        else if (pp->origin_distance == 0)
        {
            return false;
        }
    }
    return true;
};


void update_path(Vector *paths, PossiblePaths *node_removed) // check
{
    // Taking advantage of the index of the vector we update the infomrmation of each node
    PossiblePaths *node_path;
    node_path = vector_get(paths, node_removed->index);
    node_path->previous = node_removed->previous;
    node_path->previous_distance = node_removed->previous_distance;
    node_path->origin_distance = node_removed->origin_distance;
}


/* 
Recebe o nó removido, o caminho ja construido, o problem e a heap
caminho ja construidoe o problemm são usados no find neigbors
e a heap é para receber os vizinhos

Serve pra pegar os vizinhos do nó que acabara de ser adicionado ao path e coloca-los na heap além de atualizar
seus valores de distancia até a origem
 */

void update_heap(PossiblePaths *node_removed, Vector *paths, Problem *p, Heap *not_visited) // check
{
    Vector *neighbors = find_neighbors(paths, p->possible_paths_nodes, node_removed->index);
    PossiblePaths *pn;
    int node_removed_cost;
    for (int i = 0; i < vector_size(neighbors); i++)
    {
        node_removed_cost = node_removed->origin_distance;
        pn = vector_get(neighbors, i);
        pn->origin_distance = pn->previous_distance + node_removed_cost;
        heap_push(not_visited, pn, pn->origin_distance);
    }
    vector_destroy(neighbors);
}

Vector *solve_dijkstra(Problem *problem)// check
{
    Problem *p = problem;
    Vector *paths = paths_construct(p->size);
    Heap *not_visited = heap_construct();

    PossiblePaths *node_removed;
    PossiblePaths *origin = possible_paths_construct(0, 0, 0); // nó de origem

    heap_push(not_visited, origin, origin->origin_distance); // consertar a heap

    while (visited_check(paths) == false || heap_empty(not_visited) == false) // check
    {
        node_removed = heap_pop(not_visited); // check 

        if (vector_get(paths, node_removed->index) == 0 || vector_get(paths, node_removed->origin_distance) == 0) // check
        {
            void update_path(paths, node_removed); // check

            void update_heap(node_removed, paths, p, not_visited); //check
        }
    };

    heap_destroy(not_visited);
    free(origin);

    return paths;
};