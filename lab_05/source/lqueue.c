#include "lqueue.h"

#include <stdlib.h>
#include <stdio.h>

#include "err.h"


int lqueue_init(lqueue_t queue)
{
    queue->list = NULL;
    queue->pin = NULL;
    return SUCCESS;
}

int lqueue_push(lqueue_t queue, int elem)
{
    list_t new_node = (list_t)malloc(sizeof(struct node_t));
    if (!new_node)
        return MALLOC_ERROR;
    
    new_node->elem = elem;
    new_node->next = NULL;

    if (queue->pin)
        queue->pin->next = new_node;
    queue->pin = new_node;

    if (!queue->list)
        queue->list = new_node;
    return SUCCESS;
}

int lqueue_pop(lqueue_t queue, int *elem)
{
    list_t buf;
    if (!queue->list)
        return EMPTY_LIST;
    
    *elem = queue->list->elem;

    buf = queue->list;
    queue->list = queue->list->next;
    free(buf);

    return 0;
}

int lqueue_delete(lqueue_t queue)
{
    int buf;
    for (; !lqueue_pop(queue, &buf); );
    return 0;
}

int lqueue_print(lqueue queue)
{
    list_t buf = queue.list;
    while (buf)
    {
        printf("%d ", buf->elem);
        buf = buf->next;
    }
    puts("");
    return SUCCESS;
}
