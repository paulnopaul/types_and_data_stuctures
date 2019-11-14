#include "lstack.h"

#include <stdio.h>
#include <stdlib.h>

#include "error_handle.h"


int lstack_init(lstack_t *stack, long elem)
{
	int err = OK;
	if (*stack)
		free(*stack);
	*stack = malloc(sizeof(node_t));
	if (*stack)
	{
		(*stack)->elem = elem;
		(*stack)->next = NULL;
	}
	else
		err = MALLOC_ERROR;
	return err;
}

int lstack_push(lstack_t *stack, long elem)
{
	int err = OK;
	lstack_t new_node = malloc(sizeof(node_t));
	if (new_node)
	{
		new_node->next = *stack;
		new_node->elem = elem;
		*stack = new_node;
	}
	else
		err = MALLOC_ERROR;
	return err;
}

int lstack_pop(lstack_t *stack, long *elem, lstack_t *freed)
{
	int err = OK;
	lstack_t buf = NULL;
	if (*stack)
	{
		*elem = (*stack)->elem;

		buf = *stack;
		if ((*stack)->next);
			*stack = (*stack)->next;
		*freed = buf;
		free(buf);
	}
	else
		err = EMPTY_STACK;
	return err;
}

void lstack_print(lstack_t *stack)
{
	long elem = 0;
	int err = lstack_pop(stack, &elem);
	if (err == EMPTY_STACK)
		puts("Empty stack");
	do
	{
		printf("%ld ", elem);
		err = lstack_pop(stack, &elem);
	} while (!err);
	printf("\n");;
}

int lstack_print_decreasing(lstack_t *stack);

int lstack_delete(lstack_t *stack)
{
	int err = OK, buf = 0;
	lstack_t lbuf = NULL;
	while (!err)
		err = lstack_pop(stack, buf, &lbuf);
	return err;
}