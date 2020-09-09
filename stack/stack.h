#include<stddef.h>/*size_t*/

#ifndef __STACK_H__ /*INCLUDE GUARD (guard is activated) for "stack.h"*/
#define __STACK_H__

typedef struct stack stack_t;

/*Construct- use malloc*/
/*size_for_max will determine the stack's "capacity" field*/
stack_t *StackCreate(size_t size_for_max);

/*Distruct, frees the malloc*/
void StackDestroy(stack_t *stack);

/*returns the value that had been "poped", changing the stack*/
/*we rely on the user to check BEFORE calling pop whether the stack is empty*/
/*we will use ASSERT on the *stack the command gets*/
void StackPop(stack_t *stack);

/*Push will insert "value"*/
/*returns status*/
int StackPush(stack_t *stack, void *value);

/*returns the "top" value*/
void *StackPeek(const stack_t *stack);

/*checks top value- returns amount of values stored in stack*/
size_t StackSize(const stack_t *stack);

/*if top = 0, the stack is empty return 1*/
/*returns TRUE/FALSE*/
int StackIsEmpty(const stack_t *stack);

/*return max_size*/
size_t StackCapacity(const stack_t *stack);

#endif /* #ifndef __STACK_H__ << that means the "stack.h" guard ended */

