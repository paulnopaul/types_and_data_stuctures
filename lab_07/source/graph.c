#include "../include/graph.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/dot_print.h"

int graph_init(graph_t *g)
{
    g->n = 0;
    g->g = NULL;
    return 0;
}

int graph_input(graph_t *g, const char *filename)
{
    FILE *f = fopen(filename, "r");
    int err;
    if (!f)
        return 1;
    
    err = graph_get(g, f);
    fclose(f);
    return err;
}

int graph_get(graph_t *g, FILE *f)
{
    int buf;
    if (!(fscanf(f, "%d", &g->n) == 1 && g->n > 0))
        return 1;
    
    graph_allocate(g);
    for (int i = 0; i < g->n; ++i)
        for (int j = 0; j < g->n; ++j)
            if (fscanf(f, "%d", &buf) == 1 && buf >= -1 && buf != 0)
                g->g[i][j] = buf;
            else 
            {
                graph_delete(g);
                return 1;
            }

    return 0;
}

int graph_allocate(graph_t *g)
{
    g->g = (int **)malloc(g->n * sizeof(int *));
    for (int i = 0; i < g->n; ++i)
        g->g[i] = (int *)malloc(g->n * sizeof(int));
    return 0;
}

int graph_delete(graph_t *g)
{
    for (int i = 0; i < g->n; ++i)
        free(g->g[i]);
    free(g->g);
    g->n = 0;
    return 0;
}

int graph_output(graph_t *g)
{
    /*for (int i = 0; i < g->n; ++i)
    {
        for (int j = 0; j < g->n; ++j)
            printf("%d ", g->g[i][j]);
        printf("\n");
    }*/
    dot_print_graph(g);
    return 0;
} // using python function
