#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

struct node {
    uint8_t digits[4];
    struct node *next;
};

typedef struct bigint {
    struct node *high, *low;
    size_t length;
    int8_t sign;
} bigint_t;

typedef enum {
    BIGINT_STATUS_OK,
    BIGINT_STATUS_MEM,
    BIGINT_STATUS_BAD_DIGIT,
    BIGINT_STATUS_UNDERFLOW,
} bigint_status_t;

/***********************
 * Criacao e destruição
 */

bigint_t* bigint_create(void);

[[gnu::nonnull]]
bigint_t* bigint_create_from_string(const char *str);

[[gnu::nonnull]]
bigint_status_t bigint_copy(bigint_t* target, const bigint_t* source);

[[gnu::nonnull]]
void bigint_destroy(bigint_t **num);

/***********************
 * Manipulação
 */

[[gnu::nonnull]]
bigint_status_t bigint_push_high_digit(bigint_t *num, uint8_t digit);

[[gnu::nonnull(1)]]
bigint_status_t bigint_pop_high_digit(bigint_t *num, uint8_t *digit);

[[gnu::nonnull]]
void bigint_zero(bigint_t *num);

[[gnu::nonnull]]
size_t bigint_length(const bigint_t *num);

/***********************
 * Formatação
 */

[[gnu::nonnull]]
char* bigint_to_string(const bigint_t* num);

/***********************
 * Iteração
 */

[[gnu::nonnull(1, 2)]]
void bigint_iter(
    const bigint_t *num,
    void (*callback)(uint8_t, void *),
    void *userdata
);

/// Itera sobre os dígitos de dois bigint_t.
[[gnu::nonnull(1, 2, 3)]]
void bigint_iter2(
    const bigint_t *num_a,
    const bigint_t *num_b,
    void (*callback)(uint8_t, uint8_t, void *),
    void *userdata
);

