#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */


/*forward declarations */
#include "vector.h"

struct vector
{
	void **items; /* the items themselves */
	size_t size; /* how many elements are occupied */
	size_t capacity; /* how many memory is allocated */
};

/* create dynamic vector */
vector_t *VectorCreate(size_t capacity)
{
	vector_t *vector_handle = NULL;

	vector_handle = (vector_t*)malloc(sizeof(vector_t));
	vector_handle->items = NULL;
	vector_handle->items = malloc(capacity * sizeof(void *));
	if(vector_handle == NULL || vector_handle->items == NULL)
	{
		return NULL;
	}

	vector_handle->size = 0;
	vector_handle->capacity = capacity; 
	
	return vector_handle;
}




/* destory the vector */
void VectorDestroy(vector_t *vector_handle)
{
	assert(vector_handle);
	
	free(vector_handle->items);
	vector_handle->items = NULL;
	
	free(vector_handle);
	vector_handle = NULL;
}



/* reserve space (update capacity) */
int VectorReserve(vector_t *vector_handle, size_t capacity)
{
	assert(vector_handle);
	
	vector_handle->capacity += capacity;
	
	vector_handle->items =
	realloc(vector_handle->items, vector_handle->capacity + capacity*(sizeof(void *)));
	
	return NULL == vector_handle->items ? 1 : 0;
}



/* return address at index 'index' */
void *VectorGetItem(const vector_t *vector_handle, size_t index)
{
	assert(vector_handle);
 	assert(index <= vector_handle->size-1);
	
	return *(vector_handle->items + index);
}



/* push 'element' in the end */
int VectorPushBack(vector_t *vector_handle, const void *element)
{
	assert(vector_handle && element);
	
	/* if capacity is full, reallocate more space */
	if((vector_handle->capacity) == (vector_handle->size))
	{
	/* increase capacity by 2 */
		vector_handle->items =
		(void *)realloc(vector_handle->items,
		(2 *vector_handle->capacity*sizeof(void *)));
		if(NULL == vector_handle->items)
		{
		return 1;
		}
		vector_handle->capacity *= 2;
	}
		
	VectorSetItem(vector_handle, vector_handle->size, element);

	vector_handle->size += 1;
	
	return 0;
}


void VectorSetItem(const vector_t *vector, size_t index, const void *element)
{
	assert(vector);

	*(vector->items + index) = (void *)element;
}



/* return size of vector */
size_t VectorSize(const vector_t *vector_handle)
{
	assert(vector_handle);
	
	return vector_handle->size;
}


/* return capacity of vector */
size_t VectorCapacity(const vector_t *vector_handle)
{
	assert(vector_handle);
	
	return vector_handle->capacity;
}



/* pop 'element' from the end */
void VectorPopBack(vector_t *vector_handle)
{
	assert(vector_handle);
	
	
	vector_handle->size = vector_handle->size - 1;
	
	/* if size is 25% from capacity, devide capacity by two */
	if(vector_handle->size == (vector_handle->capacity)/4)
	{
		vector_handle->capacity /= 2;
		
		vector_handle->items =
		realloc(vector_handle->items,
		(vector_handle->capacity)*(sizeof(void *)));
	}

}




/* resize vector (update size) */
void VectorResize(vector_t *vector_handle, size_t size)
{
	assert(vector_handle);
	assert(size <= vector_handle->capacity);
	
	vector_handle->size = size;

	return;
}
