#ifndef __LQUEUE_H__
#define __LQUEUE_H__

struct list_node_t
{
    struct list_node_t *next;
    int data;
};

typedef struct lqueue_t
{
    struct list_node_t *head;
    struct list_node_t *tail;
    int size;
} lqueue_t;

struct list_node_t *create_node(int data);

void lqueue_init(lqueue_t *q);

int lqueue_push(lqueue_t *q, const int elem);

int lqueue_pop(lqueue_t *q, int *elem);

void lqueue_print(lqueue_t *q);

void lqueue_delete(lqueue_t *q);

#endif
