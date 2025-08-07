#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n = 0;
    int* numbers = NULL;

    if (scanf("%d", &n) != 1) {
        printf("Erro ao ler tamanho inicial do vetor.");
        return 1;
    }

    numbers = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            printf("Erro ao ler número %d.\n", i);
            return 1;
        }
    }

    int x = 0;
    if (scanf("%d", &x) != 1) {
        printf("Erro ao ler numero x.\n");
        return 1;
    }

    int p = 0;
    if (scanf("%d", &p) != 1) {
        printf("Erro ao ler posição p.\n");
        return 1;
    }

    numbers = realloc(numbers, sizeof(int) * (n + 1));

    for (int i = n; i > p; i--) {
        numbers[i] = numbers[i-1];
        numbers[i-1] = x;
    }

    printf("%d", numbers[0]);
    for (int i = 1; i < n + 1; i++) {
        printf(" %d", numbers[i]);
    }

    printf("\n");

    free(numbers);
    return 0;
}

