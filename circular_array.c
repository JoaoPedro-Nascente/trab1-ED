#include "circular_array.h"

#include <stdlib.h>

#define INITIAL_CAPACITY 5

struct circular_array
{
    Vector *data;
    int start;
    int end;
    int size;
    int capacity;
};

CircularArray *circular_array_construct()
{
    CircularArray *ca = (CircularArray *)malloc(sizeof(CircularArray));

    ca->data = vector_construct(INITIAL_CAPACITY);
    if (ca->data == NULL)
    {
        free(ca);
        return NULL; // Falha na alocação
    }
    ca->start = 0;
    ca->end = 0;
    ca->size = 0;
    ca->capacity = INITIAL_CAPACITY;
    return ca;
}

void circular_array_destroy(CircularArray *ca, void (*element_free)(void *))
{
    if (ca != NULL)
    {
        if (ca->data != NULL)
        {
            vector_destroy(ca->data, NULL);
        }
        free(ca);
    }
}

void circular_array_add(CircularArray *ca, data_type val, void (*element_free)(void *))
{
    if (ca->size == ca->capacity)
    {
        circular_array_resize(ca, ca->capacity + 1, element_free);
    }
    ca->end = (ca->start + ca->size) % ca->capacity;
    vector_push_back(ca->data, val);
    ca->size++;
}

data_type circular_array_remove(CircularArray *ca)
{
    data_type removed = vector_get(ca->data, ca->start);
    ca->start = (ca->start + 1) % ca->capacity;
    ca->size -= 1;

    return removed;
}

int circular_array_size(CircularArray *ca)
{
    return ca->size;
}

int circular_array_is_empty(CircularArray *ca)
{
    return ca->size == 0;
}

void circular_array_resize(CircularArray *ca, int new_capacity, void (*element_free)(void *))
{
    Vector *v = vector_construct(new_capacity);

    for (int i = 0; i < ca->size; i++)
    {
        vector_push_back(v, vector_get(v, (ca->start + i) % ca->capacity));
    }
    
    vector_destroy(ca->data, element_free);
    ca->data = v;
    ca->start = 0;
    ca->end = ca->size;
    ca->capacity = new_capacity;
}