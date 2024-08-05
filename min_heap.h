#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_

typedef void *data_type;

typedef struct minHeap MinHeap;

// Aloca e inicializa uma nova heap com capacidade inicial.
MinHeap *min_heap_construct(int (*compare)(const void *, const void *));

// Libera todos os recursos alocados pela heap.
void min_heap_destroy(void *heap);

// Insere um elemento na heap.
void min_heap_insert(MinHeap *heap, data_type element);

// Remove e retorna o menor elemento da heap.
data_type min_heap_extract_min(MinHeap *heap);

// Retorna o menor elemento da heap sem removê-lo.
data_type min_heap_peek_min(MinHeap *heap);

// Retorna o número de elementos na heap.
int min_heap_size(MinHeap *heap);

// Verifica se a heap está vazia.
int min_heap_is_empty(MinHeap *heap);

#endif