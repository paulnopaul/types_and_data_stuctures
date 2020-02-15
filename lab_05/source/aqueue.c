#include "../include/aqueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void aqueue_init(aqueue_t *q)
{
    q->pout = q->pin = q->size = 0;
}

int aqueue_push(aqueue_t *q, const int elem)
{
    if (q->size != AQUEUE_LEN)
    {
        q->arr[q->pin] = elem;
        q->pin = (q->pin + 1) % AQUEUE_LEN;
        ++(q->size);
    }
    else    
        return 1;
    return 0;
}

int aqueue_pop(aqueue_t *q, int *elem)
{
    if (q->size == 0)
        return 1;
    *elem = q->arr[q->pout];
    q->pout = (q->pout + 1) % AQUEUE_LEN;
    --(q->size);
    return 0;
}

void aqueue_print(aqueue_t *q)
{
    int i = q->pout; // size = q->size;
    // printf("Queue: pin = %d; pout = %d; size = %d\n", q->pin, q->pout, size);

    if (q->size == 0)
        printf("Empty");
    else 
    {
        do
        {
            printf("%d ", q->arr[i]);
            i = (i + 1) % AQUEUE_LEN;
        } while (i != q->pin);
    }
    putchar('\n');
}

void aqueue_delete(aqueue_t *q)
{
    aqueue_init(q);
}
