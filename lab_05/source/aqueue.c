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
    if ((queue->pin + 1) % (QUEUE_SIZE + 1) == queue->pout)
        return QUEUE_OVERFLOW;
    
    if (queue->pin == QUEUE_SIZE)
        queue->pin = 0;
    queue->arr[queue->pin] = elem;
    queue->pin = (queue->pin + 1) % (QUEUE_SIZE + 1);
    return SUCCESS;
}

int aqueue_pop(aqueue_t queue, int *dest)
{
    if (queue->pin == queue->pout)
        return EMPTY_QUEUE;
    
    *dest = queue->arr[queue->pout];
    queue->arr[queue->pout] = 0;
    queue->pout = (queue->pout + 1) % QUEUE_SIZE;
    return SUCCESS;
}

int aqueue_print(aqueue queue)
{
    if (queue.pout > queue.pin)
    {
        for (int i = queue.pout; i < QUEUE_SIZE; ++i)
            printf("%d ", queue.arr[i]);
        for (int i = 0; i < queue.pin; ++i)
            printf("%d ", queue.arr[i]);
    }
    else if (queue.pin > queue.pout)
        for (int i = queue.pout; i < queue.pin; ++i)
            printf("%d ", queue.arr[i]);
    else
        printf("Empty queue");
    puts("");
    return SUCCESS;
}
