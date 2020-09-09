#include <stddef.h> /* size_t */

#ifndef __VECTOR_H__ /* INCLUDE GUARD (guard is activated) for "vector.h" */
#define __VECTOR_H__

typedef struct vector vector_t; 

/* create dynamic vector */
vector_t *VectorCreate(size_t capacity);

/* destory the vector */
void VectorDestroy(vector_t *vector_handle);

/* return address at index 'index' */
void *VectorGetItem(const vector_t *vector_handle, size_t index);

void VectorSetItem(const vector_t *vector, size_t index, const void *element);

/* push 'element' in the end */
int VectorPushBack(vector_t *vector_handle, const void *element);

/* pop 'element' from the end */
void VectorPopBack(vector_t *vector_handle);

/* return size of vector */
size_t VectorSize(const vector_t *vector_handle);

/* return capacity of vector */
size_t VectorCapacity(const vector_t *vector_handle);

/* reserve space (update capacity) */
int VectorReserve(vector_t *vector_handle, size_t capacity);

/* resize vector (update size) */
void VectorResize(vector_t *vector_handle, size_t size);

#endif /* #ifndef __VECTOR_H__ */

