//
// Created by Павел Чеклин on 12.10.2019.

//

#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

int matrix_init(matrix *m)
{
    m->matrix = NULL;
    m->rows = 0;
    m->columns = 0;
    return EXIT_SUCCESS;
}

int matrix_allocate(matrix *m)
{
    m->matrix = malloc(m->rows * sizeof(int *));
    if (!m->matrix)
        return EXIT_FAILURE;
    for (int i = 0; i < m->columns; ++i)
        if (!(m->matrix[i] = calloc(m->columns, sizeof(int))))
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int matrix_input(matrix *m)
{
    printf("Input rows count: "); 
    if (scanf("%d", &m->rows) == 1 && m->rows > 0 && m->rows < 1000)
    {
        printf("Input columns count: ");
        if (scanf("%d", &m->columns) == 1 && m->columns > 0 && m->columns < 1000)
            return matrix_matrix_input(m);
    }
    return EXIT_FAILURE;
}

void matrix_output(matrix m)
{
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.columns; ++j)
            printf("%3d ", m.matrix[i][j]);
        putchar('\n');
    }
}

int matrix_matrix_input(matrix *m)
{
    matrix_allocate(m);
    
    // input
        puts("Input matrix");
        for (int i = 0; i < m->rows; ++i)
            for (int j = 0; j < m->columns; ++j)
                if (scanf("%d", &m->matrix[i][j]) != 1)
                    return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int matrix_product(matrix m1, matrix m2, matrix *res)
{
    if (m1.columns != m2.rows)
        return EXIT_FAILURE;
    
    res->rows = m1.rows;
    res->columns = m2.columns;

    if (matrix_allocate(res) == EXIT_FAILURE)
        return EXIT_FAILURE;
    
    for (int i1 = 0; i1 < m1.rows; ++i1)
        for (int i2 = 0; i2 < m2.columns; ++i2)
            for (int i3 = 0; i3 < m1.columns; ++i3)
                res->matrix[i1][i2] += m1.matrix[i1][i3] * m2.matrix[i3][i2];

    return EXIT_SUCCESS;
}

int matrix_delete(matrix *m)
{
    for (int i = 0; i < m->rows; ++i)
        free(m->matrix[i]);
    free(m->matrix);
    m->rows = 0;
    m->columns = 0;
    return EXIT_SUCCESS;
}

