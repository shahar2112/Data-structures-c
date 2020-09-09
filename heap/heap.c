#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprsize_tf */

#include "heap.h"
#include "vector.h"

static void heapifyUp(heap_t *heap);
static size_t getCurrIndex(heap_t *heap);
static size_t getParentIndex(size_t child_index);
static int HasParent(size_t index);
static void Swap(heap_t *heap, size_t parent_index, size_t child_index);
static int hasLeftChild(size_t parent_index, heap_t *heap);
static size_t getMinChildIndex(heap_t *heap, size_t parent_index);
static void heapifyDown(heap_t *heap);
static int hasRightChild(size_t parent_index, heap_t *heap);
static size_t heapFind(heap_t *heap, int (*IsMatch)(void * data, void *param), void *data);

struct heap
{
	vector_t *vector;
	int (*cmp_func)(void *data1, void *data2);
}; 

/* Create a new heap. O(1) */
/******************** create ************************/
heap_t *HeapCreate(int (*cmp_func)(void *data1, void *data2))
{
	heap_t *heap = NULL;

	heap = (heap_t*)malloc(sizeof(heap_t));
	if (NULL == heap)
	{
		fprintf(stderr, "allocation failed\n");
		return NULL;
	}

	heap->vector = VectorCreate(1);
	if (NULL == heap->vector)
	{
		fprintf(stderr, "allocation failed\n");
		free(heap);
		heap = NULL;
		return NULL;
	}
 
	heap->cmp_func = cmp_func;

	return 	heap;
}

/* Destroy the heap. O(1) */
/******************** destroy ************************/
void HeapDestroy(heap_t *heap)
{
	assert(heap);

	VectorDestroy(heap->vector);

	free(heap);
	heap = NULL;
}


/* O(log(n)) */
/******************** push ************************/
int HeapPush(heap_t *heap, void *data)
{
	assert(heap);

	if(VectorPushBack(heap->vector, data))
	{
		return 1;
	}
	
	heapifyUp(heap);

	return 0;
}


/*  O(log(n)) */
/******************** pop ************************/
void HeapPop(heap_t *heap)
{
	assert(heap);
	
	if(HeapSize(heap) == 1)
	{
		VectorPopBack(heap->vector);
		return;
	}

	VectorSetItem(heap->vector, 0, VectorGetItem(heap->vector, getCurrIndex(heap)));
	
	VectorPopBack(heap->vector);

	heapifyDown(heap);
}


/* O(log(n)) */
/******************** push ************************/
void *HeapPeek(heap_t *heap)
{
	return VectorGetItem(heap->vector, 0);
}


/******************** size ************************/
/* O(n) */
size_t HeapSize(heap_t *heap)
{
	return VectorSize(heap->vector);
}


/* O(n) */
/******************** remove ************************/
void *HeapRemove(heap_t *heap, int (*IsMatch)(void * data, void *param), void *data)
{
    size_t to_remove_index = 0;
    void *to_return = NULL;
    size_t parent_index = 0;

    assert(heap);

	parent_index = getParentIndex(to_remove_index);
    to_remove_index = heapFind(heap, IsMatch, data);

    if(to_remove_index != -1)
    {
        to_return = VectorGetItem(heap->vector, to_remove_index);
        Swap(heap, to_remove_index, getCurrIndex(heap));

        if(((heap->cmp_func(to_return, VectorGetItem(heap->vector, parent_index)) > 0)
          && HasParent(to_remove_index)) || to_remove_index == 0)
        {
            heapifyDown(heap);
        }
        else
        {
            heapifyUp(heap);
        }
        VectorPopBack(heap->vector);
    }
    return to_return;
}

/* O(n) */
/******************** isEmpty ************************/
int HeapIsEmpty(heap_t *heap)
{
	return VectorSize(heap->vector) == 0;
}


/******************** UtilityFuncs ************************/
static void heapifyUp(heap_t *heap)
{
	size_t curr_index =  getCurrIndex(heap);
	size_t parent_index = getParentIndex(curr_index);

	while(HasParent(curr_index) && 
	heap->cmp_func(VectorGetItem(heap->vector, curr_index) , VectorGetItem(heap->vector, parent_index)) < 0)
	{
		Swap(heap , parent_index, curr_index);
		curr_index = parent_index;
		parent_index = getParentIndex(curr_index);
	}

}



static void heapifyDown(heap_t *heap)
{
	size_t parent_index = 0;
	size_t min_child_index = 0;

	while(hasLeftChild(parent_index, heap))
	{	
		min_child_index = parent_index*2 + 1;
		if(hasRightChild(parent_index, heap))
		{
			min_child_index = getMinChildIndex(heap, parent_index);
		}

		if(heap->cmp_func(VectorGetItem(heap->vector, min_child_index),
		 VectorGetItem(heap->vector, parent_index)) < 0)
		{
			Swap(heap, parent_index, min_child_index);
			parent_index = min_child_index;
		}
		else
		{
			break;
		}
		
	}
}



static void Swap(heap_t *heap, size_t parent_index, size_t child_index)
{
	void *parent = NULL;
	void *child = NULL;

	parent = VectorGetItem(heap->vector, parent_index);
	child = VectorGetItem(heap->vector, child_index);
	VectorSetItem(heap->vector, child_index, parent);
	VectorSetItem(heap->vector, parent_index, child);
}



static size_t getCurrIndex(heap_t *heap)
{
	return VectorSize(heap->vector) -1;
}


static size_t getParentIndex(size_t child_index)
{
	if(child_index%2 == 0 && (child_index > 0))
	{
		return (child_index -2)/2;
	}
	else if(child_index%2 != 0 && (child_index > 0))
	{
		return (child_index -1)/2;
	}
	return 0;
}




static int HasParent(size_t index)
{
	return index != 0;
}



static size_t getMinChildIndex(heap_t *heap, size_t parent_index)
{
	size_t left_child = 0;
	size_t right_child = 0;

	left_child = parent_index*2 + 1;
	right_child = parent_index*2 + 2;

	if(heap->cmp_func(VectorGetItem(heap->vector, left_child) ,
	 VectorGetItem(heap->vector, right_child)) < 0)
	{
		return left_child;
	}
	else
	{
		return right_child;
	}
}



static int hasLeftChild(size_t parent_index, heap_t *heap)
{
	size_t left_child = 0;

	left_child = parent_index*2 + 1;

	if(left_child  <= getCurrIndex(heap))
	{
		return 1;
	}
	return 0;
}


static int hasRightChild(size_t parent_index, heap_t *heap)
{
	size_t right_child = 0;

	right_child = parent_index*2 + 2;

	if(right_child <= getCurrIndex(heap))
	{
		return 1;
	}
	return 0;
}

static size_t heapFind(heap_t *heap, int (*IsMatch)(void * data, void *param), void *data)
{
    size_t index = 0;

	for(index = 0 ; index < HeapSize(heap); index++)
	{
		if(IsMatch(VectorGetItem(heap->vector, index), data))
		{
			return index;
		}
	}

	return -1;
}
