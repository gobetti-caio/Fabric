#ifndef _PATH_H_
#define _PATH_H_

#include "problem.h"
#include "vector.h"


// Cria o vetor de caminhos com tamanho = quantidade de nós
Vector *paths_construct(int size);

// Libera a memória de vetor de caminhos e seu conteúdo
void paths_destroy(Vector *p);

// Printa os caminhos 
void paths_print(Vector *paths);


#endif
