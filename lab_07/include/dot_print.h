#ifndef __DOT_PRINT_H__
#define __DOT_PRINT_H__

#include <stdio.h>

void dot_init(FILE *f);

void dot_write_line(FILE *f, int city1, int city2, double len);

void dot_close(FILE *f);

#endif
