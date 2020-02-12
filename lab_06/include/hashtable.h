#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdio.h>

#define HASHPROD_CONST 0.1544444

typedef struct hashtable
{
    int *array; 
    int size;

    int (*hashfunc)(int, int);
    int (*hashmov)(int, int, int);

    int max_collisions;
} hashtable;

int hashtable_init(hashtable *ht, int size);

int hashtable_add(hashtable *ht, int elem);

int hashtable_get(hashtable *ht, const char *filename);

int hashtable_input(hashtable *ht, FILE *stream);

int hashtable_put(hashtable ht);

int hashtable_delete(hashtable *ht);

// hash functions

int hash_mod(int val, int max);

int hash_prod(int val, int max);

int hash_sqmov(int val, int i, int max);

#endif
