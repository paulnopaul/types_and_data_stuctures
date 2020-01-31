#include "../include/queue.h"

#include <stdlib.h>
#include <stdio.h>

queue_t* queue_create_node(void *data)
{
    queue_t *new = (queue_t *)malloc(sizeof(queue_t));
    new->next = NULL;
    new->data = data;
    return new;
}

queue_t *queue_push(queue_t *q, void *data)
{
    queue_t *new = queue_create_node(data);
    new->next = q;
    return new;
}

queue_t* queue_pop(queue_t *q, void **data)
{
    queue_t *new = q->next;
    *data = q->data;
    free(q);
    return new;
}
