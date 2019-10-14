
#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

#include "err.h"

void linked_list_output(linked_list *l)
{
    printf("%d ", l->elem);
    while(linked_list_next(&l) == OK)
        printf("%d ", l->elem);
    putchar('\n');
}

int linked_list_tail_add(linked_list *list, int elem)
{
    linked_list* l = (linked_list*)malloc(sizeof(linked_list));
    l->elem = elem;
    l->tail = NULL;
    l->head = list;
    list->tail = l;
    return 0;
}

int linked_list_next(linked_list **list)
{
    if ((*list)->tail != NULL)
        (*list) = (*list)->tail;
    else
        return NULL_TAIL;
    return OK;
}

int linked_list_init(linked_list *list, int elem)
{
    list->head = NULL;
    list->tail = NULL;
    list->elem = elem;
    return OK;
}

int linked_list_create_from_array(linked_list *list, int* arr, size_t arr_size)
{
    linked_list_init(list, arr[0]);
    linked_list *ptr = list;
    for (size_t i = 1; i < arr_size; ++i, ptr = ptr->tail)
        linked_list_tail_add(ptr, arr[i]);
    return OK;
}