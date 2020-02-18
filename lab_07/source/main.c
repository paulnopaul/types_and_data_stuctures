#include <stdio.h>

/*

Задана система двусторонних дорог. 
Найти множество городов, расстояние от которых 
до выделенного города ( столицы ) больше, чем Т.

Граф задается матрицей смежности
*/

#include "../include/graph.h"
#include "../include/task.h"

void graph_test();

int main(int argc, char **argv)
{
    if (argc == 2)
        task_main(argv[1]);
    else 
        printf("app.exe <filename>\n");
    return 0;
}

void graph_test()
{
    graph_t g;
    graph_init(&g);
    graph_input(&g, "./example/graph1.txt");
    graph_output(&g);
    graph_delete(&g);
}
