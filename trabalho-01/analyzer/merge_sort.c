#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 30

void _merge_sort(int arr[], unsigned start, unsigned end);
void _merge(int arr[], unsigned start, unsigned middle, unsigned end);

void merge_sort(int arr[], unsigned len) {
    _merge_sort(arr, 0, len);
}

void _merge_sort(int arr[], unsigned start, unsigned end) {
    if (start >= end) return;

    int middle = (start + end) / 2;

    _merge_sort(arr, start, middle);
    _merge_sort(arr, middle + 1, end);

    _merge(arr, start, middle, end);
}

void _merge(int arr[], unsigned start, unsigned middle, unsigned end) {
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
}
