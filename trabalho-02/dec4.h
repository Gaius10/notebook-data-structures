#pragma once

#include <stddef.h>
#include <stdint.h>

/// Represents a decimal number with 4 digits. From least significant to most
/// significant.
typedef struct {
    uint8_t digits[4];
} dec4_t;

dec4_t dec4_add(dec4_t a, dec4_t b, uint8_t *carry);
dec4_t dec4_neg(dec4_t a);

[[gnu::nonnull, gnu::null_terminated_string_arg(1)]]
void dec4_from_string(const char *restrict str, void (*callback)(dec4_t, void *),
                   void *ud);

uint16_t dec4_to_uint16(dec4_t value);
int16_t dec4_to_int16(dec4_t value);

int8_t dec4_sign(dec4_t value);

constexpr dec4_t DEC4_ZERO = {0, 0, 0, 0};
constexpr dec4_t DEC4_ONE = {0, 0, 0, 1};
constexpr dec4_t DEC4_MAX = {9, 9, 9, 9};
constexpr dec4_t DEC4_MIN = {0, 0, 0, 0};
