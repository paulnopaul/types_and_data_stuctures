#ifndef _AQUEUE_H_
#define _AQUEUE_H_

#include <stdlib.h>
#include <stdio.h>

#define QUEUE_SIZE 1000

typedef struct aqueue
{
    int arr[QUEUE_SIZE + 1];
    int pout, pin;
} aqueue;

typedef aqueue *aqueue_t;

int aqueue_init(aqueue_t queue);

int aqueue_push(aqueue_t queue, int elem);

int aqueue_pop(aqueue_t queue, int *dest);

int aqueue_print(aqueue queue);

double mid_push_time(int count);

double mid_pop_time(int count);

#endif