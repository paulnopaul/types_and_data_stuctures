//
// Created by Павел Чеклин on 12.10.2019.

//

#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

int matr_init(matr *m)
{
    m->matr = NULL;
    m->rows = 0;
    m->columns = 0;
    return EXIT_SUCCESS;
}

int matr_allocate(matr *m)
{
    m->matr = malloc(m->rows * sizeof(int *));
    if (!m->matr)
        return EXIT_FAILURE;
    for (int i = 0; i < m->columns; ++i)
        if (!(m->matr[i] = calloc(m->columns, sizeof(int))))
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void matr_output(matr m)
{
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.columns; ++j)
            printf("%3d ", m.matr[i][j]);
        putchar('\n');
    }
}

int matr_product(matr m1, matr m2, matr *res)
{
    if (m1.columns != m2.rows)
        return EXIT_FAILURE;
    
    res->rows = m1.rows;
    res->columns = m2.columns;

    if (matr_allocate(res) == EXIT_FAILURE)
        return EXIT_FAILURE;
    
    for (int i1 = 0; i1 < m1.rows; ++i1)
        for (int i2 = 0; i2 < m2.columns; ++i2)
            for (int i3 = 0; i3 < m1.columns; ++i3)
                res->matr[i1][i2] += m1.matr[i1][i3] * m2.matr[i3][i2];

    return EXIT_SUCCESS;
}

int matr_delete(matr *m)
{
    for (int i = 0; i < m->rows; ++i)
        free(m->matr[i]);
    free(m->matr);
    m->rows = 0;
    m->columns = 0;
    return EXIT_SUCCESS;
}

