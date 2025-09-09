#ifndef STATIC_SEQUENCE_LIST_H
#define STATIC_SEQUENCE_LIST_H

#define SSL_MAX 100
typedef int SSL_Type;

typedef struct {
    SSL_Type items[SSL_MAX];
    unsigned len;
} SSL;

SSL* ssl_create(void);
int ssl_destroy(SSL **l);

int ssl_is_empty(const SSL *l);
int ssl_is_full(const SSL *l);
int ssl_len(const SSL *l);

int ssl_push(SSL *l, SSL_Type item);
int ssl_insert_at(SSL *l, unsigned pos, SSL_Type item);
int ssl_remove_index(SSL *l, unsigned pos, SSL_Type *item);

int ssl_seek(const SSL *l, unsigned pos, SSL_Type *item);
int ssl_search(const SSL *l, SSL_Type item, unsigned *pos);

int ssl_clean(SSL *l);
int ssl_print(const SSL *l);

#endif

