// Функции для работы со сбалансированными деревьями поиска

#include "../include/btree.h"

#include <time.h>

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
    new->left = node;
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

tree_node_t* btree_node_insert(tree_node_t *root, int data, int *cmp)
{
    if (!root)
    {
        return btree_create_node(data);
    }
    ++(*cmp);
    if (data < root->data)
        root->left = btree_node_insert(root->left, data, cmp);
    else if (data == root->data)
    {   
        printf("%d уже добавлено в сбалансированное дерево\n", data);
        return root;
    }
    else 
        root->right = btree_node_insert(root->right, data, cmp);
    return btree_balance(root);
}

int btree_search(tree_node_t *root, int elem, int *cmp)
{
     if (!root)
        return 0;
    ++(*cmp);
    if (elem < root->data)
        return btree_search(root->left, elem, cmp);
    else if (elem == root->data)
        return 1;
    else 
        return btree_search(root->right, elem, cmp);
}

int btree_insert(dtree_t *root, int data)
{
    int cmp = 0;
    root->root = btree_node_insert(root->root, data, &cmp);
    // printf("Количество сравнений при в сбалансированное дерево: %d\n", cmp);
    // return 0;

    return cmp;
}


