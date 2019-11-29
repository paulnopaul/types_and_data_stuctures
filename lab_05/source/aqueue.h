#ifndef _AQUEUE_H_
#define _AQUEUE_H_

#include <stdlib.h>
#include <stdio.h>

#define QUEUE_SIZE 2000

typedef struct aqueue 
{
    int arr[QUEUE_SIZE];
    int pout, pin;
} aqueue_struct;

typedef aqueue_struct *aqueue_t;

int aqueue_init(aqueue_t queue);

int aqueue_push(aqueue_t queue, int elem);

int aqueue_pop(aqueue_t queue, int *dest);

#endif