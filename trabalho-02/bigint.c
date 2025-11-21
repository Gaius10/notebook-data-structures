#include <ctype.h>
#include <stdlib.h>

#include "bigint.h"

struct node {
    uint8_t digits[4];
    struct node *next;
};

struct bigint {
    // high: ponteiro para o nó mais significativo (tail)
    // low: ponteiro para o nó menos significativo (head)
    struct node *high, *low;
    // tamanho em digitos
    size_t length;
    // sinal, -1 para negativo, 0 para zero, 1 para positivo
    int8_t sign;
};

/// Estruturas auxiliares

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

/// Funções auxiliares

/// Callback function para o bigint_to_string
static void aux_to_string_cb(uint8_t digit, void *raw_data) {
    char **cursor = raw_data;
    **cursor = '0' + digit;
    (*cursor)--;
}

/// Soma dois dígitos, considerando o carry.
static void aux_add_cb(uint8_t digit_a, uint8_t digit_b, void *raw_data) {
    struct AddData *data = raw_data;

    int8_t sum = digit_a + digit_b + data->carry;
    data->carry = sum / 10;
    sum %= 10;

    bigint_push_high_digit(data->result, sum);
}

/// Subtrai dois dígitos, considerando o carry.
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

/// Compara dois dígitos, considerando o carry e os sinais.
static void aux_cmp_cb(uint8_t digit_a, uint8_t digit_b, void *raw_data) {
    struct CmpData *data = raw_data;
    int8_t sum = (int8_t)digit_a * data->sign_a -
                 (int8_t)digit_b * data->sign_b + data->carry;

    data->zero &= sum == 0;
    data->carry = -(sum < 0);
}

/// Compara dois bigints, com uma opção para comparação absoluta.
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

/// Zera os digitos de uma array de 4 bytes
static void aux_zero(uint8_t digits[]) {
    digits[0] = 0;
    digits[1] = 0;
    digits[2] = 0;
    digits[3] = 0;
}

/// Copia os digitos de uma array de 4 bytes para outra
static void aux_copy(uint8_t dest[], const uint8_t src[]) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
}

/// Cria um novo bigint zerado
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

/// Copia o conteúdo de um bigint para outro.
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

/// Insere um digito no bigint à esquerda
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

/// Remove o dígito mais significativo do bigint.
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

/// Zera o bigint, desalocando todos os digitos
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

/// Cria um bigint a partir de uma string. Zeros a esquerda são ignorados
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

/// Destroi um bigint
void bigint_destroy(bigint_t **num) {
    bigint_zero(*num);
    free(*num);
    *num = NULL;
}

/// Converte um bigint para uma string
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

/// Soma dois bigints e armazena o resultado.
bigint_status_t bigint_add(const bigint_t *num_a, const bigint_t *num_b,
                           bigint_t *result) {

    struct AddData data = {.result = result,
                           .carry = 0,
                           .sign_a = num_a->sign,
                           .sign_b = num_b->sign};

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

/// Compara dois números inteiros
int bigint_cmp(const bigint_t *num_a, const bigint_t *num_b) {
    return aux_cmp(num_a, num_b, false);
}

/// Itera sobre um número inteiro, chamando a função de retorno de chamada para cada dígito.
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

/// Itera sobre dois números inteiros simultaneamente, chamando a função de retorno de chamada para cada par de dígitos.
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

/// Calculates the number of digits in a bigint
size_t bigint_length(const bigint_t *num) {
    if (num->sign == 0) {
        return 1;
    }

    return num->length;
}
