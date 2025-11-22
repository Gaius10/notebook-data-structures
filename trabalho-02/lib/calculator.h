#pragma once

#include "bigint.h"

[[gnu::nonnull]]
bigint_status_t bigint_add(const bigint_t* a, const bigint_t* b, bigint_t* result);

[[gnu::nonnull]]
int8_t bigint_cmp(const bigint_t* a, const bigint_t* b);
