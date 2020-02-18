#include "../include/dot_print.h"

#include <stdio.h>
#include <stdlib.h>

void dot_init(FILE *f)
{
    fprintf(f, "graph {\n");
}

void dot_write_road(FILE *f, int city1, int city2, int len)
{
    fprintf(f, "%d -- %d [label=\"%d\", weight=\"%d\"]\n", city1, city2, len, len);
}

void dot_write_city(FILE *f, int city)
{
    fprintf(f, "%d\n", city);
}

void dot_close(FILE *f)
{
    fprintf(f, "}\n");
}

int dot_print_graph(graph_t *g)
{
    FILE *f = fopen("./cache/graph.a", "w");

    dot_init(f);

    for (int i = 0; i < g->n; ++i)
        dot_write_city(f, i);

    for (int i = 0; i < g->n; ++i)
        for (int j = 0; j < g->n; ++j)
            if (g->g[i][j] != -1 && i > j)
                dot_write_road(f, i, j, g->g[i][j]);
    
    dot_close(f);
    fclose(f);
    system("python3 ./source/viewdot.py graph.a");
    return 0;
}
