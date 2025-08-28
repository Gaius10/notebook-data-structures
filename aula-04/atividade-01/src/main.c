#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 30

void merge_sort(int arr[], int start, int end);
void merge(int arr[], int start, int middle, int end);
void printl(int arr[], int start, int end);

int main() {
    int n = 0;
    int read = 0;
    int arr[MAX_ITEMS];

    // Le numero de entradas
    read = scanf("%d", &n);
    if (read != 1) {
        printf("Erro ao ler número de itens.\n");
        return 1;
    }

    // Le entradas
    for (int i = 0; i < n; i++) {
        read = scanf("%d", &arr[i]);
        if (read != 1) {
            printf("Erro ao ler entrada %d.\n", i);
            return 1;
        }
    }

    // Faz a magica
    merge_sort(arr, 0, n - 1);

    return 0;
}

void merge_sort(int arr[], int start, int end) {
    if (start >= end) return;

    printf("DIVISAO [%d,%d]\n", start, end);

    int middle = (start + end) / 2;

    merge_sort(arr, start, middle);
    merge_sort(arr, middle + 1, end);

    merge(arr, start, middle, end);
}

void merge(int arr[], int start, int middle, int end) {
    // Tamanhos
    int left_len = middle - start + 1;
    int right_len = end - middle;

    // Vetores auxiliares
    int left[MAX_ITEMS];
    int right[MAX_ITEMS];

    // Contadores
    int l = 0;
    int r = 0;
    int c = start;

    // Inicializa vetores auxiliares
    for (int i = 0; i < left_len; i++) {
        left[i] = arr[start + i];
    }

    for (int i = 0; i < right_len; i++) {
        right[i] = arr[middle + 1 + i];
    }

    // Merge
    while (l < left_len && r < right_len) {
        if (left[l] <= right[r]) {
            arr[c++] = left[l++];
        } else {
            arr[c++] = right[r++];
        }
    }

    // Acrescenta ultimos valores do maior vetor auxiliar
    while (l < left_len)  arr[c++] = left[l++];
    while (r < right_len) arr[c++] = right[r++];

    printf("INTERCALACAO [%d,%d]:", start, end);
    printl(arr, start, end);
}

void printl(int arr[], int start, int end) {
    for (int i = start; i <= end; i++) {
        printf(" %d", arr[i]);
    }

    printf("\n");
}

