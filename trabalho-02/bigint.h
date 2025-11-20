#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct bigint bigint_t;

typedef enum {
    BIGINT_STATUS_OK,
    BIGINT_STATUS_MEM,
    BIGINT_STATUS_BAD_DIGIT,
    BIGINT_STATUS_UNDERFLOW,
} bigint_status_t;

/** Criação e destruição */

/// Cria um novo bigint_t.
bigint_t *bigint_create(void);

/// Destroi um bigint_t.
[[gnu::nonnull]]
void bigint_destroy(bigint_t **num);

/// Cria um bigint_t a partir de uma string.
[[gnu::nonnull]]
bigint_t *bigint_create_from_string(const char *str);

/// Copia um bigint_t para outro.
[[gnu::nonnull]]
bigint_status_t bigint_copy(bigint_t *target, const bigint_t *source);

/** Aritmética */

/// Soma dois bigint_t.
[[gnu::nonnull]]
bigint_status_t bigint_add(const bigint_t *num_a, const bigint_t *num_b,
                           bigint_t *result);

/// Compara dois bigint_t.
[[gnu::nonnull]]
int bigint_cmp(const bigint_t *num_a, const bigint_t *num_b);

/** Manipulação */

/// Adiciona um dígito mais significativo a um bigint_t.
[[gnu::nonnull]]
bigint_status_t bigint_push_high_digit(bigint_t *num, uint8_t digit);

/// Remove o dígito mais significativo de um bigint_t.
[[gnu::nonnull(1)]]
bigint_status_t bigint_pop_high_digit(bigint_t *num, uint8_t *digit);

/// Zera um bigint_t.
[[gnu::nonnull]]
void bigint_zero(bigint_t *num);

/// Quantidade de dígitos de um bigint_t.
[[gnu::nonnull]]
size_t bigint_length(const bigint_t *num);

/** Formatação */

/// Formata um bigint_t como uma string.
[[gnu::nonnull]]
char *bigint_to_string(const bigint_t *num);

/** Iteração */

/// Itera sobre os dígitos de um bigint_t.
[[gnu::nonnull(1, 2)]]
void bigint_iter(const bigint_t *num, void (*callback)(uint8_t, void *),
                 void *userdata);

/// Itera sobre os dígitos de dois bigint_t.
[[gnu::nonnull(1, 2, 3)]]
void bigint_iter2(const bigint_t *num_a, const bigint_t *num_b,
                  void (*callback)(uint8_t, uint8_t, void *), void *userdata);
