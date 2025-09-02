#include <stdio.h>
#include "../lib/actions.h"

int sequential_search(int search, int arr[], unsigned int arr_len) {
    printf("Bin search: %d %d", search, arr_len);
    for (unsigned i = 0; i < arr_len; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    return 0;
}

