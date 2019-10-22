//
// Created by Павел Чеклин on 12.10.2019.
//

#ifndef _ERR_H_
#define _ERR_H_

// Success code
#define OK 0

// linked_list errors
#define NULL_TAIL 1

// memory errrors
#define MALLOC_ERROR 2
#define CALLOC_ERROR 3
#define REALLOC_ERROR 4

// smatrix errors
#define MATRIX_SIZE_INPUT 5
#define MATRIX_INPUT 6
#define ALLOCATION_ERROR 7

void err_output(int err);

#endif //LAB_03_ERR_H
