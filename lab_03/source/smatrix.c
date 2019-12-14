#include "smatrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "err.h"

void s_matr_init(s_matr *m)
{
    m->rows = 0;
    m->columns = 0;

    m->a_size = 0;
    m->a = NULL;
    m->ja = NULL;
    list_init(m->ia, 0);
}


/*
s_matr *s_matr_alloc(size_t rows, size_t columns)
{
    s_matr * buf = (s_matr *)malloc(sizeof(s_matr));
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
*/

int s_matr_alloc(s_matr *m)
{
    m->a = (int *)malloc(m->rows * m->columns * sizeof(int));
    if (!m->a)
        return EXIT_FAILURE;
    m->ja = (size_t *)malloc(m->rows * m->columns * sizeof(int));
    if (!m->a)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}


int s_matr_add_elem(s_matr * m, size_t row, size_t column, int elem)
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

int s_matr_matrix_input(s_matr * m)
{
    int buf, zero_row = 1;
    puts("Input matrix");
    for (int i = 0; i < m->rows; ++i)
    {
        zero_row = 1;
        for (int  j = 0; j < m->columns; ++j)
        {
            if (scanf("%d", &buf) != 1)
                return EXIT_FAILURE;

            if (buf != 0)
            {
                if (s_matr_add_elem(m, i, j, buf) == EXIT_FAILURE)
                    return EXIT_FAILURE;
                zero_row = 0;
            }
        }
        if (zero_row)
            if (s_matr_add_elem(m, i, 1, buf) == EXIT_FAILURE) // TODO добавить стобца
                return EXIT_FAILURE; // TODO переделать ввод чтобы все работало
    }
    return EXIT_SUCCESS;
}

int s_matr_resize(s_matr * m)
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

int s_matr_input(s_matr *m)
{
    printf("Input rows count: ");
    if (!(scanf("%d", &m->rows) == 1 && m->rows > 0 && m->rows <= 1000))
        return EXIT_FAILURE;

    printf("Input columns count: ");
    if (!(scanf("%d", &m->columns) == 1 && m->columns > 0 && m->columns <= 1000))
        return EXIT_FAILURE;
    
    if (s_matr_alloc(m) == EXIT_FAILURE)
        return EXIT_FAILURE;
    
    if (s_matr_matrix_input(m) == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int s_matr_output(s_matr * m)
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

void s_matr_delete(s_matr *m)
{
    free(m->a);
    free(m->ja);
    list_delete(m->ia);

    s_matr_init(m);
}
