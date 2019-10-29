
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
        buf->prev = NULL;
        buf->next = list;
    }
    return buf;
}

list_t list_last(list_t list)
{
    if (!list)
        return NULL;
    while (list->next)
        list = list->next;
    return list;
}

list_t list_add_tail(list_t list, size_t val)
{
    list_t buf = list_init(NULL, val);

    if (!buf)
        return NULL;
    if (!list)
        return buf;

    list_t cur = list_last(list);
    buf->prev = cur;
    cur->next = buf;

    return list;
}

list_t list_add_head(list_t list, size_t elem)
{
    list_t buf = list_init(list, elem);
    return buf;
}

int list_size(list_t list)
{
    list_t buf = list;
    int count = 0;
    if (buf)
    {
        count = 1;
        for (; buf->next; buf = buf->next)
            count++;
    }
    return count;
}

void list_delete(list_t list)
{
    if (list)
    {
        list_t buf = list;
        int count = 1;
        while (buf->next)
        {
            buf = buf->next;
            free(buf->prev);
            count++;
        }
        free(buf);
        printf("%d freed\n", count);
    }
}

void list_output(list_t list)
{
    list_t buf = list;
    if (buf)
    {
        for (; buf; buf = buf->next)
            printf("%ld ", buf->value);
        putchar('\n');
    }
    //printf("%p %p %p: %ld\n", buf, buf->prev, buf->next, buf->value);
}

int list_tail(list_t list)
{
    return OK;
}
