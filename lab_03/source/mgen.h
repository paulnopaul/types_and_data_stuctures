#ifndef __MGEN_H__
#define __MGEN_H__

#include <stdio.h>
#include <time.h>

#define CACHE_MATRIX_FILENAME "../examples/cache.txt"

void filegen_menu();

int filegen(const char *filename, int rows, int columns, int elems, int row_elems);

double generate_prob();

#endif
