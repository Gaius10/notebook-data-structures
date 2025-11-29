
#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node tree_t;

typedef enum {
    TREE_PREORDER,
    TREE_INORDER,
    TREE_POSTORDER
} tree_traversal_t;

tree_t* tree_create(int value);
void tree_insert(tree_t** t, int value);

void tree_destroy(tree_t* r);
bool tree_is_empty(const tree_t* r);

int tree_node_value(const tree_t* r);
unsigned tree_len(const tree_t* r);
unsigned tree_height(const tree_t* r);

tree_t* tree_left(const tree_t* r);
tree_t* tree_right(const tree_t* r);

void tree_print(const tree_t* r, tree_traversal_t order);

#endif
