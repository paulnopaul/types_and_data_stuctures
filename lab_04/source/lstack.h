#ifndef _L_STACK_H_
#define _L_STACK_H_

// stack realisation with linked list
typedef struct node_t *lstack_t;

typedef struct node_t
{
	lstack_t next;
	long elem;
} node_t;

int lstack_init(lstack_t *stack, long elem);

int lstack_push(lstack_t *stack, long elem);

int lstack_pop(lstack_t *stack, long *elem, lstack_t *freed);

void lstack_print(lstack_t *stack);

int lstack_print_decreasing(lstack_t *stack);

int lstack_delete(lstack_t *stack);
#endif