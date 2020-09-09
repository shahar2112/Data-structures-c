#ifndef __HEAP_H__ 
#define __HEAP_H__

#include <stddef.h> /*size_t*/

typedef struct heap heap_t;

/* Create a new heap. O(1) */
heap_t *HeapCreate(int (*cmp_func)(void *data1, void *data2));

/* Destroy the heap. O(1) */
void HeapDestroy(heap_t *heap);

/* O(log(n)) */
int HeapPush(heap_t *heap, void *data);

/*  O(log(n)) */
void HeapPop(heap_t *heap);

/* O(1) */
void *HeapPeek(heap_t *heap);

/* O(n) */
size_t HeapSize(heap_t *heap);

/* O(n) */
int HeapIsEmpty(heap_t *heap);

/* O(n) */
void *HeapRemove(heap_t *heap, int (*IsMatch)(void * data, void *param), void *data);

#endif