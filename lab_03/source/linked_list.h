/*
Чеклин Павел ИУ7-32Б
Библиотека для работы со связными списками
 */

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdio.h>

typedef struct node_t *list_t;
typedef struct node_t
{
    size_t value;
    list_t prev;
    list_t next;
} node_t;


list_t list_init(list_t list, size_t elem);

list_t list_last(list_t list);

list_t list_add_tail(list_t list, size_t val);

list_t list_add_head(list_t list, size_t elem);

int list_size(list_t list);

list_t list_calloc(size_t size);

int list_tail(list_t list);

void list_delete(list_t list);

void list_output(list_t list);



#endif
