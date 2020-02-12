//
// Created by Павел Чеклин on 12.10.2019.
//

#ifndef _matr_H_
#define _matr_H_

typedef struct
{
    int rows;
    int columns;
    int **matr;
} matr;

int matr_init(matr *m);

int matr_allocate(matr *m);

int matr_input(matr *m);

void matr_output(matr m);

int matr_matr_input(matr *m);

int matr_product(matr m1, matr m2, matr *res);

int matr_delete(matr *m);


#endif //LAB_03_matr_H
