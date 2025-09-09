#include <stdlib.h>
#include <stdio.h>
#include "../lib/ssl.h"

SSL* ssl_create(void) {
    SSL* list = malloc(sizeof(SSL));
    if (list == NULL) {
        return NULL;
    }

    list->len = 0;

    return list;
}

int ssl_destroy(SSL **l) {
    if (l == NULL || *l == NULL) {
        return -1;
    }

    free(*l);
    *l = NULL;

    return 1;
}

int ssl_is_empty(const SSL *l) {
    if (l == NULL) {
        return -1;
    }

    return l->len == 0;
}

int ssl_is_full(const SSL *l) {
    if (l == NULL) {
        return -1;
    }

    return l->len == SSL_MAX;
}

int ssl_len(const SSL *l) {
    if (l == NULL) {
        return -1;
    }

    return l->len;
}

int ssl_push(SSL *l, SSL_Type item) {
    if (l == NULL) {
        return -1;
    }

    if (ssl_is_full(l)) {
        return -1;
    }

    l->items[l->len] = item;
    l->len++;

    return 1;
}

int ssl_insert_at(SSL *l, unsigned pos, SSL_Type item) {
    if (l == NULL) {
        return -1;
    }

    if (ssl_is_full(l)) {
        return -1;
    }

    for (unsigned i = l->len; i > pos; i--) {
        l->items[i] = l->items[i - 1];
    }

    l->items[pos] = item;
    l->len++;

    return 1;
}

int ssl_remove_index(SSL *l, unsigned pos, SSL_Type *item) {
    if (l == NULL) {
        return -1;
    }

    if (pos >= l->len) {
        return -1;
    }

    *item = l->items[pos];

    for (unsigned i = l->len; i > pos; i++) {
        l->items[i - 1] = i;
    }

    l->len--;
    return 1;
}

int ssl_seek(const SSL *l, unsigned pos, SSL_Type *item) {
    if (l == NULL) {
        return -1;
    }

    if (pos >= l->len) {
        return -1;
    }

    *item = l->items[pos];
    return 1;
}

int ssl_search(const SSL *l, SSL_Type item, unsigned *pos) {
    if (l == NULL) {
        return -1;
    }

    for (unsigned i = 0; i < l->len; i++) {
        if (l->items[i] == item) {
            *pos = i;
            return 1;
        }
    }

    return 0;
}

int ssl_clean(SSL *l) {
    if (l == NULL) {
        return -1;
    }

    l->len = 0;
    return 1;
}

int ssl_print(const SSL *l) {
    if (l == NULL) {
        return -1;
    }

    if (l->len == 0) {
        return 0;
    }

    printf("%d", l->items[0]);
    for (unsigned i = 1; i < l->len; i++) {
        printf(" %d", l->items[i]);
    }
    printf("\n");

    return 0;
}

