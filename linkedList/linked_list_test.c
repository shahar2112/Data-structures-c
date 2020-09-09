#include <stdio.h> /*printf */
#include <stdlib.h> /* exit */
#include <string.h> /* strcmp */

#include "linked_list.h" /* forward decleration */

int StrCmp(const void *data, void *param);
int IntCmp(const void *data, void *param);

int main()
{
	slist_t *list = NULL;
	int num1 = 3, num2 = 5, num3 = 10 , num4=6;
	int nums[]={4,6,7,8,9};
	int is_equal = 0;
	int i=0;
	int size = sizeof(nums)/sizeof(nums[i]);
	sl_iterator_t it1;
	sl_iterator_t it2;
	
	
	list = SListCreate();
	if(list == NULL)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}

	
	printf("\nall the list is: \n");
	for(i = 0; i < size; i++)
	{
		it1 = SListInsertBefore(SListEnd(list), &(nums[i]));
		printf("in place %d : %d\n", i, *(int*)SListGetData(it1));
		it1 = SListIterNext(it1);
	}
	printf("\nnumber of variables in the list is %ld \n", SListCount(list));

	it1 = SListInsertBefore(SListBegin(list), &num1);
	printf("\nbegining is %d \n", *(int*)SListGetData(it1));
	printf("next is %d \n\n",*(int*)SListGetData(SListIterNext(it1)));
	
	it1 = SListFind(SListBegin(list), IntCmp, &num4);
	
	printf("find: %d\n", *(int*)SListGetData(it1));
	it1 = SListInsertBefore(it1, &num2);
	
	it1 = SListInsertBefore(SListEnd(list), &num3);
	printf("end is %d \n", *(int*)SListGetData(it1));
	printf("begining is %d \n\n", *(int*)SListGetData(SListBegin(list)));
	printf("next is %d \n\n",*(int*)SListGetData(SListIterNext(SListBegin(list))));

	
	printf("\nall the list is: \n");
	for(it2 = SListBegin(list), i=0; 
		!SListIterIsEqual(it2, SListEnd(list)); 
		it2 = SListIterNext(it2), i++)
	{
		printf("in place %d : %d\n", i, *(int*)SListGetData(it2));
	}
	
	printf("\nnumber of variables in the list is %ld \n", SListCount(list));
	
	SListRemove(SListBegin(list));
	printf("\nbegining after remove first is %d", *(int*)SListGetData(SListBegin(list)));
	printf("\nnumber of variables in the list is %ld \n", SListCount(list));
	SListRemove(SListBegin(list));
	printf("\nbegining after scnd remove is %d", *(int*)SListGetData(SListBegin(list)));
	printf("\nnumber of variables in the list is %ld \n", SListCount(list));
	
	
	printf("\nall the list after 2 removes is: \n");
	for(it2 = SListBegin(list), i=0; 
		!SListIterIsEqual(it2, SListEnd(list)); 
		it2 = SListIterNext(it2), i++)
	{
		printf("in place %d : %d\n", i, *(int*)SListGetData(it2));
	}
	
	it1 = SListEnd(list);
	is_equal = SListIterIsEqual(it1, SListBegin(list));
	is_equal == 1 ? printf("\nequal\n") :  printf("\nnot equal\n");

	it1 = SListBegin(list);
	is_equal = SListIterIsEqual(it1, SListBegin(list));
	is_equal == 1 ? printf("equal\n") :  printf("not equal\n");
	
	
	it2 = SListFind(SListBegin(list), IntCmp, &num3);
	if(it2.curr == NULL)
	{
		printf("the data is not found\n");
	}
	else
	{
		printf("\nthe found data is : %d\n", *(int*)SListGetData(it2));
	}
	
SListDestroy(list);


return 0;
}

	
/* 1 same, 0 not */
int IntCmp(const void *data, void *param)
{
	return (*(int*)data == *(int*)param);
}



/* 0 same, 1 not 
int StrCmp(const void *data, void *param)
{
	return strcmp((char *)data, (char *)param);
}*/
	/*	
	siterator_t = SListFind(siterator_t, StrCmp, "Insert 2");
	if(siterator_t.pre == NULL && siterator_t.curr == NULL)
	{
		printf("\nThe data is not in the list\n");
	}*/


