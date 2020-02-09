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

// умножение матрицы на вектор-стобец 
// вектор-столбец хранится как строка
int s_matr_column_prod(s_matr matrix, s_matr column, s_matr *res)
{
    int m_i, c_i, m_end, c_end, buf, row;
    list_t m_ia = matrix.ia, c_ia = column.ia;
    res->rows = matrix.rows;
    res->columns = 1;
    s_matr_alloc(res);

    row = 0;
    while (m_ia->next)
    {
        m_i = m_ia->value;
        m_end = m_ia->next->value;
        c_i = c_ia->value;
        c_end = c_ia->next->value;
        buf = 0;
        // printf("%d %d\n", c_i, c_end);

        while(m_i < m_end && c_i < c_end)
        {
            if (matrix.ja[m_i] < column.ja[c_i])
                m_i++;
            else if (matrix.ja[m_i] > column.ja[c_i])
                c_i++;
            
            if (matrix.ja[m_i] == column.ja[c_i])
                buf += matrix.a[matrix.ja[m_i++]] * column.a[column.ja[c_i++]];
        }
        if (buf == 0)
            s_matr_add_line(res);
        else 
            s_matr_add_elem(res, buf, row, 0, 1);

        ++row;
        m_ia = m_ia->next;
    }
    s_matr_close(res);
    s_matr_resize(res);
    
    return 0;
}

int s_matr_soutput(s_matr *m)
{
    printf("A:  ");
    for (size_t i = 0; i < m->a_size; ++i)
        printf("%d ", m->a[i]);
    putchar('\n');

    printf("JA: ");
    for (size_t i = 0; i < m->a_size; ++i)
        printf("%d ", m->ja[i]);
    putchar('\n');

    printf("IA: ");
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

int s_matr_to_matrix(s_matr sm, matr *m)
{
    int ja_i, ja_end;
    list_t ia = sm.ia;
    m->rows = sm.rows;
    m->columns = sm.columns;
    if (matr_allocate(m))
        return 1;
    

    for (int i = 0; i < sm.rows; ++i, ia = ia->next)
    {
        ja_i = ia->value;
        ja_end = ia->next->value;
        for (int j = 0; j < sm.columns; ++j)
        {
            if (sm.ja[ja_i] < j && ja_i < ja_end)
                ++ja_i;
            if (sm.ja[ja_i] == j && ja_i < ja_end)
                m->matr[i][j] = sm.a[ja_i];
            else 
                m->matr[i][j] = 0;
        }
    }
    return 0;
}

int s_matr_col_to_matrix(s_matr sm, matr *m)
{
    int ja_i, ja_end;
    list_t ia = sm.ia;
    m->rows = sm.rows;
    m->columns = sm.columns;
    if (matr_allocate(m))
        return 1;
    

    for (int i = 0; i < sm.rows; ++i, ia = ia->next)
    {
        ja_i = ia->value;
        ja_end = ia->next->value;
        for (int j = 0; j < sm.columns; ++j)
        {
            if (sm.ja[ja_i] < j && ja_i < ja_end)
                ++ja_i;
            if (sm.ja[ja_i] == j && ja_i < ja_end)
                m->matr[j][i] = sm.a[ja_i];
            else 
                m->matr[j][i] = 0;
        }
    }
    return 0;
}
