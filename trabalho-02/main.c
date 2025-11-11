#include <stdio.h>
#include <stdlib.h>

#include "bigint.h"

static void cb(dec4_t value, void *) {
    printf("%04d\n", dec4_to_uint16(value));
}

int main() {
    /*
    const char *original = "1923727384";
    [[gnu::cleanup(bigint_destroy)]]
    bigint_t *bigint = bigint_create_from_string(original);
    char *str = bigint_to_string(bigint);

    printf("%s\n%s\n", original, str);

    free(str);
    */

    const char *a = "4999";

    bigint_t *num_a = bigint_create_from_string(a);
    char *str_a = bigint_to_string(num_a);

    printf("%s\n%s\n", a, str_a);

    free(str_a);
    // bignum_to_string()
    // dec4_from_string(a, cb, nullptr);

    return 0;
}
