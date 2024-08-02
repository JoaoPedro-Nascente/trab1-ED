#include "min_heap.h"
#include "vector.h"

#include <stdlib.h>

#define INITTIAL_CAPACITY 10

struct minHeap
{
    Vector *data;
    int size;
    int capacity;
    int (*compare)(const void *, const void *);
};

static void swap(data_type *a, data_type *b)
{
    data_type temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(MinHeap *heap, int index)
{
    while (index > 0)
    {
        int parent_index = (index - 1) / 2;
        if (heap->compare(heap->data[index], heap->data[parent_index]) >= 0)
        {
            break;
        }
        swap(&heap->data[index], &heap->data[parent_index]);
        index = parent_index;
    }
}

static void heapify_down(MinHeap *heap, int index)
{
    while (index < heap->size)
    {
        int left_child_index = 2 * index + 1;
        int right_child_index = 2 * index + 2;
        int smallest_index = index;

        if (left_child_index < heap->size &&
            heap->compare(heap->data[left_child_index], heap->data[smallest_index]) < 0)
        {
            smallest_index = left_child_index;
        }

        if (right_child_index < heap->size &&
            heap->compare(heap->data[right_child_index], heap->data[smallest_index]) < 0)
        {
            smallest_index = right_child_index;
        }

        if (smallest_index == index)
        {
            break;
        }

        swap(&heap->data[index], &heap->data[smallest_index]);
        index = smallest_index;
    }
}

MinHeap *min_heap_construct(int (*compare)(const void *, const void *))
{
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->data = vector_construct(INITTIAL_CAPACITY);
    heap->size = 0;
    heap->capacity = INITTIAL_CAPACITY;
    heap->compare = compare;
    return heap;
}

void min_heap_destroy(MinHeap *heap, void (*element_free)(void *))
{
    if (heap != NULL)
    {
        vector_destroy(heap->data, element_free);
        free(heap);
    }
}

void min_heap_insert(MinHeap *heap, data_type element)
{
    if (heap->size == heap->capacity)
    {
        heap->capacity += 1;
    }
    vector_push_back(heap->data, element);
    heapify_up(heap, heap->size);
    heap->size += 1;
}

data_type min_heap_extract_min(MinHeap *heap)
{
    if (heap->size == 0)
    {
        return NULL; // Retorna NULL se a heap estiver vazia
    }
    data_type min_element = vector_remove(heap->data, 0);
    vector_swap(heap, 0, heap->size - 1);
    heap->size -= 1;
    heapify_down(heap, 0);
    return min_element;
}

data_type min_heap_peek_min(MinHeap *heap)
{
    if (heap->size == 0)
    {
        return NULL; // Retorna NULL se a heap estiver vazia
    }
    return vector_get(heap->data, 0);
}

int min_heap_size(MinHeap *heap)
{
    return heap->size;
}

int min_heap_is_empty(MinHeap *heap)
{
    return heap->size == 0;
}