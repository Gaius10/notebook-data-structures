
#ifndef LL_H
#define LL_H

#define LL_MAX_LEN 1000

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* create(int value);
void clear(Node** n);

int insert_at(Node* n, unsigned pos, int value);
int remove_index(Node* n, unsigned pos, int* value);

int push(Node* n, int value);
void printl(const Node* n);

#endif

