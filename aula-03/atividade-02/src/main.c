#include <stdio.h>

#define INPUT_MAX_LEN 1000

int sum(unsigned int input[], unsigned int n);

int main() {
    unsigned int n = 0;
    unsigned int input[INPUT_MAX_LEN];
    for (int i = 0; i < INPUT_MAX_LEN; i++) {
        input[i] = 0;
    }

    if (scanf("%d", &n) != 1) {
        printf("Erro ao ler número de entradas.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &input[i]) != 1) {
            printf("Erro ao ler entrada %d\n", i);
            return 1;
        }
    }

    int y = sum(input, n);
    printf("Soma dos pares: %d\n", y);

    return 0;
}

int sum(unsigned int input[], unsigned int n) {
    if (n <= 0) return 0;

    int pop = input[n-1];
    if (pop % 2 == 1) pop = 0;

    int y = pop + sum(input, n - 1);
    return y;
}

