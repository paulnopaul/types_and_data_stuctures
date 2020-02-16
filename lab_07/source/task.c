#include "../include/task.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/graph.h"


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
    void print_info();

    printf("Введите город-столицу: ");

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

    int graph_delete(graph_t *g);

    return 0;
}

int task_task(graph_t g, task_t *t)
{
    t->cities = (int *)malloc(g.n * sizeof(int));

    
    return 0;
}
