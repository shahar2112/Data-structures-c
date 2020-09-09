#include <stdio.h> /*printf */
#include <stdlib.h> /* exit */

#include "linked_list.h" /* forward decleration */



int main()
{
	slist_t *list = NULL;
	node_t *node = NULL;
	node_t *node2 = NULL;
	int num1 = 4, num2 = 6, num3 = 7 ;
	sl_iterator_t siterator_t;
	
	
	SListCreate();
	
	list = SListCreate();
	if(list == NULL)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}

	printf("end is %s \n", (char*)SListGetData(SListEnd(list)));
	printf("begining is %s \n", (char*)SListGetData(SListBegin(list)));
	printf("\nnumber of variables in the list is %ld \n", SListCount(list));
	

	
	siterator_t = SListInsertBefore(SListEnd(list), &num1);
	/*printf("end is %d \n", *(int*)SListGetData(siterator_t));
	printf("begining is %d \n\n", *(int*)SListGetData(SListBegin(list)));
	printf("next is %d \n\n",*(int*)SListGetData(SListIterNext(SListBegin(list))));*/
	
	
	
	/*siterator_t = SListInsertBefore(SListEnd(list), &num2);
	printf("end is %d \n", *(int*)SListGetData(siterator_t));

	
	printf("begining is %d \n", *(int*)SListGetData(SListBegin(list)));
	printf("next is %d \n\n",*(int*)SListGetData(SListIterNext(SListBegin(list))));
	
	
	siterator_t = SListInsertBefore(SListEnd(list), &num3);
	printf("end is %d \n", *(int*)SListGetData(siterator_t));
	printf("begining is %d \n", *(int*)SListGetData(SListBegin(list)));
	printf("next is %d \n\n",*(int*)SListGetData(SListIterNext(SListBegin(list))));


	siterator_t = SListInsertBefore(SListBegin(list), &num2);
	printf("begining is %d \n", *(int*)SListGetData(siterator_t));
	printf("next is %d \n\n",*(int*)SListGetData(SListIterNext(siterator_t)));
	

	printf("\nnumber of variables in the list is %ld \n", SListCount(list));
	
	SListRemove(SListBegin(list));
	printf("begining after remove is %d \n", *(int*)SListGetData(SListBegin(list)));
	printf("\nnumber of variables in the list is %ld \n", SListCount(list));
	SListRemove(SListBegin(list));
	printf("begining after scnd remove is %d \n", *(int*)SListGetData(SListBegin(list)));
	printf("\nnumber of variables in the list is %ld \n", SListCount(list));
	
	
	/*printf("next of end is %d \n\n",*(int*)SListGetData(SListIterNext(SListEnd(list))));*/
	/*SListRemove(SListEnd(list));
	printf("end after remove is %s \n", (char*)SListGetData(SListEnd(list)));*/
	
	
	
return 0;
}
