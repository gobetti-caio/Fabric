#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

struct Vector
{
    data_type *data;
    int size;
    int allocated;
};


static const int VECTOR_INIT_SIZE = 10;
static const int VECTOR_GROWTH_RATE = 2;

Vector *vector_construct()
{
    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    v->allocated = VECTOR_INIT_SIZE;
    v->size = 0;
    v->data = (data_type *)calloc(VECTOR_INIT_SIZE, sizeof(data_type));
    return v;
};

void vector_destroy(Vector *v)
{
    free(v->data);
    free(v);
};

void vector_push_back(Vector *v, data_type val)
{
    if (v->size >= v->allocated)
    {
        v->allocated *= VECTOR_GROWTH_RATE;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    };

    v->data[v->size] = val;
    v->size++;
};

int vector_size(Vector *v)
{
    return v->size;
};

data_type vector_get(Vector *v, int i)
{
    if (v->allocated >= i && i >= 0)
    {
        return v->data[i];
    }
    else
    {
        printf("O indice nao e valido");
        exit(0);
    };
};

void vector_set(Vector *v, int i, data_type val)
{
    if (v->allocated >= i && i >= 0)
    {
        v->data[i] = val;
    }
    else
    {
        printf("O indice nao e valido");
    };
};

int vector_find(Vector *v, data_type val)
{
    for (int i = 0; i < v->size; i++)
    {
        if (v->data[i] == val)
        {
            return i;
        }
    }
    return -1;
};

data_type vector_remove(Vector *v, int i)
{
    data_type elementoRemovido = v->data[i];
    for (int j = i; j < v->size; j++)
    {
        v->data[j] = v->data[j + 1];
    };
    v->size--;
    return elementoRemovido;
};

data_type vector_pop_front(Vector *v)
{
    return vector_remove(v, 0);
};