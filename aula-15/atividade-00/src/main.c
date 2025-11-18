#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ATOM = 0,
    LIST = 1
} NodeType;

typedef struct node {
    NodeType type;

    union {
        int atom;
        struct node *list;
    } head;

    struct node *tail;
} node_t;

node_t *new_atom(int v);
node_t *new_list(node_t *first_elem);
node_t *append(node_t *head, node_t *elem);

int parse_int(char **s);
node_t *parse_element(char **s);
node_t *parse_list(char **s);
node_t *parse_element(char **s);
node_t *parse_list(char **s);

void print_node(node_t *n);
void print_list_elems(node_t *n);
void print_node_levels(node_t *n);

void free_node(node_t *n);

node_t *new_atom(int v) {
    node_t *n = (node_t*)malloc(sizeof(node_t));
    n->type = ATOM;
    n->head.atom = v;
    n->tail = NULL;
    return n;
}

node_t *new_list(node_t *first_elem) {
    node_t *n = (node_t*)malloc(sizeof(node_t));
    n->type = LIST;
    n->head.list = first_elem;
    n->tail = NULL;
    return n;
}

node_t *append(node_t *head, node_t *elem) {
    if (head == NULL) {
        return elem;
    } else {
        node_t *cur = head;
        while (cur->tail != NULL) {
            cur = cur->tail;
        }
        cur->tail = elem;
        return head;
    }
}

int parse_int(char **s) {
    int sign = 1;
    int val = 0;

    if (**s == '-') {
        sign = -1;
        (*s)++;
    }

    while (**s >= '0' && **s <= '9') {
        val = val * 10 + (**s - '0');
        (*s)++;
    }

    return sign * val;
}

node_t *parse_element(char **s) {
    if (**s == '(') {
        return parse_list(s);
    } else {
        int v = parse_int(s);
        return new_atom(v);
    }
}

node_t *parse_list(char **s) {
    (*s)++;

    node_t *level_head = NULL;

    if (**s == ')') {
        (*s)++;
        return new_list(NULL);
    }

    node_t *elem = parse_element(s);
    level_head = append(level_head, elem);

    while (**s == ',') {
        (*s)++;
        node_t *next_elem = parse_element(s);
        level_head = append(level_head, next_elem);
    }

    if (**s == ')') {
        (*s)++;
    }

    return new_list(level_head);
}

void print_list_elems(node_t *n) {
    node_t *cur = n;
    while (cur != NULL) {
        print_node(cur);
        if (cur->tail != NULL) {
            printf(",");
        }
        cur = cur->tail;
    }
}

void print_node(node_t *n) {
    if (n == NULL) {
        printf("()");
        return;
    }

    if (n->type == ATOM) {
        printf("%d", n->head.atom);
    } else {
        printf("(");
        print_list_elems(n->head.list);
        printf(")");
    }
}

unsigned get_max_level(node_t *n) {
    if (n == NULL) return 0;

    unsigned head_max = 0;
    unsigned tail_max = 0;

    if (n->type == ATOM) head_max += 0;
    if (n->type == LIST) head_max += 1 + get_max_level(n->head.list);

    tail_max += get_max_level(n->tail);

    return head_max > tail_max ? head_max : tail_max;
}

void print_node_levels(node_t *n) {
    unsigned level = get_max_level(n);
    printf("%d\n", level - 1);
}

void free_node(node_t *n) {
    if (n == NULL) return;

    if (n->type == LIST) {
        node_t *sub = n->head.list;
        while (sub != NULL) {
            node_t *next = sub->tail;
            free_node(sub);
            sub = next;
        }
    }

    free(n);
}

int main() {
    char buffer[1024];

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return 1;
    }

    char *ptr = buffer;

    node_t *root = parse_list(&ptr);
    print_node_levels(root);

    free_node(root);
    return 0;
}
