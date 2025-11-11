#include "sll-dec4.h"

#include <stdlib.h>

void sll_dec4_init(sll_dec4_t *list) {
  list->head = nullptr;
  list->tail = nullptr;
  list->size = 0;
}

sll_dec4_t *sll_dec4_create(void) {
  sll_dec4_t *list = malloc(sizeof(sll_dec4_t));

  if (list == nullptr) {
    return nullptr;
  }

  sll_dec4_init(list);

  return list;
}

void sll_dec4_clear(sll_dec4_t *list) {
  node_dec4_t *current = list->head;

  while (current != nullptr) {
    node_dec4_t *next = current->next;
    free(current);
    current = next;
  }

  list->head = nullptr;
  list->tail = nullptr;
  list->size = 0;
}

void sll_dec4_destroy(sll_dec4_t **list) {
  sll_dec4_clear(*list);

  free(list);
  *list = nullptr;
}

/// Returns:
/// - LL_STATUS_OK: Operation successful.
/// - LL_STATUS_MEM: Memory allocation failed.
ll_status_t sll_dec4_push(sll_dec4_t *list, dec4_t value) {
  node_dec4_t *new_node = malloc(sizeof(node_dec4_t));

  if (new_node == nullptr) {
    return LL_STATUS_MEM;
  }

  new_node->value = value;
  new_node->next = nullptr;

  if (list->head == nullptr) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
  }

  list->size++;

  return LL_STATUS_OK;
}

ll_status_t sll_dec4_pop(sll_dec4_t *list, dec4_t *value) {
  if (list->head == nullptr) {
    return LL_STATUS_EMPTY;
  }

  node_dec4_t *node = list->head;
  *value = node->value;

  list->head = node->next;
  free(node);
  list->size--;

  return LL_STATUS_OK;
}

void sll_dec4_iter(const sll_dec4_t *list,
                     void (*callback)(dec4_t, void *), void *userdata) {
  node_dec4_t *current = list->head;

  while (current != nullptr) {
    callback(current->value, userdata);
    current = current->next;
  }
}

void sll_dec4_iter_mut(sll_dec4_t *list,
                     void (*callback)(dec4_t*, void *), void *userdata) {
  node_dec4_t *current = list->head;

  while (current != nullptr) {
    callback(&current->value, userdata);
    current = current->next;
  }
}

ll_status_t sll_dec4_head(const sll_dec4_t *list, dec4_t *value) {
  if (list->head == nullptr) {
    return LL_STATUS_EMPTY;
  }

  if (value != nullptr) {
    *value = list->head->value;
  }

  return LL_STATUS_OK;
}

ll_status_t sll_dec4_tail(const sll_dec4_t *list, dec4_t *value) {
  if (list->tail == nullptr) {
    return LL_STATUS_EMPTY;
  }

  if (value != nullptr) {
    *value = list->tail->value;
  }

  return LL_STATUS_OK;
}

size_t sll_dec4_length(const sll_dec4_t *list) {
  return list->size;
}
