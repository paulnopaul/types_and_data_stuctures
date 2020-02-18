#include "../include/dijkstra.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int dijkstra(graph_t g, int v, int *res)
{
    int *vis = (int *)calloc(g.n, sizeof(int));

    for (int i = 0; i < g.n; ++i)
        res[i] = INT_MAX;
    res[v] = 0;

    for (int i = 0; i < g.n; ++i)
    {
        int v = -1;
        for (int j = 0; j < g.n; ++j)
            if (!vis[j] && (v == -1 || res[j] < res[v]))
                v = j;
        if (res[v] == INT_MAX)
            break;
        vis[v] = 1;

        for (int j = 0; j < g.n; ++j)
            if (g.g[j][v] > 0)
            {
                int to = j, len = g.g[j][v];
                if (res[v] + len < res[to])
                    res[to] = res[v] + len;
            }
    }

    free(vis);
    return 0;
}

