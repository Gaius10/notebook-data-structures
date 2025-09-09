#include <stdio.h>
#include "../lib/algorithms.h"

int sequential_search(int search, int arr[], unsigned int arr_len) {
    for (unsigned i = 0; i < arr_len; i++) {
        if (arr[i] == search) return i;
    }

    return -1;
}

