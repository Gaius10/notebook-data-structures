#include <stdio.h>
#include <stdlib.h>
#include "../lib/linked-list.h"

Node* create(int value) {
    Node* n = malloc(sizeof(Node));
    n->value = value;
    n->next = NULL;

    return n;
}

void clear(Node** n) {
    if (*n == NULL) {
        return;
    }

    clear(&(*n)->next);
    (*n)->next = NULL;

    free(*n);
    *n = NULL;
}

int insert_at(Node* n, unsigned pos, int value) {
    unsigned counter = 0;
    while (counter++ < pos - 1) {
        if (n->next == NULL) {
            return -1;
        }

        n = n->next;
    }

    Node* new_node = create(value);
    new_node->next = n->next;
    n->next = new_node;

    return 1;
}

int remove_index(Node* n, unsigned pos, int* value) {
    if (n == NULL) {
        return -1;
    }

    Node* before;
    Node* target;

    unsigned counter = 0;
    while (counter++ < pos - 1) {
        if (n->next == NULL) {
            return -1;
        }

        n = n->next;
    }

    before = n;
    target = n->next;

    before->next = target->next;

    target->next = NULL;
    *value = target->value;
    free(target);

    return 1;
}

int push(Node* n, int value) {
    if (n == NULL) {
        return -1;
    }

    while (n->next != NULL) {
        n = n->next;
    }

    Node* new_node = create(value);
    n->next = new_node;

    return 1;
}

void printl(const Node* n) {
    printf("[");
    printf("%d", n->value);

    while (n->next != NULL) {
        n = n->next;
        printf(",%d", n->value);
    }

    printf("]\n");
}
