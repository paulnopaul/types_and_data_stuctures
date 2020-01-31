#include "../include/dtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/queue.h"

node_t *create_node(int data)
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}

int dtree_add_node(dtree_t *root, int data)
{
    node_t *buf = root->root;
    int height = 1;

    if (root->root == NULL)
    {
        root->root = create_node(data);
        root->root->height = height;
        return 0;
    }

    while (data != buf->data &&
           !((data < buf->data && !buf->left) ||
             (data > buf->data && !buf->right)))
    {
        if (data > buf->data)
            buf = buf->right;
        else
            buf = buf->left;
        height++;
    }

    if (data > buf->data)
    {
        buf->right = create_node(data);
        buf->height = height;
    }
    else if (data < buf->data)
    {
        buf->left = create_node(data);
        buf->height = height;
    }

    return 0;
}

void dtree_init(dtree_t *root)
{
    root->root = NULL;
}

int dtree_get(dtree_t *root, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return 1;
    if (dtree_input(root, f))
    {
        fclose(f);
        return 1;
    }
    fclose(f);
    return 0;
}

int dtree_input(dtree_t *root, FILE *stream)
{
    int buf;
    while (fscanf(stream, "%d", &buf) == 1)
        if (dtree_add_node(root, buf))
            return 1;
    return 0;
}

int dtree_put(dtree_t *root, const char *filename)
{
    char fname[300];
    char command[300];
    snprintf(fname, 299, "../cache/%s.txt", filename);

    FILE *f = fopen(fname, "w");
    if (!f)
        return 1;

    if (dtree_output(root, f))
    {
        fclose(f);
        return 1;
    }
    fclose(f);

    snprintf(command, 299,
             "python3 ../scripts/draw_tree.py ../cache/%s.txt ../cache/%s.gv",
             filename, filename);

    system(command);

    return 0;
}

int dtree_output(dtree_t *root, FILE *stream)
{
    queue_t *vertex = NULL;
    node_t *buf = root->root;

    if (!root->root)
    {
        fprintf(stream, "E\n");
        return 0;
    }

    vertex = queue_push(vertex, (void *)buf);

    while (vertex)
    {
        vertex = queue_pop(vertex, (void *)&buf);

        if (buf->left)
        {
            vertex = queue_push(vertex, (void *)buf->left);
            fprintf(stream, "%d %d\n", buf->data, buf->left->data);
        }
        else
            fprintf(stream, "%d NULL\n", buf->data);

        if (buf->right)
        {
            vertex = queue_push(vertex, (void *)buf->right);
            fprintf(stream, "%d %d\n", buf->data, buf->right->data);
        }
        else
            fprintf(stream, "%d NULL\n", buf->data);
    }
    return 0;
}

int dtree_copy(dtree_t *root, dtree_t *new)
{
    queue_t *vertex = NULL;
    node_t *buf = root->root;

    if (!root->root)
    {
        return 0;
    }
    new->root = create_node(buf->data);

    vertex = queue_push(vertex, (void *)buf);

    while (vertex)
    {
        vertex = queue_pop(vertex, (void *)&buf);

        if (buf->left)
            vertex = queue_push(vertex, (void *)buf->left);
        if (buf->right)
            vertex = queue_push(vertex, (void *)buf->right);
        dtree_add_node(new, buf->data);
    }
    return 0;
}

int dtree_delete(dtree_t *root)
{
    queue_t *vertex = NULL;
    node_t *buf = root->root;

    if (!root->root)
    {
        return 0;
    }

    vertex = queue_push(vertex, (void *)buf);

    while (vertex)
    {
        vertex = queue_pop(vertex, (void *)&buf);

        if (buf->left)
            vertex = queue_push(vertex, (void *)buf->left);
        if (buf->right)
            vertex = queue_push(vertex, (void *)buf->right);
        free(buf);
    }
    return 0;
}

int dtree_balance(dtree_t *root)
{

    root->root = node_balance(root->root);
    return 0;
}

int dtree_create_balanced(dtree_t *src, dtree_t *dst)
{
    dtree_copy(src, dst);
    dtree_balance(dst);
    return 0;
}

int dtree_add_node_balanced(dtree_t *root, int data)
{
    root->root = dtree_insert(root->root, data);
    return 0;
}

int dtree_height(node_t *t)
{
    return t ? t->height : 0;
}

int dtree_bfactor(node_t *t)
{
    return dtree_height(t->right) - dtree_height(t->left);
}

int dtree_fixheight(node_t *t)
{
    int hl, hr;
    hl = dtree_height(t->left);
    hr = dtree_height(t->right);
    return ((hl > hr) ? hl : hr) + 1;
}

node_t *dtree_rotateright(node_t *t)
{
    node_t *p = t->left;
    t->left = p->right;
    p->right = t;

    dtree_fixheight(p);
    dtree_fixheight(t);

    return p;
}

node_t *dtree_rotateleft(node_t *t)
{
    node_t *p = t->right;
    t->right = p->left;
    p->left = t;

    dtree_fixheight(p);
    dtree_fixheight(t);

    return p;
}

node_t *dtree_insert(node_t *t, int data)
{
    if (!t)
        return create_node(data);
    if (data < t->data)
        t->left = dtree_insert(t->left, data);
    else
        t->right = dtree_insert(t->right, data);
    return node_balance(t);
}

node_t *node_balance(node_t *t)
{
    dtree_fixheight(t);
    if (dtree_bfactor(t) == 2)
    {
        if (dtree_bfactor(t->right) < 0)
            t->right = dtree_rotateright(t->right);
        return dtree_rotateleft(t);
    }
    if (dtree_bfactor(t) == -2)
    {
        if (dtree_bfactor(t->left) > 0)
            t->left = dtree_rotateleft(t->left);
        return dtree_rotateright(t);
    }
    return t;
}
