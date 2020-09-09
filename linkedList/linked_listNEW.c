#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /*printf */

#include "linked_list.h" /* forward decleration */

struct linked_list
{
	node_t *head; /* holds pointer to struct type node (head) */
	size_t count;
}; /*slist_t */

/*
typedef struct sl_iterator
{
	node_t *curr;
	slist_t *list;
}siterator_t; 
*/

struct node_list
{
	void *data;
	node_t *next;
}; /* node_t */


/* create a new linked list */
slist_t *SListCreate()
{
	slist_t *list = NULL;
	node_t *first = NULL; /*dummy head node */
	
	/*CHECK IF IT IS OK ALL MALLOCS CHECKING TOGETHER */
	list = (slist_t*)malloc(sizeof(slist_t));
	first = (node_t*)malloc(sizeof(node_t));
	if(NULL == list || NULL == first)
	{
		fprintf(stderr, "allocation failed\n");
		return NULL;
	}
	
	list->head = first; /* inserting first dummy node to head */
	first->data = "first";  /*data of our dummy will contain the list */
	first->next = NULL; 
	
	list->count = 0;

	return list;
}




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
	free(to_free);
	to_free = NULL;
	free(List);
	list = NULL;
}




/* return an iterator the begin of the list */
sl_iterator_t SListBegin(const slist_t *list)
{
	sl_iterator_t siterator_t;
	
	assert(list);
	
	siterator_t.pre = list->head; /*dummy head node */
	siterator_t.curr = list->head->next; /* returns pointer to head */
	
	return siterator_t;
}




/* return an iterator the end of the list */
sl_iterator_t SListEnd(const slist_t *list)
{
	sl_iterator_t siterator_t;
	
	assert(list);
	

	siterator_t.list = (slist_t*)list;
	
	return siterator_t;
}


/* the function return iterator to the next node after "where" */
sl_iterator_t SListIterNext(sl_iterator_t where)
{
	(assert(where.list->count > 0));
	
	where.pre = where.curr;
	
	if(where.curr == NULL)
	{
		return where;
	}	
	
	where.curr = where.curr->next;
	
	return where;
}







/* return a pointer to the desired data according to the inserted iterator */
void *SListGetData(sl_iterator_t where)
{
	if(where.curr == NULL)
	{
		return where.pre->data;
	}	
	return where.curr->data;
}



/* add a node in a specific place in the list  */
sl_iterator_t SListInsertBefore(sl_iterator_t where, const void *data)
{
	node_t *new_node = NULL;
	sl_iterator_t it = {NULL, NULL};
	void *temp_data;
	
	assert(data);

	/*creating new node */
	new_node = (node_t*)malloc(sizeof(node_t));
	if(new_node == NULL)
	{
		fprintf(stderr, "allocation failed\n");
		return where;
	}
	
	
	if(where.curr == NULL) /* insert before end */
	{
		memcpy(&new_node->data, &data, sizeof(void *));
		where.prev->next = new_node;
		new_node->next = NULL;
		where.curr = new_node;
		
	}
	else /* not before end */
	{
		/*printf("insert where prev: %s\n", (char *)where.prev->data);
		printf("insert where curr: %s\n", (char *)where.curr->data);	*/
		
		temp_data = where.curr->data;
		
		/*printf("temp data: %s\n", (char *)temp_data);*/
				
		memcpy(&where.curr->data, &data, sizeof(void *));
		new_node->data = temp_data;
		new_node->next = where.curr->next;
		where.curr->next = new_node;
	}

	it.curr= where.curr;
	it.prev = where.prev;
	
where.list->count +=1;
	
return where;
	
}


/* return the number of nodes in the list */
size_t SListCount(const slist_t *list)
{
	assert(list);
	
	return list->count;
}



sl_iterator_t SListRemove(sl_iterator_t where)
{
	sl_iterator_t siterator_t;
	
	where.pre->next = where.curr->next;
	
	free(where.curr);
	where.curr = NULL;
	
	siterator_t.pre = where.pre;
	siterator_t.curr = siterator_t.pre->next;
	
	return where;
}


