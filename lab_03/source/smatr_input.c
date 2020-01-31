#include "smatr_input.h"

#include <stdio.h>
#include <stdlib.h>


int s_matr_full_input(s_matr *m)
{
    int r, c;
    printf("Введите размеры матрицы: ");
    if (!(scanf("%d%d", &r, &c) == 2 && r > 0 && c > 0))
        return 1;
    
    m->rows = r;
    m->columns = c;
    if (s_matr_alloc(m))
        return 1;
    
    puts("Введите матрицу построчно, элементы - целые числа:");
    if (s_matr_matrix_input(m))
        return 1;
    s_matr_resize(m);
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
    int buf, zero_line;
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
        if (zero_line)
            s_matr_add_line(m);
    }
    s_matr_close(m);
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
