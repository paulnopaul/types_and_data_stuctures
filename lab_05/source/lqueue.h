#ifndef _LQUEUE_H_
#define _LQUEUE_H_

typedef struct node_t *list_t;

struct node_t
{
    int elem; 
    list_t next;
};

typedef struct lqueue
{
    list_t list;
    list_t pin; // указатель на последний элемент list
    // pout - нулевой список
} lqueue;

typedef lqueue *lqueue_t;

int lqueue_init(lqueue_t queue);

int lqueue_push(lqueue_t queue, int elem);

int lqueue_pop(lqueue_t queue, int *elem);

int lqueue_delete(lqueue_t queue);

int lqueue_print(lqueue queue);

void lqueue_check_memory();

#endif