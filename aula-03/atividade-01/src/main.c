#include <stdio.h>

int fib(int x);

int main() {
    int x = 0;
    if (scanf("%d", &x) != 1) {
        printf("Erro ao ler entrada.\n");
        return 1;
    }
    
    printf("Calculando fibonacci de %d...\n", x);

    int y = fib(x);
    printf("Resultado final: %d\n", y);

    return 0;
}

int fib(int x) {
    printf("Entrando em fibonacci(%d)\n", x);
    if (x < 0) {
        return -1;
    }

    if (x == 0 || x == 1) {
        printf("Caso base atingido: fibonacci(%d) = %d\n", x, x);
        return x;
    }

    int y = fib(x-1) + fib(x-2);
    printf("Retornando de fibonacci(%d) = %d\n", x, y);

    return y;
}

