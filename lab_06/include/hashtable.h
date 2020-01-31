#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdio.h>

typedef struct hashtable
{
    int *array; 

    int size;
    int allocated;

    int (*func)(int);
} hashtable;

int hashtable_init(hashtable *ht, int size);

int hashtable_add(hashtable *ht, int elem);

int hashtable_get(hashtable *ht, const char *filename);

int hashtable_input(hashtable *ht, FILE *stream);

int hashtable_put(hashtable *ht);

int hashtable_delete(hashtable *ht);

#endif
