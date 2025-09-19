#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 30

void _merge_sort(int arr[], unsigned start, unsigned end);
void _merge(int arr[], unsigned start, unsigned middle, unsigned end);

void merge_sort(int arr[], unsigned len) {
    _merge_sort(arr, 0, len - 1);
}

void _merge_sort(int arr[], unsigned start, unsigned end) {
    if (start >= end) return;

    unsigned middle = (start + end) / 2;

    _merge_sort(arr, start, middle);
    _merge_sort(arr, middle + 1, end);

    _merge(arr, start, middle, end);
}

void _merge(int arr[], unsigned start, unsigned middle, unsigned end) {
    // Tamanhos
    unsigned left_len = middle - start + 1;
    unsigned right_len = end - middle;

    // Vetores auxiliares
    int left[MAX_ITEMS];
    int right[MAX_ITEMS];

    // Contadores
    unsigned l = 0;
    unsigned r = 0;
    unsigned c = start;

    // Inicializa vetores auxiliares
    for (unsigned i = 0; i < left_len; i++) {
        printf("start = %d, i = %d\n", start, i);
        left[i] = arr[start + i];
    }

    for (unsigned i = 0; i < right_len; i++) {
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
}
