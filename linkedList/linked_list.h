#ifndef __SLIST_H__ 
#define __SLIST_H__

#include <stddef.h>

typedef struct linked_list slist_t; 

typedef struct node_list node_t;

typedef struct sl_iterator
{
	node_t *curr;
	slist_t *list;
}sl_iterator_t; 

/* create a new linked list */
slist_t *SListCreate();

/* destory the linked list */
void SListDestroy(slist_t *list);

/* add a node in a specific place in the list  */
sl_iterator_t SListInsertBefore(sl_iterator_t where, const void *data);

/* remove a node in a specific place in the list, you can't remove from end */
sl_iterator_t SListRemove(sl_iterator_t where);

/* return a pointer to the desired data according to the inserted iterator 
  you can't GetData from the end  */
void *SListGetData(sl_iterator_t where);

/* return the number of nodes in the list */
size_t SListCount(const slist_t *list);

/* return an iterator to the desired data according to a given compare function
if it can't find data it returns the end  */
sl_iterator_t SListFind(sl_iterator_t start_point,
 int (*cmp_func)(const void *, void *) ,void * param);

/* return an iterator the begin of the list */
sl_iterator_t SListBegin(const slist_t *list);

/* return an iterator the end of the list */
sl_iterator_t SListEnd(const slist_t *list);

/* the function return iterator to the next node after "where" */
sl_iterator_t SListIterNext(sl_iterator_t where);

/* the function check if a given 2 iterators are equal */
int SListIterIsEqual(sl_iterator_t it1, sl_iterator_t it2);

#endif /* #ifndef __SLIST_H__ */
