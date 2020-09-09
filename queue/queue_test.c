#include <stdio.h> /*printf */

#include "queue.h" /* forward declaration */
#include "linked_list.h" /* forward declaration */

int main()
{
	queue_t *queue= NULL;
	int num1 = 3, num2 = 4, num3 =5;

	
	queue = QCreate();
	
	QEnqueue(queue, &num1);
	printf("the first number is: %d \n", *(int*)QPeek(queue));
	printf("the number of elements in the list: %ld\n", QCount(queue));
	
	Qdequeue(queue);
	printf("the number of elements in the list after Qdequeue: %ld\n", QCount(queue));
		
	QEnqueue(queue, &num2);
	printf("the number of elements in the list after QEnqueue: %ld\n", QCount(queue));
	printf("the first number is: %d \n", *(int*)QPeek(queue));

	QEnqueue(queue, &num3);
	printf("the first number is: %d \n", *(int*)QPeek(queue));
	printf("the number of elements in the list after QEnqueue: %ld\n", QCount(queue));
	
	Qdequeue(queue);
	printf("the first number is: %d \n", *(int*)QPeek(queue));
	printf("the number of elements in the list after Qdequeue: %ld\n", QCount(queue));
		
	Qdequeue(queue);
	printf("the number of elements in the list after Qdequeue: %ld\n", QCount(queue));
	
	printf("is list empty? yes=1 no=0: %d \n", QIsEmpty(queue));
	
	QDestroy(queue);
	
return 0;
}
