#include "../include/task.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/graph.h"
#include "../include/dijkstra.h"

/*

Задана система двусторонних дорог. 
Найти множество городов, расстояние от которых 
до выделенного города (столицы) больше, чем Т.

Граф задается матрицей смежности
*/

int task_main(const char *filename)
{
    graph_t g;
    task_t t;

    graph_init(&g);
    if (graph_input(&g, filename))
    {
        puts("Ошибка при вводе графа");
        return 1;
    }

    print_info();

    puts("\na");
    graph_output(&g);
    puts("b");

    printf("Введите город-столицу (от 0 до %d): ", g.n - 1);

    if (!(scanf("%d", &t.capital) == 1 && t.capital >= 0 && t.capital < g.n))
    {
        puts("Ошибка при вводе графа");
        return 1;
    }

    printf("Введите расстояние T: ");
    if (!(scanf("%d", &t.t) == 1 && t.t >= 0))
    {
        puts("Ошибка ввода t");
        return 1;
    }

    task_task(g, &t);

    int graph_delete(graph_t * g);
    free(t.cities);

    return 0;
}

int task_task(graph_t g, task_t *t)
{
    int empty = 1;
    t->cities = (int *)malloc(g.n * sizeof(int));
    dijkstra(g, t->capital, t->cities);

    for (int i = 0; i < g.n && empty; ++i)
        if (t->cities[i] != INT_MAX && t->cities[i] != 0 &&
            t->cities[i] > t->t)
            empty = 0;

    if (!empty)
    {
        printf("Город Расстояние\n");
        for (int i = 0; i < g.n; ++i)
            if (t->cities[i] != INT_MAX && t->cities[i] != 0 &&
                t->cities[i] > t->t)
                printf("%d     %d\n", i, t->cities[i]);
    }
    else
        puts("Таких городов не существует");

    return 0;
}

void print_info()
{
    printf("Задана система двухсторонних дорог");
    
}
