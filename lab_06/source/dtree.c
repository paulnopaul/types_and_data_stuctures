#include "../include/dtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../include/queue.h"

tree_node_t *create_node(int data)
{
    tree_node_t *new = (tree_node_t *)malloc(sizeof(tree_node_t));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}

int dtree_add_node(dtree_t *root, int data)
{
    tree_node_t *buf = root->root;
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
    else
        printf("%d уже добавлено в обычное дерево\n", data);

    printf("Количество сравнений при добавлении в обычное дерево: %d\n", buf->height);
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
    {
        puts("Cant open");
        return 1;
    }
    if (dtree_input(root, f))
    {
        puts("cant input");
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
        {
            puts("cant add");
            return 1;
        }
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
    tree_node_t *buf = root->root;

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

int dtree_delete(dtree_t *root)
{
    queue_t *vertex = NULL;
    tree_node_t *buf = root->root;

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

int dtree_copy(dtree_t *root, dtree_t *new)
{
    queue_t *vertex = NULL;
    tree_node_t *buf = root->root;

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

int dtree_create_balanced(dtree_t *root, dtree_t *broot)
{
    queue_t *vertex = NULL;
    tree_node_t *buf = root->root;
    int c = 0;

    if (!root->root)
        return 0;

    vertex = queue_push(vertex, (void *)buf);
    while (vertex)
    {
        vertex = queue_pop(vertex, (void *)&buf);

        if (buf->left)
            vertex = queue_push(vertex, (void *)buf->left);
        if (buf->right)
            vertex = queue_push(vertex, (void *)buf->right);
        broot->root = btree_node_insert(broot->root, buf->data, &c);
    }
    return 0;
}
