#include <stdio.h>
#include "../lib/actions.h"

int binary_search(int search, int arr[], unsigned arr_len) {
    printf("Bin search: %d %d", search, arr_len);
    for (unsigned i = 0; i < arr_len; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    return 0;
}

