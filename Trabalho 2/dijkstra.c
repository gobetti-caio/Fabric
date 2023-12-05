#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"
#include "path.h"


/**
function that identifies wich ones of the
neighbors of a node have been alredy visited
then return the ones that havent
   @param paths - path with the nodes modified/not modified
 * @param possible_paths - vector with all the nodes analyzed (problem in this case)
 * @param prev - node analyzed
 */

Vector *find_neighbors(Vector *paths, Vector *possible_paths, int prev) 
{
    Vector *neighbors = vector_construct();
    int size = vector_size(possible_paths);

    for (int i = 0; i < size; i++)
    {
        PossiblePaths *aux = vector_get(possible_paths, i);
        PossiblePaths *was_visited = vector_get(paths, aux->index);

        if (aux->previous == prev && was_visited->origin_distance == 0 && was_visited->index != 0)
        {
            vector_push_back(neighbors, aux);
        }
    }

    return neighbors;
}


/**
analyzed if the path has already been completelly build
 * @param paths vector of the path
 */
bool visited_check(Vector *paths)
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


/** function that update the valor of the nodes that 
havent been visited with his actual values
* @param paths  - vector of the path
* @param node_removed - node to be uptaded
*/

void update_path(Vector *paths, PossiblePaths *node_removed) 
{
    // Taking advantage of the index of the vector we update the infomrmation of each node
    PossiblePaths *node_path;
    node_path = vector_get(paths, node_removed->index);
    node_path->previous = node_removed->previous;
    node_path->previous_distance = node_removed->previous_distance;
    node_path->origin_distance = node_removed->origin_distance;
}


/**
inserts in the heap the neighbors of the last updated node
*@param node_removed - last updated node
*@param paths - vector path
*@param p - vector problem to be used in find_neighbors 
*@param not_visited - heap that will recive the neighbors
*/

void update_heap(PossiblePaths *node_removed, Vector *paths, Problem *p, Heap *not_visited) 
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


Vector *solve_dijkstra(Problem *problem)
{
    Problem *p = problem;
    Vector *paths = paths_construct(p->size);
    Heap *not_visited = heap_construct();

    PossiblePaths *node_removed;
    PossiblePaths *origin = possible_paths_construct(0, 0, 0); 

    heap_push(not_visited, origin, origin->origin_distance); 

    while (visited_check(paths) == false || heap_empty(not_visited) == false) 
    {
        node_removed = heap_pop(not_visited);  
        int i = node_removed->index;
        PossiblePaths *analyzed = vector_get(paths, i);

        if (node_removed->index == 0 || analyzed->origin_distance == 0) 
        {
            void update_path(paths, node_removed); 

            void update_heap(node_removed, paths, p, not_visited); 
        }
    };

    heap_destroy(not_visited);
    free(origin);

    return paths;
};



/**
 * ___________________________________________________________________________
 * Algorithm explanation:

In theory we recevi the  *@param p with all the nodes that 
we will use to construct that path.

we  make a push of a node that represents the origin then enters
in a while that will only end when or the function visited_check
returns true or when the heap with the nodes analyzed is empty 
what implys that all the nodes had already been updated and we have 
the shortedt path of  each spot

we use the heap pop to obtain the shortest path in it and use a 
condiotional to check if the node obtained had not been updated yet
in negative cade we return to the beginning of the while, in negative
case we updated the path with the node and then updated the heap with 
it neighbors

the loop continues until one of the conditions come out as true and then
destroy the heap and the @param origin created earlier to avoid
memory leak
_____________________________________________________________________________

It seems to exist some problem on the logic of the condiotional
inisde of the loop

*/
