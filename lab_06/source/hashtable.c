#include "../include/hashtable.h"

#include <stdlib.h>
#include <stdio.h>


int hashtable_init(hashtable *ht, int size)
{
    ht->array = malloc(sizeof(int) * size);
    ht->size = 0;
    ht->allocated = size;
    return 0;
}

int hashtable_add(hashtable *ht, int elem)
{
    return 0;
}

int hashtable_get(hashtable *ht, const char *filename)
{
    return 0;
}

int hashtable_input(hashtable *ht, FILE *stream)
{
    printf("\n\n\n\nHash table");
    return 0;
}

int hashtable_put(hashtable *ht)
{
    return 0;
}

int hashtable_delete(hashtable *ht)
{
    return 0;
}
