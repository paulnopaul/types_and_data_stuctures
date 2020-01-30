#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct queue_t
{
    struct queue_t *next;
    void * data;
} queue_t;

queue_t* queue_create_node(void *data);

queue_t* queue_push(queue_t *q, void *data);

queue_t* queue_pop(queue_t *q, void **data);

#endif
