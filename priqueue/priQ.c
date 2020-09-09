/*
gd -I ../dlist -I ../sorted_list priQ.c priQ_test.c ../dlist/dlist.c ../sorted_list/slist.c 
*/

#include <stdio.h> /*printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /*assert */

#include "priQ.h" /* forward decleration */
#include "slist.h" /*forward declarations */

#ifndef NDEBUG
#define DEBUG_PRINT(s) fprintf(stderr, s)
#else
#define DEBUG_PRINT(s)
#endif

struct priority_queue
{
	sortList_t *sortlist;

}; /*pr_queue_t*/

/****************************************************************************/
/*building a Priority Queue*/
pr_queue_t *PQCreate(int (*CmpFunc)(const void *data1, const void *data2 ,const void *param),void * param)
{
	pr_queue_t *pr_queue = NULL;
	
	pr_queue = (pr_queue_t*)malloc(sizeof(pr_queue_t));
	if(NULL == pr_queue)
	{
		DEBUG_PRINT("memory allocation failed\n");
		return NULL;
	}
	
	/*combining to my SORTlist func */
	pr_queue->sortlist = SortListCreate(CmpFunc, param);
		if(NULL == pr_queue->sortlist)
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
	if(pr_queue->sortlist != NULL)
	{
		SortListDestroy(pr_queue->sortlist);
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
	sort_iter_t iter;
	int status = 1;
	
	assert(pr_queue);
	
	/*return (SortListIterIsEqual(iter , SortListEnd(pr_queue->sortlist))? 0 : 1);*/
	
	iter = SortListInsert(pr_queue->sortlist, (void *)data);
	
	/*if the iter returned is end - function failed */
	if(SortListIterIsEqual(iter , SortListEnd(pr_queue->sortlist))==1)
	{	
		status = 0;
	}
	return status;
	
	/*	return !SortListIterIsEqual(iter , SortListEnd(pr_queue->sortlist)); */
}


/****************************************************************************/
/*poping from front of Queue*/
void PQDequeue(pr_queue_t *pr_queue)
{
	assert(pr_queue);
	
	SortListPopFront(pr_queue->sortlist);
}

/***************************************************************************/
/*erase specific data using IsMatch function (Find & Remove)*/
void *PQErase(pr_queue_t *pr_queue, int(*IsMatch)(const void *data, void *param1),void * param1)
{
	sort_iter_t iter;
	void* data = NULL;
	
	assert(pr_queue);
		
	iter = (SortListFind(SortListBegin(pr_queue->sortlist),
			 SortListEnd(pr_queue->sortlist), 
			 IsMatch, param1));
	
	data = SortListGetData(iter);
	
	SortListRemove(iter);
	
	return data;
}

/***************************************************************************/
/*peeking at item at front of Priority Queue*/
void *PQPeek(const pr_queue_t *pr_queue)
{
	assert(pr_queue);
	
	return SortListGetData(SortListBegin(pr_queue->sortlist));
}

/***************************************************************************/
/*returns a status, 1=empty 0=not*/
int PQIsEmpty(const pr_queue_t *pr_queue)
{
	assert(pr_queue);
	
	return SortListIsEmpty(pr_queue->sortlist);
}

/***************************************************************************/
/*returns number of elements in the Priority Queue*/
size_t PQCount(const pr_queue_t *pr_queue)
{
	assert(pr_queue);
	
	return SortListCount(pr_queue->sortlist);
}
	


