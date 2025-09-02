#include "../lib/actions.h"

void swap(int* item1, int* item2) {
    int aux = *item1;
    *item1 = *item2;
    *item2 = aux;
}

void invert(int arr[], unsigned arr_len) {
    for (unsigned i = 0; i < (arr_len / 2); i++) {
        swap(&arr[i], &arr[arr_len - i - 1]);
    }
}

