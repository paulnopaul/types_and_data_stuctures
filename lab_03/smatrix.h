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
    int* a;
    int* ja;
    list_t ia;
} s_matr;

typedef s_matr *rare_matrix;

// выделение памяти под разреженную матрицу
int s_matr_alloc(rare_matrix m, size_t rows, size_t columns);


// полный ввод матрицы
int s_matr_full_input(rare_matrix m);



#endif
