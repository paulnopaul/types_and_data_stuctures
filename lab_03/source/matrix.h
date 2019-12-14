//
// Created by Павел Чеклин on 12.10.2019.
//

#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct
{
    int rows;
    int columns;
    int **matrix;
} matrix;

int matrix_init(matrix *m);

int matrix_allocate(matrix *m);

int matrix_input(matrix *m);

void matrix_output(matrix m);

int matrix_matrix_input(matrix *m);

int matrix_product(matrix m1, matrix m2, matrix *res);

int matrix_delete(matrix *m);

#endif //LAB_03_MATRIX_H
