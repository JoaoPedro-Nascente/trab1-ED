#include "stack.h"
#include "vector.h"

#include <stdlib.h>

#define INITTIAL_CAPACITY 10

struct stack
{
    Vector *data;
    int size;
    int capacity;
};

Stack *stack_construct()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));

    s->data = vector_construct(INITTIAL_CAPACITY);
    s->size = 0;
    s->capacity = INITTIAL_CAPACITY;
    return s;
}

void stack_destroy(Stack *s, void (*element_free)(void *))
{
    if (s != NULL)
    {
        vector_destroy(s->data, element_free);
        free(s);
    }
}

void stack_push(Stack *s, data_type element)
{
    if (s->size == s->capacity)
    {
        s->capacity += 1;
    }
    vector_push_back(s->data, element);
    s->size += 1;
}

data_type stack_pop(Stack *s)
{
    if (s->size > 0)
    {
        s->size -= 1;
        return vector_remove(s->data, s->size);
    }
    return NULL; // Retorna NULL se a pilha estiver vazia
}

data_type stack_peek(Stack *s)
{
    if (s->size > 0)
    {
        return vector_get(s->data, s->size-1);
    }
    return NULL; // Retorna NULL se a pilha estiver vazia
}

int stack_size(Stack *s)
{
    return s->size;
}

int stack_is_empty(Stack *s)
{
    return s->size == 0;
}