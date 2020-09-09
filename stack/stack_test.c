#include <stdio.h> /*printf */
#include <stdlib.h> /*exit */

#include "stack.h"


int main()
{

	stack_t *stack = NULL;
	size_t size_for_max = 10;
	int status = 0;
	float float1 = 3.14;
	char *string1 = "hello";
	
	/* checking StackCreate */
	stack = StackCreate(size_for_max);
	if(stack == NULL)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}
	
	/* checking StackIsEmpty + StackPush*/
	printf("is stack empty? (yes=1, no=0): %d \n", StackIsEmpty(stack));
	
	/* checking Stacksize */
	printf("stack size is: %ld \n", StackSize(stack));
	
	status = StackPush(stack, (void*)5);
	printf("did push succeed? (yes=1, no=0): %d \n", status);
	printf("is stack empty? (yes=1, no=0): %d \n", StackIsEmpty(stack));
	
	/* checking Stacksize */
	printf("stack size is: %ld \n", StackSize(stack));
	
	/* checking StackPeek */
	status = StackPush(stack, (void*)6);
	printf("top value is: %p \n", StackPeek(stack));

	status = StackPush(stack, (void*)4);
	printf("top value is: %p \n", StackPeek(stack));
	
	status = StackPush(stack, &float1);
	printf("top value is: %f \n", *(float*)StackPeek(stack));
	
	status = StackPush(stack, string1);
	printf("top value is: %s \n", (char*)StackPeek(stack));
	
	/* checking Stacksize */
	printf("stack size is: %ld \n", StackSize(stack));
	
	/* checking StackPop */
	StackPop(stack);
	printf("top value after pop is: %p \n", StackPeek(stack));
	
	StackPop(stack);
	printf("top value after pop is: %p \n", StackPeek(stack));
	
	StackPop(stack);
	printf("top value after pop is: %p \n", StackPeek(stack));
	
	/* checking StackPeek */
	printf("stack Capacity is: %ld \n",StackCapacity(stack));
	
	/* checking StackPeek */
	printf("stack size is: %ld \n", StackSize(stack));
	
	/* checking StackDestroy */
	StackDestroy(stack);
	
	
return 0;
}
