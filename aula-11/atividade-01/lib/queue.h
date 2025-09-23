
#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_MAX 1000

typedef struct {
    int items[QUEUE_MAX];
    unsigned start;
    unsigned end;
} Queue;

Queue* create_queue(void);

int insert(Queue *q, int value);
int shift(Queue *q, int* value);

void print_queue(Queue *q);
void free_queue(Queue **q);

#endif

