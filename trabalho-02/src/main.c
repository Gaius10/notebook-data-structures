// Caio Corrêa Chaves - 15444406
// Vinicius Henrique Pereira Giroto - 11319656

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/bigint.h"

#define BUFFER_SIZE 1024

int main() {
    size_t n;

    [[maybe_unused]]
    int _;

    _ = scanf("%zu ", &n);

    char buffer[BUFFER_SIZE];

    [[gnu::cleanup(bigint_destroy)]]
    bigint_t *result = bigint_create();

    if (result == NULL) {
        fprintf(stderr, "Erro ao criar bigint\n");
        return 1;
    }

    while (n > 0) {
        if (fgets(buffer, BUFFER_SIZE - 1, stdin) == NULL) {
            fprintf(stderr, "Erro ao ler linha\n");
            return 1;
        }

        const char *operator = strtok(buffer, " \n");
        const char *lhs_raw = strtok(NULL, " \n");
        const char *rhs_raw = strtok(NULL, " \n");

        [[gnu::cleanup(bigint_destroy)]]
        bigint_t *lhs = bigint_create_from_string(lhs_raw);
        [[gnu::cleanup(bigint_destroy)]]
        bigint_t *rhs = bigint_create_from_string(rhs_raw);

        printf("Resultado :: ");

        if (strcmp("soma", operator) == 0) {
            bigint_zero(result);
            bigint_status_t status = bigint_add(lhs, rhs, result);

            if (status != BIGINT_STATUS_OK) {
                fprintf(stderr, "Erro ao realizar soma\n");
                return 1;
            }

            char *result_str = bigint_to_string(result);
            printf("%s\n", result_str);
            free(result_str);
        } else {
            int cmp = bigint_cmp(lhs, rhs);

            if (strcmp("maior", operator) == 0) {
                printf("%s\n", cmp > 0 ? "True" : "False");
            } else if (strcmp("menor", operator) == 0) {
                printf("%s\n", cmp < 0 ? "True" : "False");
            } else if (strcmp("igual", operator) == 0) {
                printf("%s\n", cmp == 0 ? "True" : "False");
            }
        }

        n--;
    }

    return 0;
}
