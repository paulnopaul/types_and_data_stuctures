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
    {
        printf("%s не открывается\n", filename);
        return 1;
    }
    err = graph_get_for_silantyeva(g, f);
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

int graph_get_for_silantyeva(graph_t *g, FILE *f)
{
    int left, right, len;
    if (!(fscanf(f, "%d", &g->n) == 1 && g->n > 0 && g->n < 1000))
        return 1;
    if (graph_allocate(g))
        return 1;

    for (int i = 0; i < g->n; ++i)
    {
        for (int j = 0; j < g->n; ++j)
            g->g[i][j] = -1;
        g->g[i][i] = 0;
    }

    while (fscanf(f, "%d%d%d", &left, &right, &len) == 3 &&
           (left >= 0 && left < g->n) && 
           (right >= 0 && right < g->n) &&
           right != left && (len > 0))
    {
        g->g[left][right] = len;
        g->g[right][left] = len;
    }
    return 0;
}

int graph_allocate(graph_t *g)
{
    g->g = (int **)malloc(g->n * sizeof(int *));
    if (!g->g)
        return 1;
    for (int i = 0; i < g->n; ++i)
        if (!(g->g[i] = (int *)malloc(g->n * sizeof(int))))
            return 1;
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
    for (int i = 0; i < g->n; ++i)
    {
        for (int j = 0; j < g->n; ++j)
            printf("%d ", g->g[i][j]);
        printf("\n");
    }

    dot_print_graph(g);
    return 0;
} // using python function
