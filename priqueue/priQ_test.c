#include <stdio.h> /*printf */
#include <stdlib.h> /* exit */

#include "priQ.h" /* forward decleration */
#include "slist.h" /*forward declarations */

int CmpFunc(const void *iter, const void *data ,const void * param);
void Printlist(sort_iter_t iter, sortList_t *list);
int IsMatch(const void *data, void *param);
int IsMatch2(const void *list_data, void *param_from_user);

int main()
{
	int param = 0;
	int param2 = 50;
	pr_queue_t *pr_queue = NULL;
	int arr[] = {1,3,2,8, 3, 5};
	size_t i = 0;
	size_t size = sizeof(arr)/sizeof(arr[1]);
	
	pr_queue = PQCreate(CmpFunc, &param);
	if(NULL == pr_queue)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}

	printf("is the queue empty? (1=yes , 0=no) %d\n", PQIsEmpty(pr_queue));
	printf("number of elements in queue is: %ld \n", PQCount(pr_queue));
	

	for(i=0; i<size; i++)
	{
	printf("\033[1;31m");
		PQEnqueue(pr_queue, &arr[i]);
	printf("the first element is %d \n", *(int*)PQPeek(pr_queue));
	printf("\033[0m"); 
	}
	
	printf("is the queue empty? (1=yes , 0=no) %d\n", PQIsEmpty(pr_queue));
	printf("number of elements in queue is: %ld \n", PQCount(pr_queue));

	 PQDequeue(pr_queue);
	 
	 printf("the first element after dequeue is %d \n", *(int*)PQPeek(pr_queue));
	printf("number of elements in queue is: %ld \n", PQCount(pr_queue));
	
	
	PQErase(pr_queue, IsMatch, &param2);
	printf("number of elements in queue after erase is: %ld \n", PQCount(pr_queue));
	printf("the first element after dequeue is %d \n", *(int*)PQPeek(pr_queue));
	
	PQDestroy(pr_queue);

return 0;
}


/**************************************************************************/
int CmpFunc(const void *data_list, const void *data ,const void * param)
{
	if(*(int*)param == 1)
	{	/*if param is 1 so sort from small to big */
		return *(int*)data_list < *(int*)data;
	}
	else
	{	/*if param is different than 1 so sort from big to small */
		return  *(int*)data_list > *(int*)data;
	}

}

/**************************************************************************/
void Printlist(sort_iter_t iter, sortList_t *list) 
{
	size_t i;
	
	for(i=0, iter=SortListBegin(list); i<SortListCount(list); i++)
	{
		printf("\nin place %ld : %d",i, *(int*)SortListGetData(iter));
		iter = SortListIterNext(iter);
	}
}



/**************************************************************************/
/*returns 0 if match or 1 if not */
int IsMatch(const void *list_data, void *param_from_user)
{
	return (*(int*)param_from_user == (*(int*)list_data*10) ? 1 : 0);
}



