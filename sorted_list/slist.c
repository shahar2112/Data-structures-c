/* gd -I ../dlist slist.c slist_test.c ../dlist/dlist.c */

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <stdio.h> 

#include "slist.h" /* forward declaration */

#ifndef NDEBUG
#define DEBUG_PRINT(s) fprintf(stderr, s)
#else
#define DEBUG_PRINT(s)
#endif


struct sort_list
{
	dlist_t *dlist;
	int (*IsBefore)(const void *, const void *,const void * param);
	const void *param;
};/* sortList_t */


sortList_t *SortListCreate(int (*IsBefore)(const void *, const void *,const void * param), const void *param)
{
	sortList_t *list = NULL;
	do
	{
		list = (sortList_t*)malloc(sizeof(sortList_t));
		if(NULL == list)
		{
			DEBUG_PRINT("memory allocation failed\n");
			break;
		}
		
		/*combining to my dlist func */
		list->dlist = DListCreate();
		
		if(list->dlist == NULL)
		{
			DEBUG_PRINT("memory allocation failed\n");
			SortListDestroy(list);
			break;
		}
		
		list->IsBefore = IsBefore;
		list->param = (void*)param;
	}while(0);
	
	return list;
}


/**************************************************************************/
void SortListDestroy(sortList_t *list)
{
	assert(list);
	
	if (list->dlist != NULL)
	{
		DListDestroy(list->dlist);
	}
	
	free(list);
	list = NULL;
}

/**************************************************************************/
/* add a node in according to IsBefore func, 
returns iterator to added node, returns end at fail*/
sort_iter_t SortListInsert(sortList_t *list, void *data)
{
	sort_iter_t iter = SortListEnd(list); /*initializing to null */
	
	assert(list && data);
	
	iter = SortListBegin(list);
	
	
	/* if the function isbefore true, continue to next, else insert before */
	/* if the list is empty you can't get data so insert*/
	/* calling the function, get data from my list, data for user, parameter for test */
	while (  (!SortListIterIsEqual(iter, SortListEnd(list))) && 
		     ((list->IsBefore)(SortListGetData(iter), data,list->param))  )
	{
		iter = SortListIterNext(iter);
	}
	
	iter.dl_iterator= DListInsertBefore(iter.dl_iterator, data);
		
	return iter;
}

/**************************************************************************/
/* remove a node in a specific place in the list, 
returns iterator to the next node */
sort_iter_t SortListRemove(sort_iter_t where)
{
	where.dl_iterator = DListRemove(where.dl_iterator);
	
	return where;
}


/**************************************************************************/
/* returns a pointer to the desired data according to the inserted iterator */
void *SortListGetData(sort_iter_t current)
{
	return DListGetData(current.dl_iterator);
}


/**************************************************************************/
/* returns the number of nodes in the list */
size_t SortListCount(const sortList_t *list)
{
	assert(list);
	
	return DListCount(list->dlist);
}


/**************************************************************************/
/* returns an iterator to param between iterator from and iterator to, 
according to match function */
sort_iter_t SortListFind(sort_iter_t from, sort_iter_t to, 
			int (*IsMatch)(const void *, void *),void * param)
{
	
	from.dl_iterator = DListFind(from.dl_iterator, to.dl_iterator, IsMatch, param);
	
	return from;
}


/**************************************************************************/
/* returns an iterator the beginning of the list */
sort_iter_t SortListBegin(const sortList_t *list)
{
	sort_iter_t siter = SortListEnd(list); /*initializing iter */
	
	assert(list);
	
	siter.dl_iterator = DListBegin(list->dlist);
	
	return siter;
}





/**************************************************************************/
/* returns an iterator the end of the list  */
sort_iter_t SortListEnd(const sortList_t *list)
{
	sort_iter_t siter;
	
	assert(list);
	
	siter.dl_iterator = DListEnd(list->dlist);
	
	return siter;
}


/**************************************************************************/
/* returns iterator to the next node */
sort_iter_t SortListIterNext(sort_iter_t current)
{
	sort_iter_t siter;
	
	siter.dl_iterator = DListIterNext(current.dl_iterator);

	return siter;
}


/**************************************************************************/
/* returns iterator to the previous node */
sort_iter_t SortListIterPrev(sort_iter_t current)
{
	sort_iter_t siter ;
	
	siter.dl_iterator = DListIterPrev(current.dl_iterator);

	return siter;
}


/**************************************************************************/
/* check if 2 given iterators are equal */
int SortListIterIsEqual(sort_iter_t it1, sort_iter_t it2)
{
	return DListIterIsEqual(it1.dl_iterator, it2.dl_iterator);

}

/**************************************************************************/
/* check if the list is empty */
int SortListIsEmpty(const sortList_t *list)
{
	assert(list);
	
	return DListIsEmpty(list->dlist);
}

/**************************************************************************/
/* remove and return data from the front of list*/
void *SortListPopFront(sortList_t *list)
{
	assert(list);
	
	return DListPopFront(list->dlist);
}

/**************************************************************************/
/* remove and return data from the end of list*/
void *SortListPopBack(sortList_t *list)
{
	assert(list);
	
	return DListPopBack(list->dlist);
}

/**************************************************************************/
/* perform action between iterator from && to */
int SortListForEach(sort_iter_t from, sort_iter_t to, int (*Action)(void *, void *),void * param)
{
	 DListForEach(from.dl_iterator, to.dl_iterator, Action, (void*)param);
	 
	 return 0;
}


/************************************************************************/
/*merge first list into second list */
sort_iter_t SortListMerge(sortList_t *list, sortList_t *list2)
{
	sort_iter_t iter2;
	sort_iter_t iter1;

	iter2 = SortListBegin(list2);
	iter1 = SortListBegin(list);

	while(!SortListIterIsEqual(iter2, SortListEnd(list2)))
	{
		SortListInsert(list, SortListGetData(iter2));
		iter2 = SortListIterNext(iter2);
	
	}
	SortListDestroy(list2);
return iter1;
}
