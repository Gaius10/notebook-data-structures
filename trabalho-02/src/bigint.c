#include <ctype.h>
#include <stdlib.h>

#include "../lib/bigint.h"

struct node {
    uint8_t digits[4];
    struct node *next;
};

struct bigint {
    struct node *high, *low;
    size_t length;
    int8_t sign;
};

struct AddData {
    bigint_t *result;
    size_t leading_zeros;
    int8_t carry;
    int8_t sign_a, sign_b;
};

struct CmpData {
    int8_t carry;
    bool zero;
    int8_t sign_a, sign_b;
};

/***********************
 * Criacao e destruição
 */

bigint_t *bigint_create() {
    bigint_t *result = malloc(sizeof(bigint_t));

    if (result == NULL) {
        return NULL;
    }

    result->high = result->low = NULL;
    result->length = 0;
    result->sign = 0;

    return result;
}

bigint_t *bigint_create_from_string(const char *str) {
    bigint_t *result = bigint_create();

    if (result == NULL) {
        return NULL;
    }

    result->sign = 1;

    const char *cursor = str;

    while (*cursor == ' ') {
        cursor++;
    }

    while (*cursor == '-') {
        result->sign *= -1;
        cursor++;
    }

    // pula os zeros a esquerda
    while (*cursor == '0') {
        cursor++;
    }

    size_t n = 0;

    // obtem a quantidade de digitos
    {
        const char *cur = cursor;

        while (isdigit(*cur)) {
            n++;
            cur++;
        }
    }

    result->sign *= (n != 0);

    for (size_t i = 0; i < n; i++) {
        bigint_status_t status =
            bigint_push_high_digit(result, cursor[n - i - 1] - '0');

        if (status != BIGINT_STATUS_OK) {
            bigint_destroy(&result);
            return NULL;
        }
    }

    return result;
}

bigint_status_t bigint_copy(bigint_t *target, const bigint_t *source) {
    bigint_zero(target);

    struct node *current = source->low;

    while (current != NULL) {
        struct node *new_node = malloc(sizeof(struct node));

        if (new_node == NULL) {
            bigint_zero(target);
            return BIGINT_STATUS_MEM;
        }

        aux_copy(new_node->digits, current->digits);
        new_node->next = NULL;

        if (target->low == NULL) {
            target->low = new_node;
        } else {
            target->high->next = new_node;
        }

        target->high = new_node;

        current = current->next;
    }

    target->length = source->length;
    target->sign = source->sign;

    return BIGINT_STATUS_OK;
}

void bigint_destroy(bigint_t **num) {
    bigint_zero(*num);
    free(*num);
    *num = NULL;
}

/***********************
 * Manipulação
 */

bigint_status_t bigint_push_high_digit(bigint_t *num, uint8_t digit) {
    if (digit > 9) {
        return BIGINT_STATUS_BAD_DIGIT;
    }

    size_t offset = num->length % 4;

    if (offset == 0) {
        struct node *new_node = malloc(sizeof(struct node));

        if (new_node == NULL) {
            return BIGINT_STATUS_MEM;
        }

        aux_zero(new_node->digits);
        new_node->digits[0] = digit;

        if (num->low == NULL) {
            num->low = new_node;
        } else {
            num->high->next = new_node;
        }

        num->high = new_node;
    } else {
        struct node *high = num->high;
        high->digits[offset] = digit;
    }

    if (num->sign == 0) {
        num->sign = digit != 0;
    }

    num->length++;

    return BIGINT_STATUS_OK;
}

bigint_status_t bigint_pop_high_digit(bigint_t *num, uint8_t *digit) {
    if (num->high == NULL) {
        return BIGINT_STATUS_UNDERFLOW;
    }

    if (digit != NULL) {
        *digit = num->high->digits[num->length % 4];
    }

    if (num->length == 1) {
        free(num->low);
        num->high = num->low = NULL;
    } else if (num->length % 4 == 1) {
        struct node *old_high = num->high;
        struct node *current = num->low;

        while (current->next != old_high) {
            current = current->next;
        }

        num->high = current;

        free(old_high);
    }

    num->length--;

    return BIGINT_STATUS_OK;
}

void bigint_zero(bigint_t *num) {
    struct node *current = num->low;

    while (current != NULL) {
        struct node *next = current->next;
        free(current);
        current = next;
    }

    num->low = num->high = NULL;
    num->length = 0;
    num->sign = 0;
}

size_t bigint_length(const bigint_t *num) {
    if (num->sign == 0) {
        return 1;
    }

    return num->length;
}

/***********************
 * Formatação
 */
static void aux_to_string_cb(uint8_t digit, void *raw_data);

char *bigint_to_string(const bigint_t *num) {
    size_t n_digits = bigint_length(num);
    n_digits += num->sign == -1;

    char *buffer = calloc(n_digits + 1, sizeof(char));

    if (buffer == NULL) {
        return NULL;
    }

    if (num->sign == 0) {
        *buffer = '0';
    } else {
        char *cursor = buffer + n_digits - 1;

        bigint_iter(num, aux_to_string_cb, &cursor);

        if (num->sign == -1) {
            *buffer = '-';
        }
    }

    return buffer;
}

/***********************
 * Iteração
 */

void bigint_iter(const bigint_t *num, void (*callback)(uint8_t, void *),
                 void *userdata) {
    struct node *current = num->low;

    size_t i = 0;

    while (current != NULL) {
        for (size_t j = 0; j < 4 && i < num->length; j++, i++) {
            callback(current->digits[j], userdata);
        }
        current = current->next;
    }
}

static void aux_zero(uint8_t digits[]);
static void aux_copy(uint8_t dest[], const uint8_t src[]);

void bigint_iter2(const bigint_t *num_a, const bigint_t *num_b,
                  void (*callback)(uint8_t, uint8_t, void *), void *userdata) {

    size_t len_a = num_a->length;
    size_t len_b = num_b->length;

    size_t len = len_a > len_b ? len_a : len_b;

    struct node *current_a = num_a->low;
    struct node *current_b = num_b->low;

    size_t i = 0;

    while (current_a != NULL || current_b != NULL) {
        uint8_t digits_a[4], digits_b[4];

        if (current_a != NULL) {
            aux_copy(digits_a, current_a->digits);
            current_a = current_a->next;
        } else {
            aux_zero(digits_a);
        }

        if (current_b != NULL) {
            aux_copy(digits_b, current_b->digits);
            current_b = current_b->next;
        } else {
            aux_zero(digits_b);
        }

        for (size_t j = 0; j < 4 && i < len; j++, i++) {
            callback(digits_a[j], digits_b[j], userdata);
        }
    }
}

/**
 * Funções auxiliares
 */
static void aux_zero(uint8_t digits[]) {
    digits[0] = 0;
    digits[1] = 0;
    digits[2] = 0;
    digits[3] = 0;
}

static void aux_copy(uint8_t dest[], const uint8_t src[]) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
}

static void aux_to_string_cb(uint8_t digit, void *raw_data) {
    char **cursor = raw_data;
    **cursor = '0' + digit;
    (*cursor)--;
}
