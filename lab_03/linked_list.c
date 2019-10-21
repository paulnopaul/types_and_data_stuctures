
#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

#include "err.h"


list_t list_init(list_t list, size_t elem)
{
    list_t buf = (list_t)malloc(sizeof(node_t));
    if (buf)
    {
        buf->value = elem;
        buf->head = NULL;
        buf->tail = list;
    }
    return buf;
}

list_t list_add_tail(list_t list, size_t elem)
{
    return OK;
}

list_t list_add_head(list_t list, size_t elem)
{
    list_t buf = list_init(list, elem);
    return buf;
}



int list_size(list_t list)
{
    return OK;
}