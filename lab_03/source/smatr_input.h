#ifndef _SMATR_INPUT_H_
#define _SMATR_INPUT_H_

#include "smatrix.h"

int s_matr_full_input(s_matr *m);

int s_matr_matrix_input(s_matr *m);

int s_matr_add_elem(s_matr *m, int buf, int row, int column, int new_line);

int s_matr_add_line(s_matr *m);

int s_matr_close(s_matr *m);

#endif
