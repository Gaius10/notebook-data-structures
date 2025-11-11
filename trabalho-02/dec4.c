#include "dec4.h"

#include <ctype.h>
#include <stdlib.h>

dec4_t dec4_add(dec4_t a, dec4_t b, uint8_t *carry) {
    dec4_t result;

    for (size_t i = 0; i < 4; i++) {
        uint8_t sum = a.digits[i] + b.digits[i] + *carry;
        result.digits[i] = sum % 10;
        *carry = sum / 10;
    }

    return result;
}

dec4_t dec4_neg(dec4_t a) {
    dec4_t result;

    for (size_t i = 0; i < 4; i++) {
        result.digits[i] = 9 - a.digits[i] + (i == 3);
    }

    return result;
}

/// Returns the sign of a decimal number.
/// -1 if negative, 0 if zero, 1 if positive.
int8_t dec4_sign(dec4_t value) {
    uint32_t cast = *(uint32_t *)&value;

    return cast * (value.digits[3] < 5 ? 1 : -1);
}

void dec4_from_string(const char *restrict str, void (*callback)(dec4_t, void *),
                   void *ud) {
    bool negative = false;

    const char *ptr = str;

    while (*ptr == ' ') {
        ptr++;
    }

    while (*ptr == '-') {
        negative ^= true;
        ptr++;
    }

    // skip leading zeros
    while (*ptr == '0') {
        ptr++;
    }

    size_t n = 0;

    // get number of digits
    {
        const char *cur = ptr;

        while (isdigit(*cur)) {
            n++;
            cur++;
        }
    }

    dec4_t result;
    size_t i = 0;

    for (; i < n; i++) {
        if (i % 4 == 0) {
            if (i > 0) {
                callback(result, ud);
            }

            result = negative ? DEC4_MAX : DEC4_ZERO;
        }

        result.digits[i % 4] = negative
                                   ? 9 - (ptr[n - i - 1] - '0') + (i == 0)
                                   : ptr[n - i - 1] - '0';
    }

    callback(result, ud);

    if (!negative && result.digits[3] >= 5) {
        callback(DEC4_ZERO, ud);
    }
}

uint16_t dec4_to_uint16(dec4_t value) {
    uint16_t result = 0;

    for (size_t i = 0; i < 4; i++) {
        result = result * 10 + value.digits[3 - i];
    }

    return result;
}

int16_t dec4_to_int16(dec4_t value) {
    int16_t result = dec4_to_uint16(value);
    return result >= 5000 ? result - 10000 : result;
}
