#include <stdio.h>
#include <stdlib.h>

#include "../lib/tree.h"

struct node {
    tree_t* left;
    tree_t* right;
    int value;
};

tree_t* tree_create(int value) {
    tree_t* t = malloc(sizeof(tree_t));

    if (t == NULL) {
        fprintf(stderr, "Error: tree_create failed to allocate memory\n");
        exit(1);
    }

    t->left = NULL;
    t->right = NULL;
    t->value = value;

    return t;
}

void tree_insert(tree_t** t, int value) {
    if (*t == NULL) {
        *t = tree_create(value);
        return;
    }

    tree_t* node = *t;

    if (value < node->value) {
        tree_insert(&node->left, value);
        return;
    }

    if (value > node->value) {
        tree_insert(&node->right, value);
        return;
    }
}

void tree_destroy(tree_t* r) {
    if (r == NULL) {
        return;
    }

    tree_destroy(r->left);
    tree_destroy(r->right);
    free(r);
}

tree_t* tree_left(const tree_t* r) {
    if (r == NULL) {
        fprintf(stderr, "Error: tree_left called with NULL tree_t\n");
        exit(1);
    }

    return r->left;
}

tree_t* tree_right(const tree_t* r) {
    if (r == NULL) {
        fprintf(stderr, "Error: tree_right called with NULL tree_t\n");
        exit(1);
    }

    return r->right;
}

bool tree_is_empty(const tree_t* r) {
    return r == NULL;
}

int tree_node_value(const tree_t* r) {
    if (r == NULL) {
        fprintf(stderr, "Error: tree_value called with NULL tree_t\n");
        exit(1);
    }

    return r->value;
}

unsigned tree_len(const tree_t* r) {
    if (r == NULL) {
        return 0;
    }

    return 1 + tree_len(r->left) + tree_len(r->right);
}

unsigned tree_height(const tree_t* r) {
    if (r == NULL) {
        return 0;
    }

    unsigned left_height = tree_height(r->left);
    unsigned right_height = tree_height(r->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

void tree_print_preorder(const tree_t* r);
void tree_print_inorder(const tree_t* r);
void tree_print_postorder(const tree_t* r);
void tree_print(const tree_t* t, tree_traversal_t order) {
    if (t == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    switch (order) {
        case TREE_PREORDER:
            tree_print_preorder(t);
            break;
        case TREE_INORDER:
            tree_print_inorder(t);
            break;
        case TREE_POSTORDER:
            tree_print_postorder(t);
            break;
        default:
            fprintf(stderr, "Error: Unknown traversal order\n");
            exit(1);
    }

    printf("\n");
}

void tree_print_preorder(const tree_t* r) {
    if (r == NULL) {
        return;
    }

    printf("%d ", r->value);
    tree_print_preorder(r->left);
    tree_print_preorder(r->right);
}

void tree_print_inorder(const tree_t* r) {
    if (r == NULL) {
        return;
    }

    tree_print_inorder(r->left);
    printf("%d ", r->value);
    tree_print_inorder(r->right);
}

void tree_print_postorder(const tree_t* r) {
    if (r == NULL) {
        return;
    }

    tree_print_postorder(r->left);
    tree_print_postorder(r->right);
    printf("%d ", r->value);
}
