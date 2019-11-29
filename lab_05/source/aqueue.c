#include "aqueue.h"

#include <stdio.h>
#include <stdlib.h>

#include "err.h"

int aqueue_init(aqueue_t queue)
{
    queue->pin = queue->pout = 0;
    return SUCCESS;
}

int aqueue_push(aqueue_t queue, int elem)
{
    if (queue->pin == queue->pout - 1)
        return QUEUE_OVERFLOW;
    
    queue->arr[queue->pin] = elem;
    queue->pin = (queue->pin + 1) % QUEUE_SIZE;
    return SUCCESS;
}

int aqueue_pop(aqueue_t queue, int *dest)
{
    if (queue->pin == queue->pout)
        return EMPTY_QUEUE;
    
    *dest = queue->arr[queue->pout];
    queue->pout = (queue->pout + 1) % QUEUE_SIZE;
    return SUCCESS;
}

