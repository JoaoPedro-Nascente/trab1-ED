#include "queue.h"
#include "circular_array.h"

#include <stdlib.h>

#define INITIAL_CAPACITY 10

struct queue
{
    CircularArray *data;
    int size;
    int capacity;
};

Queue *queue_construct()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));

    q->data = circular_array_construct(INITIAL_CAPACITY);
    q->size = 0;
    q->capacity = INITIAL_CAPACITY;
    return q;
}

void queue_destroy(void *q)
{
    Queue *queue = (Queue *)q;
    if (queue != NULL)
    {
        if (queue->data != NULL)
            circular_array_destroy(queue->data, NULL);
        free(q);
    }
}

void queue_enqueue(Queue *q, data_type element)
{
    if (q->size == q->capacity)
    {
        circular_array_resize(q->data, q->capacity * 2, NULL);
        q->capacity *= 2;
    }
    circular_array_add(q->data, element, NULL);
    q->size += 1;
}

data_type queue_dequeue(Queue *q)
{
    if (q->size > 0)
    {
        q->size -= 1;
        return circular_array_remove(q->data);
    }
    return NULL; // Retorna NULL se a fila estiver vazia
}

data_type queue_peek(Queue *q)
{
    if (q->size > 0)
    {
        return circular_array_remove(q->data);
    }
    return NULL; // Retorna NULL se a fila estiver vazia
}

int queue_size(Queue *q)
{
    return q->size;
}

int queue_is_empty(Queue *q)
{
    return q->size == 0;
}