#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>

typedef struct graph_t
{
    int n;
    int **g;
} graph_t;

int graph_input(graph_t *g, const char *filename);

int graph_get(graph_t *g, FILE *f);

int graph_init(graph_t *g);

int graph_allocate(graph_t *g);

int graph_output(graph_t *g); // using python function

int graph_delete(graph_t *g);

#endif
