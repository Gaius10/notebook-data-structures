
#include "../lib/bigint.h"

static void aux_add_cb(uint8_t a, uint8_t b, void *raw_data);
static void aux_sub_cb(uint8_t a, uint8_t b, void *raw_data);

bigint_status_t bigint_add(
    const bigint_t *num_a,
    const bigint_t *num_b,
    bigint_t *result
) {

    struct AddData data = {
        .result = result,
        .carry = 0,
        .sign_a = num_a->sign,
        .sign_b = num_b->sign
    };

    if (num_a->sign == 0) {
        bigint_copy(result, num_b);
    } else if (num_b->sign == 0) {
        bigint_copy(result, num_a);
    } else if (num_a->sign != num_b->sign &&
               (num_a->sign < 0 || num_b->sign < 0)) {
        int8_t cmp = aux_cmp(num_a, num_b, true);

        // se |num_a| > |num_b|
        if (cmp > 0) {
            bigint_iter2(num_a, num_b, aux_sub_cb, &data);
            result->sign = num_a->sign;
        } else if (cmp < 0) {
            bigint_iter2(num_b, num_a, aux_sub_cb, &data);
            result->sign = num_b->sign;
        } else {
            bigint_zero(result);
            return BIGINT_STATUS_OK;
        }

        if (data.carry != 0) {
            bigint_push_high_digit(result, data.carry);
        } else {
            for (size_t n = 0; n < data.leading_zeros; n++) {
                bigint_pop_high_digit(result, NULL);
            }
        }
    } else {
        bigint_iter2(num_a, num_b, aux_add_cb, &data);
        result->sign = num_a->sign;

        if (data.carry != 0) {
            bigint_push_high_digit(result, data.carry);
        }
    }

    return BIGINT_STATUS_OK;
}

static void aux_cmp_cb(uint8_t a, uint8_t b, void *raw_data) {
int bigint_cmp(const bigint_t *num_a, const bigint_t *num_b) {
    return aux_cmp(num_a, num_b, false);
}

/**
 * Funções auxiliares
 */
static void aux_sub_cb(uint8_t digit_a, uint8_t digit_b, void *raw_data) {
    struct AddData *data = raw_data;

    int8_t new_a = (int8_t)digit_a + data->carry;

    if (new_a < (int8_t)digit_b) {
        data->carry = -1;
        new_a += 10;
    } else {
        data->carry = 0;
    }

    uint8_t digit = (uint8_t)new_a - digit_b;

    if (digit == 0) {
        data->leading_zeros++;
    } else {
        data->leading_zeros = 0;
    }

    bigint_push_high_digit(data->result, digit);
}

static void aux_add_cb(uint8_t digit_a, uint8_t digit_b, void *raw_data) {
    struct AddData *data = raw_data;

    int8_t sum = digit_a + digit_b + data->carry;
    data->carry = sum / 10;
    sum %= 10;

    bigint_push_high_digit(data->result, sum);
}


static void aux_cmp_cb(uint8_t a, uint8_t b, void *raw_data);
static int aux_cmp(const bigint_t *num_a, const bigint_t *num_b, bool abs) {
    if (abs) {
        struct CmpData data = {.carry = 0, .zero = 1, .sign_a = 1, .sign_b = 1};

        bigint_iter2(num_a, num_b, aux_cmp_cb, &data);

        return !data.zero * (data.carry < 0 ? -1 : 1);
    } else if (num_a->sign != num_b->sign) {
        return num_a->sign > num_b->sign ? 1 : -1;
    }

    struct CmpData data = {
        .carry = 0, .zero = 1, .sign_a = num_a->sign, .sign_b = num_b->sign};

    bigint_iter2(num_a, num_b, aux_cmp_cb, &data);

    return !data.zero * (data.carry < 0 ? -1 : 1);
}

static void aux_cmp_cb(uint8_t digit_a, uint8_t digit_b, void *raw_data) {
    struct CmpData *data = raw_data;
    int8_t sum = (int8_t)digit_a * data->sign_a -
                 (int8_t)digit_b * data->sign_b + data->carry;

    data->zero &= sum == 0;
    data->carry = -(sum < 0);
}
