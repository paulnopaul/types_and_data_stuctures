//
// Created by Павел Чеклин on 12.10.2019.
//

#include "err.h"

#include <stdio.h>

void err_output(int err)
{
    switch (err)
    {
        case MALLOC_ERROR:
            puts("Malloc error");
            break;
        case CALLOC_ERROR:
            puts("Calloc error");
            break;
        case REALLOC_ERROR:
            puts("Realloc error");
            break;
        case matr_SIZE_INPUT:
            puts("matr size input error");
            break;
        case matr_INPUT:
            puts("matr input error");
            break;
    }
}
