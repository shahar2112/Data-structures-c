#ifndef __DLIST_H__ 
#define __DLIST_H__

#include <stddef.h> /* for size_t */

typedef struct linked_list dlist_t; 
typedef struct node node_t;

typedef struct dl_iterator
{
	node_t *curr;
}iter_t; 


dlist_t *DListCreate(void);

void DListDestroy(dlist_t *list);

/* add a node in a specific place in the list, returns iterator to added node, returns end at fail, complexity */
iter_t DListInsertBefore(iter_t where, void *data);

/* remove a node in a specific place in the list, returns iterator to the next node */
iter_t DListRemove(iter_t where);

/* returns a pointer to the desired data according to the inserted iterator */
void *DListGetData(iter_t current);

/* returns the number of nodes in the list */
size_t DListCount(const dlist_t *list);

/* returns an iterator to param between iterator from and iterator to, according to match function  if it can't find it returns the end*/
iter_t DListFind(iter_t from, iter_t to, int (*IsMatch)(const void *, void *),void * param);

/* returns an iterator the beginning of the list */
iter_t DListBegin(const dlist_t *list);

/* returns an iterator the end of the list  */
iter_t DListEnd(const dlist_t *list);

/* returns iterator to the next node */
iter_t DListIterNext(iter_t current);

/* returns iterator to the previous node */
iter_t DListIterPrev(iter_t current);

/* check if 2 given iterators are equal */
int DListIterIsEqual(iter_t it1, iter_t it2);

/* check if the list is empty */
int DListIsEmpty(const dlist_t *list);

/* add a node to the front of the list*/
iter_t DListPushFront(dlist_t *list, void *data);

/* add a node to the end of the list*/
iter_t DListPushBack(dlist_t *list, void *data);

/* remove and return data from the front of list*/
void *DListPopFront(dlist_t *list);

/* remove and return data from the end of list*/
void *DListPopBack(dlist_t *list);

/* perform action on nodes from "from" to "to" */
int DListForEach(iter_t from, iter_t to, int (*Action)(void *, void *), void * param);

/* remove nodes from 1 list, in range from-to (not including to) and insert them in where */
iter_t DListSplice(iter_t dest_where, iter_t src_from, iter_t src_to);

#endif


