#include "queue.h"
#include "vector.h"

#include <stdlib.h>

#define INITTIAL_CAPACITY 10

struct queue
{
    Vector *data;
    int front;
    int rear;
    int size;
    int capacity;
};

Queue *queue_construct()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));

    q->data = vector_construct(INITTIAL_CAPACITY);
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = INITTIAL_CAPACITY;
    return q;
}

void queue_destroy(Queue *q, void (*element_free)(void *))
{
    if (q != NULL)
    {
        if (q->data != NULL)
            vector_destroy(q->data, element_free);
        free(q);
    }
}

void queue_enqueue(Queue *q, data_type element, void (*element_free)(void *))
{
    if (q->size == q->capacity)
    {
        q->capacity += 1;
        Vector *v = vector_construct(q->capacity);
        for (int i = 0; i < q->size; i++)
        {
            vector_push_back(v, vector_get(q->data, (q->front + i) % q->capacity / 2));
        }

        vector_destroy(q->data, element_free);
        q->data = v;
        q->front = 0;
        q->rear = q->size - 1;
    }
    q->rear = (q->rear + 1) % q->capacity;
    vector_push_back(q->data, element);
    q->size += 1;
}

data_type queue_dequeue(Queue *q)
{
    if (q->size == 0)
    {
        return NULL; // Retorna NULL se a fila estiver vazia
    }
    data_type removed = vector_remove(q->data, q->front);
    q->front = (q->front + 1) % q->capacity;
    q->size -= 1;
    return removed;
}

data_type queue_peek(Queue *q)
{
    if (q->size == 0)
    {
        return NULL; // Retorna NULL se a fila estiver vazia
    }
    return vector_get(q->data, q->front);
}

int queue_size(Queue *q)
{
    return q->size;
}

int queue_is_empty(Queue *q)
{
    return q->size == 0;
}