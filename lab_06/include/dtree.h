#ifndef _DTREE_H_
#define _DTREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
    struct node_t *left;
    struct node_t *right;

    int data;
    int height;
} node_t;

typedef struct dtree_t
{
    node_t *root;
} dtree_t;


node_t* create_node(int data);

int dtree_add_node(dtree_t *root, int data);

void dtree_init(dtree_t *root);

int dtree_get(dtree_t *root, const char *filename);

int dtree_input(dtree_t *root, FILE *stream);

int dtree_put(dtree_t *root, const char *filename);

int dtree_output(dtree_t *root, FILE *stream);

int dtree_delete(dtree_t *root);

// balancedь

int dtree_copy(dtree_t *root, dtree_t *new);

int dtree_balance(dtree_t *root);

int dtree_create_balanced(dtree_t *src, dtree_t *dst);

int dtree_add_node_balanced(dtree_t *root, int data);

int dtree_height(node_t *t);

int dtree_bfactor(node_t *t);

int dtree_fixheight(node_t *t);

node_t *dtree_rotateright(node_t *t);

node_t *dtree_rotateleft(node_t *t);

#endif
