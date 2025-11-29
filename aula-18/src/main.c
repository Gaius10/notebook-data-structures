#include <stdio.h>
#include <stdlib.h>

#include "../lib/tree.h"

int main() {
    unsigned n = 0;
    tree_t* tree = NULL;

    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Error reading number of elements\n");
        return 1;
    }

    for (unsigned i = 0; i < n; i++) {
        int value = 0;

        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Error reading element %u\n", i);
            tree_destroy(tree);
            return 1;
        }

        if (tree == NULL) {
            tree = tree_create(value);
            continue;
        }

        tree_insert(&tree, value);
    }

    tree_print(tree, TREE_PREORDER);
    tree_print(tree, TREE_INORDER);
    tree_print(tree, TREE_POSTORDER);
    tree_destroy(tree);
}
