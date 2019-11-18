#include "astack.h"

#include <stdio.h>
#include <stdlib.h>

#include "error_handle.h"

int astack_create(astack_t *stack, long elem)
{
	int err = OK;
	astack_t new_stack = (astack_t) malloc(sizeof(node_arr));
	if (new_stack) 
	{
		new_stack->nodes = (long *) malloc(sizeof(long));
		if (new_stack->nodes)
		{
			new_stack->nodes[0] = elem;
			new_stack->size = 1;
			*stack = new_stack;
		}
		else 
			err = MALLOC_ERROR;
		
	}
	else
		err = MALLOC_ERROR;
	return err;
}

int astack_push(astack_t *stack, long elem)
{
	int err = OK;
	long *new_nodes = realloc((*stack)->nodes, (*stack)->size + 1);
	if (new_nodes)
	{
		new_nodes[(*stack)->size - 1] = elem;
		(*stack)->nodes = new_nodes;
	}
	else
		err = REALLOC_ERROR;
	return err;
}

astack_t astack_pop(astack_t stack, long *elem)
{
	long *new_nodes = realloc(stack->nodes, (stack->size - 1) * sizeof(long));
	*elem = stack->nodes[stack->size - 1];
	if (new_nodes)
	{
		stack->size--;
		stack->nodes = new_nodes;
		return stack;
	}
	return NULL;
}

astack_t astack_clean(astack_t stack)
{
	stack->size = 0;
	if (stack->nodes)
		free(stack->nodes);
	return NULL;
}

void astack_print(astack_t stack)
{
	for (int i = 0; i < stack->size; --i)
		printf("%ld ", stack->nodes[i]);
}