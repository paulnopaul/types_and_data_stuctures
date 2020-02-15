#ifndef __AQUEUE_H__
#define __AQUEUE_H__

#define AQUEUE_LEN 10000

typedef struct aqueue_t
{
    int arr[AQUEUE_LEN];
    int pout;
    int pin;
    int size;
} aqueue_t;

void aqueue_init(aqueue_t *q);

int aqueue_push(aqueue_t *q, const int elem);

int aqueue_pop(aqueue_t *q, int *elem);

void aqueue_print(aqueue_t *q);

void aqueue_delete(aqueue_t *q);

#endif
