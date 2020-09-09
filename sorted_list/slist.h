#ifndef __SORTLIST_H__ 
#define __SORTLIST_H__



#include "dlist.h" /*forward declarations */

typedef struct sort_list sortList_t; 

typedef struct Sort_iterator
{
	iter_t dl_iterator; /*iterator double.list*/
}sort_iter_t; 


sortList_t *SortListCreate(int (*IsBefore)(const void *, const void *,const void * param), const void *param);

void SortListDestroy(sortList_t *list);

/* add a node in according to IsBefore func, returns iterator to added node, returns end at fail*/
sort_iter_t SortListInsert(sortList_t *list, void *data);

/* remove a node in a specific place in the list, returns iterator to the next node */
sort_iter_t SortListRemove(sort_iter_t where);

/* returns a pointer to the desired data according to the inserted iterator */
void *SortListGetData(sort_iter_t current);

/* returns the number of nodes in the list */
size_t SortListCount(const sortList_t *list);

/* returns an iterator to param between iterator from and iterator to, according to match function */
sort_iter_t SortListFind(sort_iter_t from, sort_iter_t to, int (*IsMatch)(const void *, void *),void * param);

/* returns an iterator the beginning of the list */
sort_iter_t SortListBegin(const sortList_t *list);

/* returns an iterator the end of the list  */
sort_iter_t SortListEnd(const sortList_t *list);

/* returns iterator to the next node */
sort_iter_t SortListIterNext(sort_iter_t current);

/* returns iterator to the previous node */
sort_iter_t SortListIterPrev(sort_iter_t current);

/* check if 2 given iterators are equal */
int SortListIterIsEqual(sort_iter_t it1, sort_iter_t it2);

/* check if the list is empty */
int SortListIsEmpty(const sortList_t *list);

/* remove and return data from the front of list*/
void *SortListPopFront(sortList_t *list);

/* remove and return data from the end of list*/
void *SortListPopBack(sortList_t *list);

/* perform action between iterator from && to */
int SortListForEach(sort_iter_t from, sort_iter_t to, int (*Action)(void *, void *), void * param);

#endif

