// Набор функций для работы со сбалансированными деревьями поиска
#ifndef __BTREE_H__
#define __BTREE_H__

#include <stdio.h>
#include <stdlib.h>

#include "dtree.h"

typedef struct tree_node_t tree_node_t;
typedef struct dtree_t dtree_t;

void btree_init(dtree_t *root);

tree_node_t* btree_create_node(int data);

int btree_height(tree_node_t *node);

int btree_bfactor(tree_node_t *node);

void btree_fixheight(tree_node_t *node);

tree_node_t* btree_rotateright(tree_node_t *node);

tree_node_t* btree_rotateleft(tree_node_t *node);

tree_node_t* btree_balance(tree_node_t *node);

tree_node_t* btree_insert(tree_node_t *root, int data);


#endif
