#ifndef _DTREE_H_
#define _DTREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
    struct node_t *left;
    struct node_t *right;

    int data;
} node_t;

typedef struct dtree_t
{
    node_t *root;
} dtree_t;


node_t* create_node(int data);

int dtree_add_node(dtree_t *root, int data);

void dtree_init(dtree_t *root);

int dtree_delete_node(dtree_t *root, int data); // TODO

int dtree_search(dtree_t *root, int data); // TODO

int dtree_get(dtree_t *root, const char *filename);

int dtree_input(dtree_t *root, FILE *stream);

int dtree_put(dtree_t *root, const char *filename);

int dtree_output(dtree_t *root, FILE *stream);

#endif
