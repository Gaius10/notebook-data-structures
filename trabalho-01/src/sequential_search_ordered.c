#include "../lib/algorithms.h"

int sequential_search_ordered(int search, int arr[], unsigned int arr_len) {
    unsigned i;

    for (i = 0; i < arr_len; i++) {
        if (arr[i] >= search) break;
    }

    if (i < arr_len && arr[i] == search)
        return i;

    return -1;
}
