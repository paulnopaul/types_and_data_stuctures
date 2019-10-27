//
// Created by Павел Чеклин on 22.10.2019.
//

#include "test.h"

#include <stdlib.h>
#include <stdio.h>
#include "time.h"

#include "linked_list.h"
#include "smatrix.h"
#include "matrix.h"


void linked_list_test()
{
    list_t l = NULL;
    puts("CREATE");
    for (size_t i = 0; i < 10; ++i)
        l = list_add_tail(l, i);
    puts("OUTPUT");
    list_output(l);
    list_output(l);
    puts("DELETE");
    list_delete(l);
}

void smatrix_io_test()
{
    rare_matrix m;
    s_matr_full_input(&m);
    s_matr_output(m);
}

