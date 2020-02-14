#include "smatr_input.h"

#include <stdio.h>
#include <stdlib.h>


int s_matr_full_input(s_matr *m)
{
    int r = 0, c = 0;
    printf("Input rows and columns count: ");
    if (!(scanf("%d%d", &r, &c) == 2) && (r > 0) && (c > 0))
        return 1;
    
    m->rows = r;
    m->columns = c;
    if (s_matr_alloc(m))
        return 1;
    
    puts("Input matrix, elements are integers:");
    if (s_matr_matrix_input(m))
        return 1;
    s_matr_resize(m);
    return 0;
}

int s_matr_column_input(s_matr *c, int rows)
{
    c->rows = 1;
    c->columns = rows;
    if (s_matr_alloc(c))
        return 1;

    printf("Input vector with size %d:\n", rows);
    if (s_matr_matrix_input(c))
        return 1;
    s_matr_resize(c);
    return 0;
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
    int buf, zero_line, prev_zero_line = 0;
    for (int i = 0; i < m->rows; ++i)
    {
        zero_line = 1;
        for (int j = 0; j < m->columns; ++j)
        {
            if (scanf("%d", &buf) != 1)
                return 1;

            if (buf !=  0)
            {  
                s_matr_add_elem(m, buf, i, j, zero_line); 
                zero_line = 0;
            }
        }

        for (; prev_zero_line; --prev_zero_line)
            s_matr_add_line(m);
        
         if (zero_line)
            prev_zero_line++;
    }
    s_matr_close(m);
    for (; prev_zero_line; --prev_zero_line)
            s_matr_add_line(m);
    
    return 0; 
}

int s_matr_add_elem(s_matr *m, int buf, int row, int column, int new_line)
{
    m->a[m->a_size] = buf;
    m->ja[m->a_size] = column;
    
    if (new_line)
        m->ia = list_push_back(m->ia, m->a_size);
    
    ++(m->a_size);

    return 0;
}

int s_matr_add_line(s_matr *m)
{
    if (m->a_size == 0)
        m->ia = list_push_back(m->ia, 0);
    else 
        m->ia = list_double_tail(m->ia);;
    return 0;
}

int s_matr_close(s_matr *m)
{
    if (m->a_size > 0)
        m->ia = list_push_back(m->ia, m->a_size);
    return 0;
}

void s_matr_noutput(s_matr m)
{
    int ja_i, ja_end;
    list_t ia = m.ia;
    if (m.a_size)
    {
        for (int i = 0; i < m.rows; ++i, ia = ia->next)
        {
            ja_i = ia->value;
            ja_end = ia->next->value;
            for (int j = 0; j < m.columns; ++j)
            {
                if (m.ja[ja_i] < j && ja_i < ja_end)
                    ++ja_i;

                if (m.ja[ja_i] == j && ja_i < ja_end)
                    printf("%3d ", m.a[ja_i]);
                else 
                    printf("%3d ", 0);
            }
            putchar('\n');
        }
    }
    else
        for (int i = 0; i < m.rows; ++i)
        {
            for (int j = 0; j < m.columns; ++j)
                printf("%3d", 0);
            putchar('\n');
        }
}
