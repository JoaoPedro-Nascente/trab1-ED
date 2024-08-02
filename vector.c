#include "vector.h"
#include <stdlib.h>
#include <string.h>

struct vector
{
    data_type *data;
    int size;
    int capacity;
};

Vector *vector_construct(int inittial_capacity)
{
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->data = (data_type *)malloc(inittial_capacity * sizeof(data_type));
    v->size = 0;
    v->capacity = inittial_capacity;
    return v;
}

void vector_destroy(Vector *v, void (*element_free)(void *))
{
    if (v != NULL)
    {
        vector_clear(v, element_free);

        free(v);
    }
}

void vector_push_back(Vector *v, data_type val)
{
    if (v->size == v->capacity)
    {
        v->capacity += 1;
        v->data = (data_type *)realloc(v->data, v->capacity * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size += 1;
}

int vector_size(Vector *v)
{
    return v->size;
}

data_type vector_get(Vector *v, int i)
{
    return v->data[i];
}

void vector_set(Vector *v, int i, data_type val)
{
    if (i >= v->capacity)
    {
        v->capacity = i;
        v->data = (data_type *)realloc(v->data, sizeof(data_type) * v->capacity);
    }

    if (v->data[i] == NULL)
        v->size += 1;

    v->data[i] = val;
}

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
}

data_type vector_remove(Vector *v, int i)
{
    data_type removed = v->data[i];
    for (int j = i; j < v->size - 1; j++)
    {
        v->data[j] = v->data[j + 1];
    }
    v->size -= 1;
    return removed;
}

data_type vector_pop_front(Vector *v)
{
    v->size -= 1;
    return vector_remove(v, 0);
}

data_type vector_pop_back(Vector *v)
{
    if (v->size > 0)
    {
        v->size -= 1;
        return vector_remove(v, v->size - 1);
    }
    return NULL;
}

void vector_insert(Vector *v, int i, data_type val)
{
    if (v->size == v->capacity)
    {
        v->capacity += 1;
        v->data = (data_type *)realloc(v->data, v->capacity * sizeof(data_type));
    }

    for (int j = v->size; j > i; j--)
    {
        v->data[j] = v->data[j - 1];
    }
    v->data[i] = val;
    v->size += 1;
}

void vector_swap(Vector *v, int i, int j)
{
    data_type aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

void vector_sort(Vector *v, int (*compare)(const void *, const void *))
{
    qsort(v->data, v->size, sizeof(data_type), compare);
}

int vector_binary_search(Vector *v, data_type val, int (*compare)(const void *, const void *))
{
    data_type *item = (data_type *)bsearch(&val, v->data, v->size, sizeof(data_type), compare);
    if (item)
    {
        return (int)(item - v->data);
    }
    return -1;
}

void vector_reverse(Vector *v)
{
    int left = 0;
    int right = v->size - 1;
    while (left < right)
    {
        vector_swap(v, left, right);
        left += 1;
        right -= 1;
    }
}

Vector *vector_copy(Vector *v)
{
    Vector *copy = vector_construct(v->size);
    copy->data = (data_type *)malloc(v->capacity * sizeof(data_type));
    memcpy(copy->data, v->data, v->size * sizeof(data_type));
    copy->size = v->size;
    copy->capacity = v->capacity;

    return copy;
}

void vector_clear(Vector *v, void (*element_free)(void *))
{
    for (int i = 0; i < v->size; i++)
    {
        if (v->data != NULL)
        {
            if (v->data[i] != NULL)
                element_free(v->data[i]);
        }
    }
    v->size = 0;
}