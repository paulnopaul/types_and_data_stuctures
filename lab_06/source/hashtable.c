#include "../include/hashtable.h"

#include <stdlib.h>
#include <stdio.h>

#define __INT_MIN (-__INT_MAX__ - 1)

int hashtable_init(hashtable *ht, int size)
{
    ht->array = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i)
        ht->array[i] = __INT_MIN;

    ht->size = size;
    ht->max_collisions = 0;
    ht->hashfunc = hash_mod;
    return 0;
}

int hashtable_add(hashtable *ht, int elem)
{
    int i = 0, j;
    do 
    {
        j = hash_sqmov(elem, i, ht->size);
        if (ht->array[j] == __INT_MIN)
        {
            ht->array[j] = elem;
            if (i > ht->max_collisions)
                ht->max_collisions = i;
            return 0;
        }
        ++i;
    } while (i != ht->size);
    return 1; // переполнение 
}

int hashtable_get(hashtable *ht, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f)
    {
        if (hashtable_input(ht, f) == 1)
        {
            fclose(f);
            return 1;
        }
        fclose(f);
        return 0;
    }
    return 1;
}

int hashtable_input(hashtable *ht, FILE *stream)
{
    int buf;
    while (fscanf(stream, "%d", &buf) == 1)
        if (hashtable_add(ht, buf) == 1)
            return 1;
    return 0;
}

int hashtable_put(hashtable ht)
{
    puts("Hashtable\nKey Value");
    for (int i = 0; i < ht.size; ++i)
        if (ht.array[i] != __INT_MIN)
            printf("%d %d\n", i, ht.array[i]);
    return 0;
}

int hash_mod(int val, int max)
{
    return abs(val) % max;
}

int hash_prod(int val, int max)
{
    return (int)(max * (((double)abs(val)) * HASHPROD_CONST -
                        (int)(((double)abs(val)) * HASHPROD_CONST)));
}

int hash_sqmov(int val, int i, int max)
{
    return (abs(val) + i * i) % max; 
}

int hashtable_delete(hashtable *ht)
{
    free(ht->array);
    ht->size = 0;
    ht->max_collisions = 0;
    ht->hashfunc = NULL;
    ht->hashmov = NULL;
    return 0;
}
