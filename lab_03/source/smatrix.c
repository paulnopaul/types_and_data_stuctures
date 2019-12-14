#include "smatrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "err.h"


rare_matrix s_matr_alloc(size_t rows, size_t columns)
{
    rare_matrix buf = (rare_matrix)malloc(sizeof(s_matr));
    int *buf_a = (int *)malloc(rows * columns * sizeof(int));
    size_t *buf_ja = (size_t *)malloc(rows * columns * sizeof(size_t));

    if (buf && buf_a && buf_ja)
    {
        buf->rows = rows;
        buf->columns = columns;
        buf->a = buf_a;
        buf->ja = buf_ja;
        return buf;
    }
    return NULL;
}

int s_matr_add_elem(rare_matrix m, size_t row, size_t column, int elem)
{
    // printf("Add elem: %ld %ld = %d\n", row, column, elem);
    int ia_size = list_size(m->ia);
    // printf("ia_size = %d    row = %d\n", ia_size, (int)row);

    if ((long long)ia_size <= (long long)row)
        m->ia = list_add_tail(m->ia, m->a_size);
    m->a_size++;
    if (m->ia)
    {
        m->a[m->a_size - 1] = elem;
        m->ja[m->a_size - 1] = column;
        return OK;
    }
    else
        return MALLOC_ERROR;
}

/*
    Ввод разреженной матрицы
    Алгоритм:
    for i = 0 to rows - 1:
        for j = 0 to columns - 1:
            ввод buf
            если buf не 0:
                добавить в конец разреженной матрицы элемент buf
        если строка нулевая:
            добавить последний элемент ia в ia
 */

int s_matr_input(rare_matrix m)
{
    int err = OK, inp, zeros;
    int buf;
    m->a_size = 0;
    for (size_t i = 0; i < m->rows && !err; ++i)
    {
        zeros = 1;
        for (size_t j = 0; j < m->columns && !err; ++j)
            if ((inp = scanf("%d", &buf)) == 1 && buf != 0)
            {
                err = s_matr_add_elem(m, i, j, buf);
                zeros = 0;
            }
            else if (inp != 1)
                err = MATRIX_INPUT;
        if (zeros)
            err = (m->ia = list_add_tail(m->ia, list_tail(m->ia))) ? OK : MALLOC_ERROR;
    }
    m->ia = list_add_tail(m->ia, m->a_size + 1);
    return err;
}

int s_matr_resize(rare_matrix m)
{
    int *new_a = (int *)realloc(m->a, m->a_size * sizeof(int));
    size_t *new_ja = (size_t *)realloc(m->ja, m->a_size * sizeof(size_t));

    if (new_a && new_ja)
    {
        m->a = new_a;
        m->ja = new_ja;
    }
    else
        return REALLOC_ERROR;
    return OK;
}

int s_matr_full_input(rare_matrix *m)
{

    int err = OK;
    long long buf_r, buf_c;
    size_t rows, columns;

    printf("Input row and column count: ");
    if (scanf("%lld%lld", &buf_r, &buf_c) == 2 && (buf_r > 0) && (buf_c > 0))
    {
        puts("ALLOCATION START"); // TEST
        rows = (size_t)buf_r;
        columns = (size_t)buf_c;
        err = (*m = s_matr_alloc(rows, columns)) ? OK : ALLOCATION_ERROR;
        puts(!err ? "ALLOCATION COMPLETE" : "ALLOCATION FAILED"); // TEST
    }
    else
        err = MATRIX_SIZE_INPUT;
    if (!err)
    {
        puts("Input matrix");
        err = s_matr_input(*m);
    }

    if (!err)
        err = s_matr_resize(*m);
    return err;
}

int s_matr_output(rare_matrix m)
{
    for (size_t i = 0; i < m->a_size; ++i)
        printf("%d ", m->a[i]);
    putchar('\n');

    for (size_t i = 0; i < m->a_size; ++i)
        printf("%ld ", m->ja[i]);
    putchar('\n');

    list_output(m->ia);

    return OK;
}
