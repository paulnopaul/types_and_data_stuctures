#include "../include/lqueue.h"

#include <stdlib.h>
#include <stdio.h>


struct list_node_t *create_node(int data)
{
    struct list_node_t *new = (struct list_node_t *)malloc(sizeof(struct list_node_t));
    new->data = data;
    new->next = NULL;
    return new;
}

void lqueue_init(lqueue_t *q)
{
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
}

int lqueue_push(lqueue_t *q, const int elem)
{
    struct list_node_t *new = create_node(elem);
    if (!new)
        return 1;

    if (!q->size)
        q->head = q->tail = new;
    else
    {
        q->tail->next = new;
        q->tail = q->tail->next;
    }
    ++(q->size);
    return 0;
}

int lqueue_pop(lqueue_t *q, int *elem)
{
    struct list_node_t *buf = q->head;
    if (q->size == 0)
        return 1;
    
    *elem = q->head->data;
    q->head = q->head->next;

    free(buf);
    --(q->size);

    return 0;
}

void lqueue_print(lqueue_t *q)
{
    if (q->size == 0)
        printf("Empty");
    else 
        for (struct list_node_t *buf = q->head; buf; buf = buf->next)
            printf("%d ", buf->data);
    putchar('\n');
}

void lqueue_delete(lqueue_t *q)
{
    struct list_node_t *prev, *head = q->head;

    if (head)
    {
        prev = head;
        head = q->head->next;
        while (head)
        {
            free(prev);
            prev = head;
            head = head->next;
        }
        free(prev);
    }

    q->size = 0;
    q->head = NULL;
    q->tail = NULL; 
}
