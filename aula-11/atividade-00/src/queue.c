#include <stdlib.h>
#include <stdio.h>
#include "../lib/queue.h"

Queue* create_queue() {
    Queue* q = malloc(sizeof(Queue));
    if (q == NULL) {
        return NULL;
    }

    q->start = 0;
    q->end = 0;

    return q;
}

int insert(Queue *q, int value) {
    if (q == NULL) {
        return -1;
    }

    if (q->end >= QUEUE_MAX) {
        return -1;
    }

    q->items[q->end] = value;
    q->end++;

    return 1;
}

int shift(Queue *q, int *buffer) {
    if (q == NULL) {
        return -1;
    }

    if (q->start >= q->end) {
        return -1;
    }

    *buffer = q->items[q->start];
    q->start++;

    return 1;
}

void print_queue(Queue *q) {
    for (unsigned i = q->start; i < q->end; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

void free_queue(Queue **q) {
    free(*q);
    *q = NULL;
}

