#ifndef __DOT_PRINT_H__
#define __DOT_PRINT_H__

#include <stdio.h>

#include "graph.h"

int dot_print_graph(graph_t *g);

void dot_init(FILE *f);

void dot_write_road(FILE *f, int city1, int city2, int len);

void dot_write_city(FILE *f, int city);

void dot_close(FILE *f);

#endif
