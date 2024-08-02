#ifndef _CIRCULAR_ARRAY_H_
#define _CIRCULAR_ARRAY_H_

#include "vector.h"

typedef void *data_type;

typedef struct circular_array CircularArray;

// Inicializa o array circular com uma capacidade inicial.
CircularArray *circular_array_construct();

// Libera os recursos alocados pelo array circular.
void circular_array_destroy(CircularArray *ca, void (*element_free)(void *));

// Adiciona um elemento ao final do array circular.
void circular_array_add(CircularArray *ca, data_type val, void (*element_free)(void *));

// Remove o primeiro elemento do array circular.
data_type circular_array_remove(CircularArray *ca);

// Retorna o número de elementos no array circular.
int circular_array_size(CircularArray *ca);

// Verifica se o array circular está vazio.
int circular_array_is_empty(CircularArray *ca);

// Aumenta a capacidade do array circular.
void circular_array_resize(CircularArray *ca, int new_capacity, void (*element_free)(void *));

#endif