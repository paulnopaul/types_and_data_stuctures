/*
Чеклин Павел ИУ7-32Б
Библиотека для работы со связными списками
 */

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdio.h>

typedef struct linked_list
{
    struct linked_list *head;
    struct linked_list *tail;
    int elem;
} linked_list;

// linked list output
void linked_list_output(linked_list *l);

int linked_list_tail_add(linked_list *list, int elem);

int linked_list_head_add(linked_list list, int elem);

int linked_list_create_from_array(linked_list *list, int* arr, size_t arr_size);

int linked_list_init(linked_list *list, int elem);

int linked_list_next(linked_list **list);

#endif
