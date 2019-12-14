
#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

#include "err.h"

list_t list_create(size_t elem)
{
    list_t new_list = (list_t)malloc(sizeof(node_t));
    if (new_list)
    {
        new_list->prev = NULL;
        new_list->next = NULL;
        new_list->value = elem;
    }
    return new_list;
}

list_t list_push_back(list_t list, size_t val)
{
    // printf("Adding %ld, list: \n", val);
    // list_output(list);
    list_t buf;
    list_t new_node = list_create(val);
    if (!list)
        return new_node;

    // puts("Start Going to end");
    buf = list;
    while (buf->next)
        buf = buf->next;
    // puts("End going to end");

    buf->next = new_node;
    if (new_node)
        new_node->prev = buf;
    return list;
}

void list_output(list_t list)
{
    list_t buf;
    if (!list)
    {
        puts("Empty");
        return;
    }
    buf = list;
    while(buf)
    {
        printf("%ld ", buf->value);
        buf = buf->next;
    }
    printf("\n");
    //printf("%p %p %p: %ld\n", buf, buf->prev, buf->next, buf->value);
}

list_t list_double_tail(list_t list)
{
    list_t buf;
    list_t new_node;
    if (!list)
        return list_create(0);

    buf = list;
    while (buf->next)
        buf = buf->next;

    new_node = list_create(buf->value);
    buf->next = new_node;

    if (new_node)
        new_node->prev = buf;

    return list;
}

list_t list_delete(list_t list)
{
    if (!list)
        return NULL;

    while (list->next)
    {
        list = list->next;
        free(list->prev);
    }
    free(list);
    return NULL;
}
