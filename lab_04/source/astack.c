#include "astack.h"

#include <stdio.h>
#include <stdlib.h>

#include "error_handle.h"

astack_t astack_create()
{
	astack_t new_stack = (astack_t)malloc(sizeof(node_arr));
	if (new_stack)
	{
		new_stack->size = 0;
		new_stack->nodes = NULL;
	}
	return new_stack;
}

astack_t astack_push(astack_t stack, long elem)
{
	long *new_nodes = realloc(stack->nodes, ++stack->size);
	if (new_nodes)
	{
		new_nodes[stack->size - 1] = elem;
		stack->nodes = new_nodes;
		return stack;
	}
	return NULL;
}

astack_t astack_pop(astack_t stack, long elem)
{
	long *new_nodes = realloc(stack->nodes, --stack->size);
	if (new_nodes)
	{
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