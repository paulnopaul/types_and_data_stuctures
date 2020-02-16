#ifndef __TASK_H__
#define __TASK_H__

#include "graph.h"

typedef struct task_t
{
    int capital;
    int t;
    int *cities;
} task_t;

int task_main(const char *filename);

int task_task(graph_t g, task_t *t);

void print_info();

#endif
