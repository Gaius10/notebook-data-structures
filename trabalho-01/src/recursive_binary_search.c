#include <stdio.h>
#include "../lib/actions.h"

int recursive_binary_search(int search, int arr[], unsigned int arr_len) {
    printf("Rec bin search: %d %d", search, arr_len);
    for (unsigned i = 0; i < arr_len; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    return 0;
}

