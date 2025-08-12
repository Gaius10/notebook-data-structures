#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOOP 0
#define ADD 1
#define POP 2
#define LIST 3
#define ABSTRACT 4
#define SORT 5
#define EXIT 6

// Uma função por comando
void add(int** numbers, unsigned int* size);
void pop(int** numbers, unsigned int* size);
void list(int** numbers, unsigned int* size);
void abstract(int** numbers, unsigned int* size);
void sort(int** numbers, unsigned int* size);

int main() {
    unsigned int op = NOOP;
    unsigned int size = 0;
    int* numbers = NULL;

    do {
        // Switch para definir qual a operação desejada
        switch (op) {
            case NOOP:
                break;
            case ADD:
                add(&numbers, &size);
                break;
            case POP:
                pop(&numbers, &size);
                break;
            case LIST:
                list(&numbers, &size);
                break;
            case ABSTRACT:
                abstract(&numbers, &size);
                break;
            case SORT:
                sort(&numbers, &size);
                break;
            default:
                printf("Operação inválida.\n");
                break;
        }

        if (scanf("%d", &op) != 1) {
            printf("Erro ao ler operação.\n");
            exit(1);
        }
        // Sai do loop quando ler op == 6
    } while (op != EXIT);

    free(numbers);
    return 0;
}

void add(int** numbers, unsigned int* size) {
    int novo = 0;

    if (scanf("%d", &novo) != 1) {
        printf("Erro ao ler novo número.");
        exit(1);
    }

    // Atualiza tamanho, realoca vetor de numeros, adiciona novo
    // numero.
    *size = *size + 1;
    *numbers = (int*) realloc(*numbers, sizeof(int) * (*size));
    (*numbers)[(*size) - 1] = novo;
}

void pop(int** numbers, unsigned int* size) {
    if (*size == 0) {
        return;
    }

    // Reduz size, realoca vetor perdendo ultimo numero
    *size = *size - 1;
    *numbers = (int *) realloc(*numbers, sizeof(int) * (*size));
}

void list(int** numbers, unsigned int* size) {
    if (*size == 0) return;

    // Printa antes para garantir que não termina em espaço
    printf("%d", (*numbers)[0]);

    // Printa espaco + cada um dos elementos
    for (int i = 1; i < *size; i++) {
        printf(" %d", (*numbers)[i]);
    }

    printf("\n");
}

void abstract(int** numbers, unsigned int* size) {
    long int soma = 0;
    double media = 0;

    // Soma tudo
    for (int i = 0; i < *size; i++) {
        soma += (*numbers)[i];
    }

    // Usa soma para calcular media
    media = (float) soma / (float) *size;
    printf("Soma = %ld, Media = %.2lf\n", soma, media);
}

void sort(int** numbers, unsigned int* size) {
    // Busca os menores valores e os puxa para o inicio do vetor
    for (int i = 0; i < *size; i++) {
        int min_value = numbers[0][i];
        int min_index = i;

        for (int j = i+1; j < *size; j++) {
            if (numbers[0][j] < min_value) {
                min_value = numbers[0][j];
                min_index = j;
            }
        }

        numbers[0][min_index] = numbers[0][i];
        numbers[0][i] = min_value;
    }
}

