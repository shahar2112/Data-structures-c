/* gd -I ../dlist slist.c slist_test.c ../dlist/dlist.c */

#include <stdio.h> /*printf */
#include <stdlib.h> /* exit */
#include <string.h> /* strcmp */

#include "slist.h" /* forward decleration */
void Printlist(sort_iter_t iter, sortList_t *list) ;

int IsBefore(const void *, const void *,const void * param);
sort_iter_t SortListMerge(sortList_t *list, sortList_t *list2);

int main()
{
	sortList_t *list = NULL;
	sortList_t *list2 = NULL;
	sortList_t *list3 = NULL;
	sortList_t *list4 = NULL;
	int param = 0;
	int param2 = 1;
	int param3 = 2;
	size_t i = 0;
	int arr[] = {5, 2, 4, 7, 8, 2};
	int arr3[]= {1, 3, 4, 6, 20, 10};
	char arr2[] = {'A', 'C', 'X', 'Z', 'A', 'B', 'S'};
	/*char *arr2[] = {"A", "C", "X", "Z", "A", "B", "S"};*/
	size_t size = sizeof(arr)/sizeof(arr[i]);
	size_t size2 = sizeof(arr2)/sizeof(arr2[i]);
	size_t size3 = sizeof(arr3)/sizeof(arr3[i]);
	sort_iter_t iter;
	
	/*creating first list */
	list = SortListCreate(IsBefore, &param);
	if(NULL ==list)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}
	
	/*creating second list */
	list2 = SortListCreate(IsBefore, &param2);
	if(NULL ==list2)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}
	
	
	printf("is list empty? 1=yes, 0=no %d\n",SortListIsEmpty(list));
	printf("\nnumber of elements is: %ld\n", SortListCount(list));
	
	for(i=0, iter=SortListBegin(list); i<size; i++)
	{
		iter = SortListInsert(list, &arr[i]);
	}
	
	printf("\nfirst list (case 0):");
	Printlist(iter, list);
	printf("\n\nnumber of elements is: %ld", SortListCount(list));
	
	iter = SortListRemove(SortListBegin(list));
	
	printf("\nnumber of elements after remove is: %ld", SortListCount(list));
	
	printf("\n\nnew list after remove begin is:");
	Printlist(iter, list);
	 
	 
	for(i=0, iter=SortListBegin(list2); i<size; i++)
	{
		iter = SortListInsert(list2, &arr[i]);
	}
	
	
	printf("\n\nsecond list (case 1) is:");
	 Printlist(iter, list2);

	



printf("\n\n 4 list (case 1) is:");
	list4 = SortListCreate(IsBefore, &param);
	if(NULL ==list4)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}
	for(i=0, iter=SortListBegin(list4); i<size3; i++)
	{
		iter = SortListInsert(list4, &arr3[i]);
	}
	Printlist(iter, list4);

	
	iter = SortListMerge(list, list4);
	
	printf("\n\nafter merge:\n");
	Printlist(iter, list) ;
	
	

	/*creating third list */
	list3 = SortListCreate(IsBefore, &param3);
	if(NULL ==list3)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}

	for(i=0, iter=SortListBegin(list3); i<size2; i++)
	{
		iter = SortListInsert(list3, &arr2[i]);
	}

	printf("\n\nthird list (case 3) is:");
		
	for(i=0, iter=SortListBegin(list3); i<SortListCount(list3); i++)
	{
		printf("\033[1;31m");
		printf("\nin place %ld : %c",i, *(char *)SortListGetData(iter));
		iter = SortListIterNext(iter);
		printf("\033[0m");
	}
	printf("\n");

	SortListDestroy(list);
	SortListDestroy(list2);
	
		/*iter = SortListRemove(SortListIterNext(iter));
		printf("next iter is %d\n", *(int*)iter);*/
	
return 0;
}


/**************************************************************************/
int IsBefore(const void *data_list, const void *data_user ,const void * param)
{
	switch (*(int*)param)
	{
		case 0:  
			return *(int*)data_list < *(int*)data_user;
			break;
		case 1: 
			return *(int*)data_list > *(int*)data_user;
			break;
		case 2: 
			return *(char*)data_list < *(char*)data_user;
			/*return (0 > strcmp((char*)data_list, (char*)data_user));*/
			break;
		default : printf("choice other than 0, 1 and 2\n");
			break;
	}
	return 0;
}

/**************************************************************************/
void Printlist(sort_iter_t iter, sortList_t *list) 
{
	size_t i;
	
	for(i=0, iter=SortListBegin(list); i<SortListCount(list); i++)
	{
		printf("\033[1;31m");
		printf("\nin place %ld : %d",i, *(int*)SortListGetData(iter));
		iter = SortListIterNext(iter);
		printf("\033[0m"); 
	}
	
}




