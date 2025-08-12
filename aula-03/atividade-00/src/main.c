#include <stdio.h>

int fatorial(int x);

int main() {
    int x = 0;
    if (scanf("%d", &x) != 1) {
        printf("Erro ao ler entrada.\n");
        return 1;
    }

    printf("Calculando fatorial de %d...\n", x);;

    int y = fatorial(x);
    printf("Resultado final: %d", y);

    return 0;
}

int fatorial(int x) {
    printf("Entrando em fatorial(%d)\n", x);
    if (x < 0) return 0;
    if (x == 1 || x == 0) {
        printf("Caso base atingido: fatorial(%d) = 1\n", x);
        return 1;
    }

    int y = x * fatorial(x - 1);
    printf("Retornando de fatorial(%d) = %d\n", x, y);

    return y;
}

