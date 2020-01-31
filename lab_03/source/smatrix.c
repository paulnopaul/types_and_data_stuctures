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

    
    return 0;
}

// умножение матрицы на вектор-стобец (вектор-стобец хрнавится как вертикальный
// столбец матрицы)
int s_matr_column_prod(s_matr matrix, s_matr column, s_matr *res)
{

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
