#include "../include/dot_print.h"

#include <stdio.h>

void dot_init(FILE *f)
{
    fprintf(f, "graph {\n");
}

void dot_write_line(FILE *f, int city1, int city2, double len)
{
    fprintf(f, "%d -- %d [label=\"%.2lf\", weight=\"%.2lf\"\n", city1, city2, len, len);
}

void dot_close(FILE *f)
{
    fprintf(f, "}\n");
}
