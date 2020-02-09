// Функции для работы со сбалансированными деревьями поиска

#include "../include/btree.h"

void btree_init(dtree_t *root)
{
    root->root = NULL;
}

tree_node_t *btree_create_node(int data)
{
    // key = k; left = right = 0; height = 1;
    tree_node_t *new = (tree_node_t *)malloc(sizeof(tree_node_t));
    if (new)
    {
        new->data = data;
        new->left = new->right = NULL;
        new->height = 1;
    }
    return new;
}

int btree_height(tree_node_t *node)
{
    return node ? (node->height) : 0;
}

int btree_bfactor(tree_node_t *node)
{
    return btree_height(node->right) - btree_height(node->left);
}

void btree_fixheight(tree_node_t *node)
{
    int hl, hr;
    hl = btree_height(node->left);
    hr = btree_height(node->right);
    node->height = ((hl > hr) ? hl : hr) + 1;
}

tree_node_t* btree_rotateright(tree_node_t *node)
{
    tree_node_t *new = node->left;
    node->left = new->right;
    new->right = node;
    btree_fixheight(node);
    btree_fixheight(new);
    return new;
}


tree_node_t* btree_rotateleft(tree_node_t *node)
{
    tree_node_t *new = node->right;
    node->right = new->left;
    new->right = node;
    btree_fixheight(node);
    btree_fixheight(new);
    return new;
}

tree_node_t* btree_balance(tree_node_t *node)
{
    btree_fixheight(node);
    if (btree_bfactor(node) == 2)
    {
            if (btree_bfactor(node->right) < 0)
                node->right = btree_rotateright(node->right);
            return btree_rotateleft(node);
    }
    if (btree_bfactor(node) == -2)
    {
        if (btree_bfactor(node->left) > 0)
            node->left = btree_rotateleft(node->left);
        return btree_rotateright(node);
    }
    return node;
}

tree_node_t* btree_insert(tree_node_t *root, int data)
{
    if (!root)
        return btree_create_node(data);
    if (data < root->data)
        root->left = btree_insert(root->left, data);
    else 
        root->right = btree_insert(root->right, data);
    return btree_balance(root);
}


