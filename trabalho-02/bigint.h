#pragma once

#include "ll.h"
#include "sll-dec4.h"

typedef struct {
  sll_dec4_t list;
} bigint_t;

typedef enum {
  BIGINT_STATUS_OK = LL_STATUS_OK,
  BIGINT_STATUS_MEM = LL_STATUS_MEM,
  BIGINT_STATUS_DIGIT
} bigint_status_t;

bigint_t *bigint_create(void);

[[gnu::nonnull]]
void bigint_destroy(bigint_t **bigint);

[[gnu::nonnull, gnu::null_terminated_string_arg(1)]]
bigint_t *bigint_create_from_string(const char *str);

[[gnu::nonnull]]
bigint_status_t bigint_add(const bigint_t *a, const bigint_t *b,
                           bigint_t *result);

[[gnu::nonnull]]
bigint_status_t bigint_push_low_digit(bigint_t *a, uint8_t digit);

[[gnu::nonnull]]
bigint_status_t bigint_sub(const bigint_t *a, const bigint_t *b,
                           bigint_t *result);

[[gnu::nonnull]]
int bigint_cmp(const bigint_t *a, const bigint_t *b);

[[gnu::nonnull]]
char *bigint_to_string(const bigint_t *bigint);
