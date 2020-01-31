#include "smatrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "err.h"
#include "smatr_input.h"

void s_matr_init(s_matr *m)
{
    m->rows = 0;
    m->columns = 0;

    m->a_size = 0;
    m->a = NULL;
    m->ja = NULL;
    m->ia = NULL;
}

int s_matr_alloc(s_matr *m)
{
    m->a = (int *)malloc(m->rows * m->columns * sizeof(int));
    if (!m->a)
        return EXIT_FAILURE;
    m->ja = (int *)malloc(m->rows * m->columns * sizeof(int));
    if (!m->a)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int s_matr_resize(s_matr *m)
{
    int *new_a = (int *)realloc(m->a, m->a_size * sizeof(int));
    int *new_ja = (int *)realloc(m->ja, m->a_size * sizeof(int));

    if (!new_a || !new_ja)
        return 1;

    m->a = new_a;
    m->ja = new_ja;
    return 0;
}

// умножение матрицы на вектор-стобец (вектор-стобец хрнавится как вертикальный
// столбец матрицы)
int s_matr_column_prod(s_matr matrix, s_matr column, s_matr *res)
{
    int m_i, c_i, m_start, m_end, c_start, c_end, buf, row;
    list_t m_ia = matrix.ia, c_ia = column.ia;
    res->rows = matrix.rows;
    res->columns = 1;

    row = 0;
    while (m_ia->next)
    {
        m_i = m_ia->value;
        m_end = m_ia->next->value;
        c_i = c_ia->value;
        c_end = c_ia->next->value;
        buf = 0;
        while(m_i < m_end && c_i < c_end)
        {
            
        }
        if (buf == 0)
            s_matr_add_line(res);
        else 
            s_matr_add_elem(res, buf, row, 0, 1);
            
        ++row;
        m_ia = m_ia->next;
        m_ia = m_ia->next;
    }
    
    return 0;
}

int s_matr_output(s_matr *m)
{
    for (size_t i = 0; i < m->a_size; ++i)
        printf("%d ", m->a[i]);
    putchar('\n');

    for (size_t i = 0; i < m->a_size; ++i)
        printf("%d ", m->ja[i]);
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
