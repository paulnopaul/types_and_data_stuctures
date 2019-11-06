#ifndef _L_STACK_H_
#define _L_STACK_H_

// stack realisation with linked list
typedef struct node_t *lstack_t;

typedef struct node_t
{
	lstack_t next;
	long elem;
} node_t;

lstack_t create_lstack(long num);

lstack_t lstack_init(lstack_t stack, long num);

lstack_t lstack_push(lstack_t stack, long num);

lstack_t lstack_pop(lstack_t stack, long *elem);

lstack_t lstack_delete(lstack_t stack);

lstack_t lstack_print(lstack_t stack);

#endif