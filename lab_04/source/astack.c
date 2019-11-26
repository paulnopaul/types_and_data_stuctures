#include "astack.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "error_handle.h"

int astack_create(astack_t *stack, long elem)
{
	if (*stack)
		free(*stack);
	
	int err = OK;

	astack_t new_stack = (astack_t) malloc(sizeof(node_arr));
	if (new_stack) 
	{
		(*stack) = new_stack;

		(*stack)->nodes = (long *) malloc(sizeof(long));
		if (new_stack->nodes)
		{
			(*stack)->nodes[0] = elem;
			(*stack)->size = 1;
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
	if (*stack)
	{
		long *new_nodes = (long *) realloc((*stack)->nodes, sizeof(long) * ((*stack)->size + 1));
		if (new_nodes)
		{
			new_nodes[(*stack)->size] = elem;
			(*stack)->nodes = new_nodes;
			++(*stack)->size;
		}
		else
			err = REALLOC_ERROR;
	}
	else
		err = astack_create(stack, elem);
	
	return err;
}

int astack_pop(astack_t *stack, long *elem)
{
	int err = OK;
	if (*stack)
	{
		if ((*stack)->size == 1)
		{
			*elem = (*stack)->nodes[0];
			free((*stack)->nodes);
			(*stack)->nodes = NULL;
			(*stack)->size = 0;
		}
		else if ((*stack)->size == 0)
			err = EMPTY_STACK;
		else 
		{
			long * new_nodes = realloc((*stack)->nodes, ((*stack)->size - 1) * sizeof(long));
			if (new_nodes)
			{
				--(*stack)->size;
				*elem = (*stack)->nodes[(*stack)->size];
				(*stack)->nodes = new_nodes;
			}
		}
	}
	else 
		err = EMPTY_STACK;

	return err;
}

int astack_clean(astack_t *stack)
{
	int err = OK;
	long buf;
	while (!err)
		err = astack_pop(stack, &buf);
	return err;
}

int astack_print(astack_t *stack)
{
	long elem;
	int err = OK;
	int empty = 1;
	astack_t new_stack = NULL;
	
	// read and output elements from stack and push them to buffer stack
	// (because of stack it gets reverse)
	if (!*stack)
		puts("Empty stack");
		
	while (!err && *stack)
	{
		err = astack_pop(stack, &elem);
		if (!err)
		{
			printf("%ld ", elem);
			err = astack_push(&new_stack, elem);
			empty = 0;
		}
	}
	printf("\n");
	// push elements to source stack to make order like source
	if (!empty && err == EMPTY_STACK)
		err = OK;
	while (!err && new_stack)
	{
		err = astack_pop(&new_stack, &elem);
		if (!err)
			err = astack_push(stack, elem);
	}

	

	return err;
}

int astack_print_decreasing(astack_t *stack)
{
	
	long elem, prev = LONG_MAX;
	int err = OK, start = 1, empty = 1;
	astack_t new_stack = NULL;

	while (!err && *stack)
	{
		err = astack_pop(stack, &elem);
		if (!err)
		{
			err = astack_push(&new_stack, elem);
			empty = 0;
		}
	}

	if (!empty && err == EMPTY_STACK)
		err = OK;

	while (!err && new_stack)
	{
		err = astack_pop(&new_stack, &elem);
		if (!err)
		{
			if (prev < elem)
			{
				if (start)
				{
					printf("\n%ld ", prev);
					start = 0;
				}
				printf("%ld ", elem);
			}
			else
				start = 1;
			prev = elem;
			err = astack_push(stack, elem);
		}
	}
	
	printf("\n");
	if (!empty && err == EMPTY_STACK)
		err = OK;

	return err;
}
