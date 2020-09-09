#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /*printf */

#include "linked_list.h" /* forward decleration */

struct linked_list
{
	node_t *head; /* holds pointer to struct type node (head) */
	node_t *end; /* holds pointer to struct type node (end) */
	size_t count;
}; 

struct node_list
{
	void *data;
	node_t *next;
}; 

/****************************************************************************/
/* create a new linked list */
slist_t *SListCreate()
{
	slist_t *list = NULL;
	node_t *last = NULL; /*dummy end node */
	
	list = (slist_t*)malloc(sizeof(slist_t));
	if(NULL == list)
	{
		fprintf(stderr, "allocation failed\n");
		return NULL;
	}
	last = (node_t*)malloc(sizeof(node_t));
	if(NULL == last)
	{
		fprintf(stderr, "allocation failed\n");
		free(list);
		list = NULL;
		return NULL;
	}
	
	last->data = NULL;  /*data of our dummy will contain the list */
	last->next = NULL; 
	
	list->head = last; /* inserting last dummy node to head */
	list->end = last; /* inserting last dummy node to end */
	list->count = 0;


	return list;
}



/****************************************************************************/
/* destory the linked list */
void SListDestroy(slist_t *list)
{
	node_t *to_free;
	
	assert(list);
	
	while(list->head != NULL)
	{
		to_free = list->head;
		list->head = list->head->next;
		free(to_free);
		to_free = NULL;
	}

	free(list);
	list = NULL;
}



/****************************************************************************/
/* return an iterator the begin of the list */
sl_iterator_t SListBegin(const slist_t *list)
{
	sl_iterator_t it;
	
	assert(list);
	/*assert(list->head->next);*/
	
	it.curr = list->head; /*returns pointer to head */
	it.list = (slist_t*)list;
	
	return it ;
}



/****************************************************************************/
/* return an iterator the end of the list */
sl_iterator_t SListEnd(const slist_t *list)
{
	sl_iterator_t it;
	
	assert(list);
	
	it.curr = list->end; /*returns pointer to end */
	it.list = (slist_t*)list;
	
	return it;
}


/****************************************************************************/
/* the function return iterator to the next node after "where" */
sl_iterator_t SListIterNext(sl_iterator_t where)
{
	assert(where.list->count > 0);
	
	if(where.curr->next == NULL)
	{
		return where;
	}
	
	where.curr = where.curr->next;
	
	return where;
}






/****************************************************************************/
/* return a pointer to the desired data according to the inserted iterator */
void *SListGetData(sl_iterator_t where)
{
	assert(where.curr->next != NULL);

	return where.curr->data;
}



/****************************************************************************/
/* add a node in a specific place in the list  */
sl_iterator_t SListInsertBefore(sl_iterator_t where, const void *data)
{
	node_t *new_node = NULL;
	
	assert(data);
	
	/*creating new node */
	new_node = (node_t*)malloc(sizeof(node_t));
	if(new_node == NULL)
	{
		fprintf(stderr, "allocation failed\n");
		return where;
	}
	
	new_node->data = where.curr->data; /*new node data equal to where node data */
	new_node->next = where.curr->next; /*new node next is whers next */
	where.curr->data = (void*)data; /*previouse node has value of new data */
	where.curr->next = new_node;  /* where is pointing to new node */
	
	/*insert at the end - updating end */
	if(new_node->next == NULL)
	{
		where.list->end = new_node;
	}
	
	/* add one for count */
	where.list->count +=1;
		
return where;
	
}


/****************************************************************************/
/* return the number of nodes in the list */
size_t SListCount(const slist_t *list)
{
	assert(list);
	
	return list->count;
}


/****************************************************************************/
/* remove a node in a specific place in the list */
sl_iterator_t SListRemove(sl_iterator_t where)
{
	node_t *to_free = NULL;
	
	assert(where.list->count > 0);
	assert(where.curr->next != NULL);
	
	to_free = where.curr->next;

	/*update the end*/
	/*if there is only one node left in the list so change pointers and free it */
	if(where.curr->next == where.list->end)
	{
		where.list->head = where.list->end;
		free(where.curr);
		where.curr = where.list->head;
		(where.list->count) -=1;
		
		return where;
	}
	
	/*else change the current node data to next->next node and free the next node */
	where.curr->data = where.curr->next->data;
	where.curr->next = where.curr->next->next;
	(where.list->count) -=1;
	
	free(to_free);
	to_free = NULL;
	
	return where;
}


/****************************************************************************/
/* return an iterator to the desired data according to a given compare function */
sl_iterator_t SListFind(sl_iterator_t start_point, 
	int (*cmp_func)(const void *, void *) ,void * param)
{
	
	while(1 != (cmp_func(start_point.curr->data, param)) &&
		 (start_point.curr->next != NULL))
	{
		start_point.curr = start_point.curr->next;
	}

	return start_point;
}



/****************************************************************************/
/* the function check if a given 2 iterators are equal */
int SListIterIsEqual(sl_iterator_t it1, sl_iterator_t it2)
{
	/* 1 for true 0 */
	return (it1.curr == it2.curr) ;
}



