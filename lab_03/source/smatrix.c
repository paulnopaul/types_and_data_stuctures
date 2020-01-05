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
    m->ia = NULL;
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
    m->ja = (size_t *)malloc(m->rows * m->columns * sizeof(size_t));
    if (!m->a)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
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
    добавить количество ненулевых строк в ia
 */
int s_matr_matrix_input(s_matr *m)
{
    int buf, zero_row, zero_row_count = 0;
    puts("Input matrix");
    for (int i = 0; i < m->rows; ++i)
    {
        zero_row = 1;
        for (int j = 0; j < m->columns; ++j)
        {
            if (scanf("%d", &buf) != 1)
                return EXIT_FAILURE;

            if (buf != 0)
            {
                if (s_matr_add_elem(m, i, j, buf, zero_row) == EXIT_FAILURE)
                    return EXIT_FAILURE;
                zero_row = 0;
            }
        }
        zero_row_count += zero_row;
        if (!zero_row && zero_row_count)
        {
            for (int j = 0; j < zero_row_count; ++j)
                if (!(m->ia = list_double_tail(m->ia)))
                    return EXIT_FAILURE;
            zero_row_count = 0;
        }
    }
    if (!(m->ia = list_push_back(m->ia, m->a_size)))
        return EXIT_FAILURE;
    if (zero_row_count)
    {
        for (int j = 0; j < zero_row_count; ++j)
            if (!(m->ia = list_double_tail(m->ia)))
                return EXIT_FAILURE;
        zero_row_count = 0;
    }
    return EXIT_SUCCESS;
}

int s_matr_add_elem(s_matr *m, int row, int column, int elem, int new_row)
{
    if (new_row)
        if (!((m->ia = list_push_back(m->ia, m->a_size))))
            return EXIT_FAILURE;

    m->a[m->a_size] = elem;
    m->ja[m->a_size] = column;
    ++m->a_size;
    return EXIT_SUCCESS;
}

// умножение матрицы на вектор-стобец (вектор-стобец хрнавится как вертикальный
// столбец матрицы)
int s_matr_column_prod(s_matr matrix, s_matr column, s_matr *res)
{
    list_t mlist = matrix.ia, clist;
    int icstart, icend, imstart, imend;
    int im, ic;
    int buf;
    while (mlist)
    {
        imstart = imend;
        imend = mlist->value;
        clist = column.ia;
        buf = 0;
        im = imstart;
        while(clist)
        {   
            icstart = icend;
            imstart++;
            icend = clist->value;

            if (icstart < icend)
                
            
            clist = clist->next;
        }

        mlist = mlist->next; 
    }
    return s_matr_resize(res);
}

// особенность - вектор-столбец хранится в строке матрицы
int s_matr_matrix_column_production(s_matr matrix, s_matr vector, s_matr *res)
{
    list_t mlist = matrix.ia;
    int istart, iend; 
    int buf, row = 0;
    if (matrix.columns != vector.columns && vector.ia->next && vector.ia->next->next && !vector.ia->next->next->next)
        return EXIT_FAILURE;

    s_matr_init(res);
    res->rows = matrix.rows;
    res->columns = 1;
    if (s_matr_alloc(res) == EXIT_FAILURE)
        return EXIT_FAILURE;
    
    iend = mlist->value;
    mlist = mlist->next;

    while (mlist)
    {
        buf = 0;
        istart = iend;
        iend = mlist->value;
        for (int i = 0; i < vector.a_size && istart < iend; ++i)
        {
            if (vector.ja[i] == matrix.ja[istart])
                buf += vector.a[i] * matrix.ja[istart];
        }
        if (buf != 0 && s_matr_add_elem(res, row, 0, buf, 1) == EXIT_FAILURE)
            return EXIT_FAILURE;

        mlist = mlist->next;
    }
    return s_matr_resize(res);
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
    if (s_matr_resize(m) == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int s_matr_output(s_matr *m)
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
