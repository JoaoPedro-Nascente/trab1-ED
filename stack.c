#include "stack.h"
#include "circular_array.h"

#include <stdlib.h>

#define INITIAL_CAPACITY 10

struct stack
{
    CircularArray *data;
    int size;
    int capacity;
};

Stack *stack_construct()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));

    s->data = circular_array_construct(INITIAL_CAPACITY);
    s->size = 0;
    s->capacity = INITIAL_CAPACITY;
    return s;
}

void stack_destroy(void *s)
{
    Stack *stack = (Stack *)s;
    if (stack != NULL)
    {
        if (stack->data != NULL)
            circular_array_destroy(stack->data, NULL);
        free(stack);
    }
}

void stack_push(Stack *s, data_type element)
{
    if (s->size == s->capacity)
    {
        circular_array_resize(s->data, s->capacity * 2, NULL);
        s->capacity *= 2;
    }
    circular_array_add(s->data, element, NULL);
    s->size += 1;
}

data_type stack_pop(Stack *s)
{
    if (s->size > 0)
    {
        s->size -= 1;
        return circular_array_remove(s->data);
    }
    return NULL; // Retorna NULL se a pilha estiver vazia
}

data_type stack_peek(Stack *s)
{
    if (s->size > 0)
    {
        return circular_array_remove(s->data);
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