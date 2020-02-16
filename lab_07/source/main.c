#include <stdio.h>

/*

Задана система двусторонних дорог. 
Найти множество городов, расстояние от которых 
до выделенного города ( столицы ) больше, чем Т.

Граф задается матрицей смежности
*/

#include "../include/graph.h"

void graph_test();

int main()
{
    graph_test();
    return 0;
}

void graph_test()
{
    graph_t g;
    graph_init(&g);
    graph_input(&g, "../example/graph1.txt");
    graph_output(&g);
    graph_delete(&g);
}
