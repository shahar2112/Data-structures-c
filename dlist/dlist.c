#include <stdio.h> /*printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /*assert */

#include "dlist.h" /* forward decleration */

#ifndef NDEBUG
#define DEBUG_PRINT(s) fprintf(stderr, s)
#else
#define DEBUG_PRINT(s)
#endif

static iter_t ReturnEnd(iter_t iter);

struct node
{
	void *data;
	node_t *next;
	node_t *prev;
}; 


struct linked_list
{
	node_t head; /*  node head */
	node_t end; /* node end */
}; 

/****************************************************************************/
/* create a new linked list */
dlist_t *DListCreate(void)
{
	dlist_t *list = NULL;
	
	list = (dlist_t*)malloc(sizeof(dlist_t));
	if(NULL == list)
	{
		DEBUG_PRINT("memory allocation failed\n");
		return NULL;
	}
	
	/*defining the head data node */
	list->head.data = "head";
	list->head.prev = NULL;
	list->head.next = &list->end;
	
	/*defining the end data node */
	list->end.data = "end";
	list->end.next = NULL;
	list->end.prev = &list->head;
	
	return list;
}


/****************************************************************************/
void DListDestroy(dlist_t *list)
{
	node_t *to_free = NULL;
	
	assert(list);
	
	while(list->head.next != &(list->end))
	{
		to_free = list->head.next;
		list->head.next = list->head.next->next;
		free(to_free);
		to_free = NULL;
	}
	
	free(list);
	list = NULL;
}


/****************************************************************************/
/* add a node in a specific place in the list, returns iterator to added node,
 returns end at fail, complexity ??? */
iter_t DListInsertBefore(iter_t where, void *data)
{
	node_t *new_node = NULL;
	
	assert(data);
	
	/*creating new node*/
	new_node = (node_t*)malloc(sizeof(node_t));
	if(NULL == new_node)
	{
		DEBUG_PRINT("memory allocation failed\n");
		return ReturnEnd(where);
	}
	
	new_node->data = (void*)data;
	new_node->next = where.curr;
	new_node->prev = where.curr->prev;
	
	where.curr->prev = new_node;
	new_node->prev->next = new_node;
	where.curr = new_node;
	
	return where;
}



/****************************************************************************/
/* remove a node in a specific place in the list, returns iterator to the next node */
iter_t DListRemove(iter_t where)
{
	node_t *to_free = NULL;
	
	/* you can't remove when list is empty */
	assert(where.curr->next != NULL);
	
	to_free = where.curr;
	
	where.curr->prev->next = where.curr->next;
	where.curr->next->prev = where.curr->prev;
	where.curr = where.curr->next;
	
	free(to_free);
	to_free = NULL;
	
	return where;
}


/****************************************************************************/
/* returns an iterator the beginning of the list */
iter_t DListBegin(const dlist_t *list)
{
	iter_t it;
	
	assert(list);
	
	it.curr = list->head.next;
	
	return it;
}


/****************************************************************************/
/* return a pointer to the desired data according to the inserted iterator */
void *DListGetData(iter_t current)
{
	assert(current.curr->next != NULL); /*you can't get dummy end*/
	
	return current.curr->data; 
}


/****************************************************************************/
/* returns an iterator the end of the list  */
iter_t DListEnd(const dlist_t *list)
{
	iter_t it;
	
	assert(list);
	
	it.curr = (node_t*)&list->end;
	
	return it;
}

/****************************************************************************/
/* returns iterator to the next node */
iter_t DListIterNext(iter_t current)
{
	/*you cant previous end */
	if(current.curr->next != NULL)
	{
	 	current.curr = current.curr->next;	
	}
	 
	return current;
}

/****************************************************************************/
/* returns iterator to the previous node */
iter_t DListIterPrev(iter_t current)
{
	/*you cant previous head */
	if(current.curr->prev->prev != NULL)
	{
		current.curr = current.curr->prev;	
	}

	return current;
}


/***************************************************************************/
/* returns the number of nodes in the list */
size_t DListCount(const dlist_t *list)
{
	size_t count=0;
	
	node_t *count_node = NULL;
	
	assert(list);
	
	/* creating a pointer node to first node with data*/
	count_node = (node_t*)&list->head ;
	
	while(count_node->next->next != NULL )
	{
		count++;
		count_node = count_node->next ;
	}

	return count;
}


/***************************************************************************/
/* returns an iterator to param between iterator from and iterator to, according to match function */
iter_t DListFind(iter_t from, iter_t to, 
int (*IsMatch)(const void *, void *),void * param)
{

	while(!DListIterIsEqual(from, to))
	{
		if(IsMatch(from.curr->data, param) == 1)
		{
			break;
		}
		from = DListIterNext(from);
	}
	if (DListIterIsEqual(from, to))
	{
		from = ReturnEnd(from);
 	}
	return from;
}


/****************************************************************************/
/* check if 2 given iterators are equal if yes 1 else 0*/
int DListIterIsEqual(iter_t it1, iter_t it2)
{
	return (it1.curr == it2.curr);
}



/****************************************************************************/
/* check if the list is empty */
int DListIsEmpty(const dlist_t *list)
{
	assert(list);
	
	return DListCount(list) == 0;
}

/****************************************************************************/
/* add a node to the front of the list*/
iter_t DListPushFront(dlist_t *list, void *data)
{
	assert(list);
	assert(data);
	
	DListInsertBefore(DListBegin(list), data);
	
	return DListBegin(list);
}

/****************************************************************************/
/* add a node to the end of the list*/
iter_t DListPushBack(dlist_t *list, void *data)
{
	iter_t it = DListEnd(list); /* initializing it */
	
	assert(list);
	assert(data);
	
	it = DListInsertBefore(DListEnd(list), data);
	
	return it;
}

/****************************************************************************/
/* remove and return data from the front of list*/
void *DListPopFront(dlist_t *list)
{
	void *data = NULL;
	iter_t it = DListEnd(list); /* initializing it */
	
	assert(list);
	
	it = DListBegin(list); /*iterator to the first data node */
	data = it.curr->data;
	
	DListRemove(it);
	
	return data;
}



/****************************************************************************/
/* remove and return data from the end of list*/
void *DListPopBack(dlist_t *list)
{
	void *data = NULL;
	iter_t it = DListEnd(list); /* initializing it */
	
	assert(list);
	assert(DListCount(list) > 0);
	
	it = DListEnd(list);
	it.curr = it.curr->prev; /*iterator to the last data node */
	data = it.curr->data;
	
	DListRemove(it);
	
	return data;
}

/***************************************************************************/
/* receive iter and return dummy end*/
static iter_t ReturnEnd(iter_t iter)
{
	while(iter.curr->next != NULL)
	{
		iter.curr = iter.curr->next;
	}
	return iter;
}


/***************************************************************************/
/* perform action on nodes data from "from" to "to" */
int DListForEach(iter_t from, iter_t to, int (*Action)(void *, void *), void * param)
{
	
	while(!DListIterIsEqual(from, to)) /*(from.curr != to.curr)*/
	{
		Action(from.curr->data, param);
		from = DListIterNext(from); /*from.curr = from.curr->next;*/
	}
	return 0;

}


/***************************************************************************/
/* remove nodes from 1 list, in range from-to (not including to)
    and insert them in where */
iter_t DListSplice(iter_t dest_where, iter_t src_from, iter_t src_to)
{
	iter_t iter;
	
	iter.curr = dest_where.curr->prev;
	iter.curr->next = src_from.curr; /* first the next of node before where will be from */
	src_from.curr->prev->next = src_to.curr;/* connect prev from to to */
	src_to.curr->prev->next = dest_where.curr;/* connect prev of to to where */
	
	dest_where.curr->prev = src_to.curr->prev; /*connect where to prev to */
	src_to.curr->prev = src_from.curr->prev;/* connect prev to to from */
	src_from.curr->prev = iter.curr;
	
	return iter;
}

