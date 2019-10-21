#include "smatrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

rare_matrix s_matr_alloc(size_t rows, size_t columns)
{
    rare_matrix buf = (rare_matrix) malloc(sizeof(s_matr));
    int* buf_a = (int*) malloc(rows * columns * sizeof(int));
    int* buf_ja = (int*) malloc(rows * columns * sizeof(int));
    list_t buf_ia = list_calloc(rows);
    if (buf && buf_a && buf_ja && buf_ia)
    {
        buf->rows = rows;
        buf->columns = columns;
        buf->a = buf_a;
        buf->ja = buf_ja;
        buf->ia = buf_ia;
        return buf;
    }
    return NULL;
}