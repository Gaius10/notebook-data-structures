#include <stdio.h>

void hanoi(int n, char origin, char aux, char dest);

int main() {
    unsigned int n = 0;

    if (scanf("%d", &n) != 1) {
        printf("Erro ao ler número de discos.");
        return 1;
    }

    hanoi(n, 'A', 'B', 'C');

    return 0;
}

void hanoi(int n, char origin, char aux, char dest) {
    if (n == 0) return;

    hanoi(n - 1, origin, dest, aux);

    printf("Mova o disco %d de %c para %c\n", n, origin, dest);

    hanoi(n - 1, aux, origin, dest);
}

