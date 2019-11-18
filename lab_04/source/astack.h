#ifndef _A_STACK_
#define _A_STACK_

#define MAX_SIZE 100000 // максимальный размер стека

typedef struct node_arr *astack_t;

typedef struct node_arr
{
	long* nodes;
	long size;
} node_arr;

int astack_create(astack_t *stack, long elem);

int astack_push(astack_t *stack, long elem);

int astack_pop(astack_t *stack, long *elem);

int astack_clean(astack_t *stack);

int astack_print(astack_t *stack);

int astack_print_decreasing(astack_t *stack);


#endif