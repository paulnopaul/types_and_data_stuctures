#ifndef __DTREE_H__
#define __DTREE_H__

#include <stdio.h>
#include <stdlib.h>

#include "btree.h"

typedef struct tree_node_t
{
    struct tree_node_t *left;
    struct tree_node_t *right;

    int data;
    int height;
} tree_node_t;

typedef struct dtree_t
{
    tree_node_t *root;
} dtree_t;


tree_node_t* create_node(int data);

int dtree_add_node(dtree_t *root, int data);

void dtree_init(dtree_t *root);

int dtree_get(dtree_t *root, const char *filename);

int dtree_input(dtree_t *root, FILE *stream);

int dtree_put(dtree_t *root, const char *filename);

int dtree_output(dtree_t *root, FILE *stream);

int dtree_delete(dtree_t *root);

// balancedь

int dtree_copy(dtree_t *root, dtree_t *new);

int dtree_create_balanced(dtree_t *root, dtree_t *broot);

#endif
