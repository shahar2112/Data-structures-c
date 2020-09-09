#include <stdlib.h> /* malloc */
#include <stdio.h> /*printf */
#include <assert.h> /*assert */

#include "stack.h"

struct stack
{
	void **values; /*the stack itself, an array of general elements*/
	size_t top; /*index*/
	size_t capacity; /*max_size*/
};


/*size_for_max will determine the stack's "capacity" field*/
stack_t *StackCreate(size_t size_for_max)
{
	
	stack_t *new_stack = (stack_t*)malloc(sizeof(stack_t));
	new_stack->values = (void*)malloc(size_for_max*sizeof(void*));
	if(NULL == new_stack || NULL == new_stack->values )
	{
		return NULL;
    }
	
	new_stack->capacity = size_for_max;
    new_stack->top = 0;
    
	return new_stack;
}


/*Distruct, frees the malloc*/
void StackDestroy(stack_t *stack)
{
	assert(stack);
	
	free(stack->values);
	stack->values = NULL;
	
	stack->top = 0;
	free(stack);
}


/*we rely on the user to check BEFORE calling pop whether the stack is empty*/
/*we will use ASSERT on the *stack the command gets*/
void StackPop(stack_t *stack)
{
	assert(stack->top > 0); /*you can't pop an empty stack */
	stack->top -= 1; /* decreasing index in one */
}



/*Push will insert "value"*/
/*returns status*/
int StackPush(stack_t *stack, void *value)
{
	assert(stack);
	
	if(stack->top == stack->capacity)
	{
		return 0;
	}
	else
	{
		stack->values[stack->top] = value;
		stack->top += 1;
	}
	return 1;
}



/*returns the "top" value*/
void *StackPeek(const stack_t *stack)
{
	assert(stack);
	
	return stack->values[stack->top - 1];
}



/*checks top value- returns amount of values stored in stack*/
size_t StackSize(const stack_t *stack)
{
	assert(stack);
	
	return stack->top;
}


/*if top = 0, the stack is empty*/
/*returns TRUE/FALSE*/
int StackIsEmpty(const stack_t *stack)
{
	assert(stack);
	
	return ((stack->top) == 0) ? 1 : 0;
}



/*return max_size*/
size_t StackCapacity(const stack_t *stack)
{
	assert(stack);
	
	return stack->capacity;
}
