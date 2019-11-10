#include "lstack.h"

#include <stdio.h>
#include <stdlib.h>

#include "error_handle.h"

lstack_t create_lstack(long num)
{
	lstack_t new_stack = (lstack_t)malloc(sizeof(node_t));
	if (new_stack)
	{
		new_stack->next = NULL;
		new_stack->elem = num;
	}
	return new_stack;
}

lstack_t lstack_init(lstack_t stack, long num)
{
	if (!stack)
		free(stack);
	stack = create_lstack(num);
	return stack;
}

lstack_t lstack_push(lstack_t stack, long num)
{
	lstack_t new_node = create_lstack(num);
	if (new_node)
		new_node->next = stack;
	return new_node;
}

lstack_t lstack_pop(lstack_t stack, long *elem)
{
	lstack_t new_stack = stack->next;
	*elem = stack->elem;
	free(stack);
	return new_stack;
}

lstack_t lstack_delete(lstack_t stack)
{
	lstack_t next;
	for (; stack; stack = next)
	{
		next = stack->next;
		free(stack);
	}
	return NULL;
}

void lstack_print(lstack_t stack)
{
	for (; stack->next; stack = stack->next)
		printf("%ld ", stack->elem);
	printf("\n");
}