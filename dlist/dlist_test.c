#include <stdio.h> /*printf */
#include <stdlib.h> /* exit */
#include <string.h> /* strcmp */

#include "dlist.h" /* forward decleration */
iter_t ReturnEnd(iter_t iter);
int IsMatch(const void *data, void *param);
int Action(void *data, void *param);
void Printlist(iter_t iter, dlist_t *list) ;

int main()
{
	dlist_t *list = NULL;
	dlist_t *list2 = NULL;
	dlist_t *list3 = NULL;
	iter_t it;
	iter_t it_from;
	iter_t it_to;
	iter_t it_where;
	iter_t it_splice;
	int num_from = 3, num_to = 9, num_where = 66;
	int check = 0;
	size_t i;
	size_t count = 0;
	size_t arr1[] = {1,8,3,4,5,9};
	size_t arr2[] = {11,22,66,77,88};
	size_t size1 = sizeof(arr1)/sizeof(arr1[i]);
	size_t size2 = sizeof(arr2)/sizeof(arr2[i]);
	
	list = DListCreate();
	if(NULL == list)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}
	
	check = DListIsEmpty(list);
	printf("is list empty? 1=yes 0=no %d\n", check);

	count = DListCount(list);
	printf("the number of nodes is %ld\n\n", count);
	
	it = DListInsertBefore(DListEnd(list), "third");
	printf("the first node is: %s\n", (char*)DListGetData(it));
	
	check = DListIsEmpty(list);
	printf("is list empty? 1=yes 0=no %d\n", check);
	
	count = DListCount(list);
	printf("the number of nodes is %ld\n\n", count);
	
	it = DListInsertBefore(DListBegin(list), "second");
	printf("the second node is: %s\n", (char*)DListGetData(it));
	
	printf("\033[1;31m");
	printf("\nAll elements:\n");
	printf("\033[0m"); 
	for(i=0, it=DListBegin(list); i<DListCount(list); i++)
	{
		printf("in place %ld : %s\n ",i, (char*)DListGetData(it));
		it = DListIterNext(it);
	}
	
	
	count = DListCount(list);
	printf("the number of nodes is %ld\n\n", count);
	
	it = DListInsertBefore(DListBegin(list), "first");
	printf("the new first node is: %s\n", (char*)DListGetData(it));
	count = DListCount(list);
	printf("the number of nodes is %ld\n\n", count);
	
	it = DListInsertBefore(DListBegin(list), "hello");
	printf("the new first node is: %s\n", (char*)DListGetData(it));
	count = DListCount(list);
	printf("the number of nodes is %ld\n\n", count);
	
	it = DListFind(DListBegin(list), DListEnd(list), IsMatch, "first");
	it = DListInsertBefore(DListBegin(list), "hey");
	printf("the new first node is: %s\n", (char*)DListGetData(it));
	count = DListCount(list);
	printf("the number of nodes is %ld\n\n", count);
	
	printf("\033[1;31m");
	printf("\nAll elements:\n");
	printf("\033[0m"); 
	
	printf("the number of nodes is %ld\n\n", DListCount(list));
	for(i=0, it=DListBegin(list); i<DListCount(list); i++)
	{
		printf("in place %ld : %s\n ",i, (char*)DListGetData(it));
			 it = DListIterNext(it);
	}
	
	
	/*testing next */
	it = DListIterNext(DListBegin(list));
	printf("\nthe next node after begin is: %s\n", (char*)DListGetData(it));
	it = DListIterNext(it);
	printf("and the next is: %s\n", (char*)DListGetData(it) );
	printf("and the next is: %s\n\n", (char*)DListGetData( DListIterNext(it)));
	
	/*testing prev */
	it =DListIterPrev(it);
	printf("the previous node is: %s\n", (char*)DListGetData(it));
	it =DListIterPrev(it);
	printf("and the prev is: %s\n", (char*)DListGetData(it));
	printf("the number of nodes is %ld\n\n", count);
	
	/*testing push */
	it = DListPushFront(list, (char*)"new first");
	printf("the new first is: %s\n", (char*)DListGetData(it) );
	printf("the number of nodes is %ld\n\n", DListCount(list));
	
	it = DListPushBack(list, (char*)"new last");
	printf("the new last is: %s\n", (char*)DListGetData(it) );
	printf("the number of nodes is %ld\n\n", DListCount(list));

	printf("the poped data from begining is: %s\n", (char*)DListPopBack(list));
	printf("the number of nodes is %ld\n\n", DListCount(list));
	
	printf("the poped data from begining is: %s\n", (char*)DListPopFront(list));
	printf("the new begining is: %s\n", (char*)DListGetData(DListBegin(list)));
	printf("the number of nodes is %ld\n\n", DListCount(list));
	
	printf("\033[1;31m");
	printf("\nAll elements:\n");
	printf("\033[0m"); 
	
	printf("the number of nodes is %ld\n\n", DListCount(list));
	for(i=0, it=DListBegin(list); i<DListCount(list); i++)
	{
		printf("in place %ld : %s\n",i, (char*)DListGetData(it));
		 it = DListIterNext(it);
	}

	it = DListEnd(list);
	check = DListIterIsEqual(it, DListBegin(list));
	check == 1 ? printf("\nequal\n") : printf("\nnot equal\n");

	it = DListBegin(list);
	check = DListIterIsEqual(it, DListBegin(list));
	check == 1 ? printf("equal\n") : printf("not equal\n");
	
	it = DListRemove(DListBegin(list));
	printf("\nthe first node after removing begining is: %s\n", (char*)DListGetData(it));
	count = DListCount(list);
	printf("the number of nodes is %ld\n\n", count);
	
	
	Printlist(it, list) ; 

	printf("the number of nodes is %ld\n\n", DListCount(list));
	
	Printlist(it, list) ;
	
	printf("\n");
	it = DListFind(DListBegin(list), DListEnd(list), IsMatch, "second");
	if(DListIterIsEqual(it, DListEnd(list))== 1)
	{
		printf("data is not found\n");
	}
	else
	{
		printf("the found data is- %s\n", (char*)DListGetData(it));
	}

	
	it = DListFind(DListBegin(list), DListEnd(list), IsMatch, "first");
	if(DListIterIsEqual(it, DListEnd(list))== 1)
	{
		printf("data is not found\n");
	}
	else
	{
		printf("the found data is- %s\n\n", (char*)DListGetData(it));
	}
	
	/****testing for each**********/

	it = DListFind(DListBegin(list), DListEnd(list), IsMatch, "second");
	DListForEach(it, DListEnd(list), Action, "add\n");
	
	Printlist(it, list);

	
	DListDestroy(list);
	
/*	for(it = SListBegin(list), i=0; 
		!SListIterIsEqual(it, SlistEnd(list)); 
		it = SlistIterNext(it), i++)
	{
		printf("in place %ld : %s\n", i, (char *)SListGetData(it));
	}*/
	

/**************************testing split lists******************************/
/***************************************************************************/

	/**********creating + printing elements of first list************/
list2 = DListCreate();
	if(NULL == list2)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}
	

printf("\033[1;31m");
printf("\n\n\nAll elements of new first list:\n");
printf("\033[0m"); 
	for(i=0, it=DListBegin(list2); i<size1; i++)
	{
		it = DListInsertBefore(DListEnd(list2), &arr1[i]);
		printf("in place %ld : %d\n",i, *(int*)DListGetData(it));
		it = DListIterNext(it);
	}
	
	
	/**********creating + printing elements of first list************/
	list3 = DListCreate();
		if(NULL == list3)
		{
			printf("Error. Allocation was unsuccessful. \n");
			exit(1);
		}
		

	printf("\033[1;31m");
	printf("\n\n\nAll elements of new second list:\n");
	printf("\033[0m"); 
		for(i=0, it=DListBegin(list3); i<size2; i++)
		{
			it = DListInsertBefore(DListEnd(list3), &arr2[i]);
			printf("in place %ld : %d\n",i, *(int*)DListGetData(it));
			it = DListIterNext(it);
		}
	
	/********************testing it_splice******************/
	printf("\n\n");
	it_from = DListFind(DListBegin(list2), DListEnd(list2), IsMatch, &num_from);
	printf("it_from is %d\n", *(int*)DListGetData(it_from));
	it_to = DListFind(DListBegin(list2), DListEnd(list2), IsMatch, &num_to);
	printf("it_to is %d\n",  *(int*)DListGetData(it_to));
	it_where = DListFind(DListBegin(list3), DListEnd(list3), IsMatch, &num_where);
	printf("it_where is %d\n", *(int*)DListGetData(it_where));

	it_splice = DListSplice(it_where, it_from, it_to);

printf("\033[1;31m");
printf("\n\n\nAll elements of new second list:\n");
printf("\033[0m"); 
	for(i=0, it_splice=DListBegin(list3); i<size2+3; i++)
	{
		printf("in place %ld : %d\n",i, *(int*)DListGetData(it_splice));
		it_splice = DListIterNext(it_splice);
	}
	
	DListDestroy(list2);
	DListDestroy(list3);

return 0;
}

/***************************************************************************/
/*0 same or 1 if not */
int IsMatch(const void *data, void *param)
{
	return (strcmp((char*)data ,(char*)param) == 0);
}


/***************************************************************************/
int Action(void *data, void *param)
{
	printf("%s %s", (char*)data, (char*)param);

	return 0;
}

/**************************************************************************/
void Printlist(iter_t iter, dlist_t *list) 
{
	size_t i;
	
		printf("\033[1;31m");
		printf("\nAll elements:\n");
		printf("\033[0m"); 

	for(i=0, iter=DListBegin(list); i<DListCount(list); i++)
	{
	
		printf("in place %ld : %s\n ",i, (char*)DListGetData(iter));
		 iter = DListIterNext(iter);
	}
}


