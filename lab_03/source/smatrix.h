/*
Чеклин Павел ИУ7-32Б
Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:
- вектор A содержит значения ненулевых элементов;
- вектор JA содержит номера столбцов для элементов вектора A;
- связный список IA, в элементе Nk которого находится номер компонент в A и JA, с которых начинается
описание строки Nk матрицы A.
 */

#ifndef _SMATRIX_H_
#define _SMATRIX_H_

#include <stdio.h>
#include "linked_list.h"

typedef struct s_matr
{
    // source matrix sizes
    int rows;
    int columns;

    // rare matrix params
    size_t a_size; // a size is equal to ja size 
    int *a;
    size_t *ja;
    list_t ia;

} s_matr;

void s_matr_init(s_matr *m);

// выделение памяти под разреженную матрицу
// s_matr *s_matr_alloc(size_t rows, size_t columns);
int s_matr_alloc(s_matr *m);

// ввод матрицы
int s_matr_matrix_input(s_matr * m);

// добавление элемента в разреженную матрицу (в конец)
int s_matr_add_elem(s_matr * m, size_t row, size_t column, int elem);

// сокращение матрицы
int s_matr_resize(s_matr * m);

// полный ввод матрицы
int s_matr_input(s_matr *m);

// вывод матрицы
int s_matr_output(s_matr *m);

void s_matr_delete(s_matr *m);


#endif
