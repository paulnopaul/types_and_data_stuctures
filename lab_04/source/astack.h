#ifndef _A_STACK_
#define _A_STACK_

#define MAX_SIZE 100000 // максимальный размер стека


typedef struct node_arr
{
	long* nodes;
	long size;
} node_arr;

typedef node_arr *astack_t;

astack_t astack_create();

astack_t astack_push(astack_t stack, long elem);

astack_t astack_pop(astack_t stack, long elem);

astack_t astack_clean(astack_t stack);

void astack_print(astack_t stack);



#endif