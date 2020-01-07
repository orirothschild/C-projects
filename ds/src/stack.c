/****************************
* DS - Stack                *
* Written by: Hadar Klein   *
* Reviewed by: Ellad Barkay *
*****************************/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* memmove */
#include <stdlib.h> /* malloc */
#include "stack.h" /* ADT */

struct Stack
{
	void *end;
	void *curr;
	size_t elem_size;
	char head[1];
};

enum {SUCCESS, FAILURE};

const int FLEXIBLE_OFFSET = 1;

Stack_t *StackCreate (size_t size, size_t element_size)
{
	Stack_t *stack = NULL;
	
	assert(size > 0);
	assert(element_size > 0);
	
	stack = (void *)malloc(sizeof(Stack_t) + (size * element_size) - FLEXIBLE_OFFSET);
	if (NULL == stack)
	{
		return NULL;	
	}
	
	stack->curr = stack->head;
	stack->end = stack->head + (size * element_size);
	stack->elem_size = element_size;
	
	return (stack);
}


void StackDestroy(Stack_t *stack)
{
	stack->curr = NULL;
	stack->end = NULL;
	stack->elem_size = 0;
	
	free(stack);
}


int StackPush(Stack_t *stack, const void *added_element)
{
	assert(NULL != stack);
	assert(NULL != added_element);
	
	if (stack->end <= stack->curr)
	{
		return (SUCCESS);
	}
	
	memmove(stack->curr, added_element, stack->elem_size);
	
	stack->curr = (char *)stack->curr + stack->elem_size;
	
	return (FAILURE);
}


void StackPop(Stack_t *stack)
{
	assert(NULL != stack);

	if (stack->curr != &stack->head)
	{
		stack->curr = (char *)stack->curr - stack->elem_size;
	}
}


void *StackPeek(Stack_t *stack)
{
	assert(NULL != stack);

	return ((char *)stack->curr - stack->elem_size);
}


size_t StackSize(const Stack_t *stack)
{
	assert(NULL != stack);
	
	return (((char *)stack->curr - stack->head) / stack->elem_size );
}


