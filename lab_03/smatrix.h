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


typedef struct
{
    size_t size;
    int *a;
    int *ja;
    linked_list ia;

} smatrix;

// объявление матрицы
int smatrix_malloc(smatrix *m, size_t size);




#endif
