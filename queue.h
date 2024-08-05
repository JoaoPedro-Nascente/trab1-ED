#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef void *data_type;

typedef struct queue Queue;

// Aloca e inicializa uma nova fila.
Queue *queue_construct();

// Libera todos os recursos alocados pela fila.
void queue_destroy(void *q);

// Insere um elemento no fim da fila.
void queue_enqueue(Queue *q, data_type element);

// Remove e retorna o elemento na frente da fila.
data_type queue_dequeue(Queue *q);

// Retorna o elemento na frente da fila sem removê-lo.
data_type queue_peek(Queue *q);

// Retorna o número de elementos atualmente na fila.
int queue_size(Queue *q);

// Verifica se a fila está vazia.
int queue_is_empty(Queue *q);

#endif