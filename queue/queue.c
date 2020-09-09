#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "queue.h" /* forward declaration */
#include "linked_list.h" /* forward declaration */

#ifndef NDEBUG
#define DEBUG_PRINT(s) fprintf(stderr, s)
#else
#define DEBUG_PRINT(s)
#endif

struct queue
{
	slist_t *list;
};/* queue_t*/


/**************************************************************************/
/*building a queue*/
queue_t *QCreate()
{
	queue_t *queue = NULL;
	
	queue = (queue_t*)malloc(sizeof(queue_t));
	if(NULL == queue)
	{
		DEBUG_PRINT("memory allocation failed\n");
	}
	
	/*combining to my slist function */
	queue->list = SListCreate();
	return queue;
}


/**************************************************************************/
void QDestroy(queue_t *queue)
{
	assert(queue);
	
	SListDestroy(queue->list);
	
	free(queue);
	queue = NULL;
}


/**************************************************************************/
/*pushing to back end of the queue. returns status*/
int QEnqueue(queue_t *queue, const void *data)
{
	sl_iterator_t it1;
	
	assert(queue);
	assert(data);
	
	it1 = SListInsertBefore(SListEnd(queue->list), data);
	
	/*if the function before failed the return value will remain the same 
	as the insertion */
	if(SListIterIsEqual(it1, SListEnd(queue->list)))
	{
		DEBUG_PRINT("memory allocation failed\n");  
		return 1;
	}
	return 0;
}



/**************************************************************************/
/*poping from queue begining*/
void Qdequeue(queue_t *queue)
{
	assert(queue);
	
	SListRemove(SListBegin(queue->list));
}



/**************************************************************************/
/*peeking at item at front of queue*/
void *QPeek(const queue_t *queue)
{
	assert(queue);
	assert(QIsEmpty(queue) != 1);
	
	return SListGetData(SListBegin(queue->list));
}






/**************************************************************************/
/*returns a status 1 if empty*/
int QIsEmpty(const queue_t *queue)
{
	size_t count = QCount(queue);
	
	assert(queue);

	/*if count = 0 return 1(yes) */
	return count==0 ? 1 : 0;
}


/*returns number of elements in the queue*/
/**************************************************************************/
size_t QCount(const queue_t *queue)
{
	assert(queue);
	
	return SListCount(queue->list);
}






