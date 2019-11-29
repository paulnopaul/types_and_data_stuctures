#include "lqueue.h"

#include <stdlib.h>

#include "err.h"


int lqueue_init(lqueue_t queue)
{
    queue->list = NULL;
    queue->pin = NULL;
    return SUCCESS;
}

// TODO all lower this
int lqueue_push(lqueue_t queue, int elem)
{

}

int lqueue_pop(lqueue_t queue, int elem);

int lqueue_delete(lqueue_t queue);