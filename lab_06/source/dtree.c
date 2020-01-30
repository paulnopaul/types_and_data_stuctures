#include "../include/dtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/queue.h"

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

node_t *create_node(int data)
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void dtree_init(dtree_t *root)
{
    root->root = NULL;
}

int dtree_add_node(dtree_t *root, int data)
{
    node_t *buf = root->root;
    if (root->root == NULL)
    {
        root->root = create_node(data);
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
    }

    if (data > buf->data)
        buf->right = create_node(data);
    else if (data < buf->data)
        buf->left = create_node(data);

    return 0;
}

int dtree_put(dtree_t *root, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
        return 1;

    if (dtree_output(root, f))
    {
        fclose(f);
        return 1;
    }
    fclose(f);
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
