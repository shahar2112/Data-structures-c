/*
gd -I ../dlist -I ../sorted_list priQ.c priQ_test.c ../dlist/dlist.c ../sorted_list/slist.c 
*/

#include <stdio.h> /*printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /*assert */

#include "heap_PQ.h" /* forward decleration */
#include "heap.h" /*forward declarations */

#ifndef NDEBUG
#define DEBUG_PRINT(s) fprintf(stderr, s)
#else
#define DEBUG_PRINT(s)
#endif

struct priority_queue
{
	heap_t *heap;
}; 

/****************************************************************************/
/*building a Priority Queue*/
pr_queue_t *PQCreate(int (*CmpFunc)(void *data1, void *data2))
{
	pr_queue_t *pr_queue = NULL;
	
	pr_queue = (pr_queue_t*)malloc(sizeof(pr_queue_t));
	if(NULL == pr_queue)
	{
		DEBUG_PRINT("memory allocation failed\n");
		return NULL;
	}
	
	/*combining to my SORTlist func */
	pr_queue->heap = HeapCreate(CmpFunc);
		if(NULL == pr_queue->heap)
	{
		DEBUG_PRINT("memory allocation failed\n");
		free(pr_queue);
		return NULL;
	}
	
	return pr_queue;
}


/****************************************************************************/
void PQDestroy(pr_queue_t *pr_queue)
{
	/*if the list allocation succeeded destroy also list*/
	if(pr_queue->heap != NULL)
	{
		HeapDestroy(pr_queue->heap);
	}
	
	free(pr_queue);
	pr_queue = NULL;
}

/****************************************************************************/
/*pushing to the Queue, accoring to the priority. returns status*/
/*if the sortlist returns an iterator end so the function failed 
and status returned is 0 */
int PQEnqueue(pr_queue_t *pr_queue, const void *data)
{
	assert(pr_queue);

	return HeapPush(pr_queue->heap, (void *)data) == 0;
}


/****************************************************************************/
/*poping from front of Queue*/
void PQDequeue(pr_queue_t *pr_queue)
{
	assert(pr_queue);
	
	HeapPop(pr_queue->heap);
}

/***************************************************************************/
/*erase specific data using IsMatch function (Find & Remove)*/
void *PQErase(pr_queue_t *pr_queue, int(*IsMatch)(void *data, void *param1),void * param1)
{
	assert(pr_queue);
	
	return HeapRemove(pr_queue->heap, IsMatch, param1);
}

/***************************************************************************/
/*peeking at item at front of Priority Queue*/
void *PQPeek(const pr_queue_t *pr_queue)
{
	assert(pr_queue);
	
	return HeapPeek(pr_queue->heap);
}

/***************************************************************************/
/*returns a status, 1=empty 0=not*/
int PQIsEmpty(const pr_queue_t *pr_queue)
{
	assert(pr_queue);
	
	return HeapIsEmpty(pr_queue->heap);
}

/***************************************************************************/
/*returns number of elements in the Priority Queue*/
size_t PQCount(const pr_queue_t *pr_queue)
{
	assert(pr_queue);
	
	return HeapSize(pr_queue->heap);
}
	


