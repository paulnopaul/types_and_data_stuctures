#include "smatrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "err.h"

rare_matrix s_matr_alloc(size_t rows, size_t columns)
{
    rare_matrix buf = (rare_matrix) malloc(sizeof(s_matr));
    int *buf_a = (int *) malloc(rows * columns * sizeof(int));
    size_t *buf_ja = (size_t *) malloc(rows * columns * sizeof(size_t));

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

void s_matr_add_elem(rare_matrix m, size_t row, size_t column, int elem)
{
    int ia_size = list_size(m->ia);
    if (ia_size < row)
        list_add_tail(m->ia, (m->a_size)++);
    m->a[m->a_size - 1] = elem;
    m->ja[m->a_size - 1] = column;
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
            добавить -1 в ia
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
                s_matr_add_elem(m, i, j, buf);
                zeros = 0;
            }
            else if (inp != 1)
                err = MATRIX_INPUT;
        if (zeros)
            list_add_tail(m->ia, list_tail(m->ia));
    }
    return err;
}

int s_matr_resize(rare_matrix m)
{
    int *new_a = (int *) realloc(m->a, m->a_size * sizeof(int));
    size_t *new_ja = (size_t *) realloc(m->ja, m->a_size * sizeof(size_t));

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

    printf("Input rows and columns sizes: ");
    if (scanf("%lld%lld", &buf_r, &buf_c) == 1 && (buf_r > 0) && (buf_c > 0))
    {
        rows = (size_t) buf_r;
        columns = (size_t) buf_c;
        *m = s_matr_alloc(rows, columns);
    }
    else
        err = MATRIX_SIZE_INPUT;

    if (!err)
        err = s_matr_input(*m);

    if (!err)
        err = s_matr_resize(*m);

    return err;
}

