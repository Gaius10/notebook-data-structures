#include <stdio.h>
#include <stdlib.h>
#include "../lib/actions.h"

#define ARR_MAX 1000

#define OP_INVERT 1
#define OP_SEQUENTIAL_SEARCH 2
#define OP_BINARY_SEARCH 3
#define OP_RECURSIVE_BINARY_SEARCH 4
#define OP_EXIT 5

int main() {
    int arr[ARR_MAX];
    unsigned len = 0;
    unsigned read = 0;
    unsigned op = 0;

    for (unsigned i = 0; i < ARR_MAX; i++) arr[i] = 0;

    read = scanf("%u", &len);
    if (read != 1) {
        printf("Erro ao ler tamanho da lista.\n");
        return 1;
    }

    for (unsigned i = 0; i < len; i++) {
        read = scanf("%d", &arr[i]);
        if (read != 1) {
            printf("Erro ao ler elemento %d\n", i);
            return 1;
        }
    }

    do {
        read = scanf("%u", &op);
        if (read != 1) {
            printf("Erro ao ler operacao.\n");
            continue;
        }

        switch (op) {
            case OP_INVERT:
                invert(arr, len);

                for (unsigned i = 0; i < len; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\n");

                break;
            case OP_SEQUENTIAL_SEARCH:
                printf("Buscando sequencialmente...\n");
                break;
            case OP_BINARY_SEARCH:
                printf("Fazendo busca binaria...\n");
                break;
            case OP_RECURSIVE_BINARY_SEARCH:
                printf("Fazendo busca binaria recursiva...\n");
                break;
            case OP_EXIT:
                // printf("Saindo...\n");
                break;
        }
    } while (op != OP_EXIT);
}

