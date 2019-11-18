#include "pointer_array.h"

#include <stdio.h>
#include <stdlib.h>

#include "error_handle.h"

int p_arr_create(void ***arr, size_t *size, void* pointer)
{
    int err = OK;

    if (*arr)
        free(*arr);

    *arr = malloc(sizeof(void *));

    if (*arr)
    {
        (*arr)[0] = pointer;
        *size = 1;
    }
    else 
        err = MALLOC_ERROR;
    
    return err;
}

int p_arr_push_back(void ***arr, size_t *size, void* pointer)
{
    int err = OK;
    void **new_arr;
    if (!(*arr))
        err = p_arr_create(arr, size, pointer);
    else
    {
        new_arr = realloc(*arr, (*size + 1) * sizeof(void *));
        if (new_arr)
        {
            *arr = new_arr;
            (*arr)[*size] = pointer;
            ++(*size);
        }
        else
            err = REALLOC_ERROR;
    }

    if (!err)
        printf("ADDED %p = %p\n", pointer, (*arr)[*size - 1]);
    return err;
}
