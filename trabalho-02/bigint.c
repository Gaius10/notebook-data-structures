#include "bigint.h"
#include "sll-dec4.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bigint_t *bigint_create() {
    bigint_t *result = malloc(sizeof(bigint_t));

    if (result == nullptr) {
        return nullptr;
    }

    sll_dec4_init(&result->list);

    return result;
}

#pragma region create_from_string

static void from_string_cb(dec4_t value, void *data) {
    sll_dec4_t *list = (sll_dec4_t *)data;
    sll_dec4_push(list, value);
}

bigint_t *bigint_create_from_string(const char *str) {
    bigint_t *result = bigint_create();

    if (result == nullptr) {
        return nullptr;
    }

    dec4_from_string(str, from_string_cb, &result->list);

    return result;
}

#pragma endregion

void bigint_destroy(bigint_t **bigint) {
    sll_dec4_clear(&(*bigint)->list);
    free(*bigint);
    *bigint = nullptr;
}

#pragma region to_string

struct ToStringData {
    char *buffer;
    size_t length, index, written;
    bool is_negative;
};

/// Callback function for bigint_to_string iterator
static void to_string_cb(dec4_t value, void *raw_data) {
    struct ToStringData *data = raw_data;

    size_t offset = (data->length - data->index) * 4 + 1;

    char digits[5];
    uint16_t value16 = dec4_to_uint16(value);

    int written = snprintf(digits, 5, "%04u", value16);

    strncpy(data->buffer + offset, digits, 4);

    data->written += written;
    data->index++;
}

/// Converts a bigint to a string
char *bigint_to_string(const bigint_t *bigint) {
    size_t length = sll_dec4_length(&bigint->list);

    size_t n_digits = length * 4 + 2;

    struct ToStringData data = {.buffer = malloc(n_digits),
                                .length = length,
                                .index = 0,
                                .written = 0,
                                .is_negative =
                                    dec4_sign(bigint->list.head->value) < 0};

    data.buffer[n_digits - 1] = '\0';

    sll_dec4_iter(&bigint->list, to_string_cb, &data);

    return data.buffer;
}

#pragma endregion
