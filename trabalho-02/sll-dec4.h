#pragma once

#include <stddef.h>

#include "ll.h"
#include "dec4.h"

typedef struct node_dec4 {
  dec4_t value;
  struct node_dec4 *next;
} node_dec4_t;

typedef struct {
  node_dec4_t *head, *tail;
  size_t size;
} sll_dec4_t;


[[gnu::nonnull(1)]]
void sll_dec4_init(sll_dec4_t *list);

sll_dec4_t *sll_dec4_create(void);

[[gnu::nonnull(1)]]
void sll_dec4_clear(sll_dec4_t *list);

[[gnu::nonnull(1)]]
void sll_dec4_destroy(sll_dec4_t **list);

[[gnu::nonnull(1)]]
ll_status_t sll_dec4_push(sll_dec4_t *list, dec4_t value);

[[gnu::nonnull(1)]]
ll_status_t sll_dec4_pop(sll_dec4_t *list, dec4_t *value);

[[gnu::nonnull(1, 2)]]
void sll_dec4_iter(const sll_dec4_t *list, void (*callback)(dec4_t, void*), void* ud);

[[gnu::nonnull(1, 2)]]
void sll_dec4_iter_mut(sll_dec4_t *list, void (*callback)(dec4_t*, void*), void* ud);

[[gnu::nonnull(1)]]
ll_status_t sll_dec4_head(const sll_dec4_t *list, dec4_t *value);

[[gnu::nonnull(1)]]
ll_status_t sll_dec4_tail(const sll_dec4_t *list, dec4_t *value);

[[gnu::nonnull(1)]]
size_t sll_dec4_length(const sll_dec4_t *list);
