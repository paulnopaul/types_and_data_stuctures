#ifndef _POINTER_ARR_H_
#define _POINTER_ARR_H_

#include <stdio.h>

int p_arr_create(void ***arr, size_t *size, void* pointer);

int p_arr_push_back(void ***arr, size_t *size, void* pointer);

#endif