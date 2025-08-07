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

#define LIST_MAX_SIZE 10000

void clear_buffer();

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

    *size = *size + 1;
    *numbers = (int*) realloc(*numbers, sizeof(int) * (*size));
    (*numbers)[(*size) - 1] = novo;
}

void pop(int** numbers, unsigned int* size) {
    if (*size == 0) {
        return;
    }

    *size = *size - 1;
    *numbers = (int *) realloc(*numbers, sizeof(int) * (*size));
}

void list(int** numbers, unsigned int* size) {
    for (int i = 0; i < *size; i++) {
        printf("%d\n", (*numbers)[i]);
    }
}

void abstract(int** numbers, unsigned int* size) {
    long int soma = 0;
    double media = 0;

    for (int i = 0; i < *size; i++) {
        soma += (*numbers)[i];
    }

    media = (float) soma / (float) *size;

    printf("%ld\n", soma);
    printf("%lf\n", media);
}

void sort(int** numbers, unsigned int* size) {
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

