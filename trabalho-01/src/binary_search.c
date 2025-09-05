#include <stdio.h>
#include "../lib/actions.h"

int binary_search(int search, int arr[], unsigned arr_len) {
    int start = 0;
    int end = arr_len;

    int middle;

    while (start < end) {
        middle = (start + end) / 2;
        if (arr[middle] == search) return middle;

        if (search > arr[middle]) {
            start = middle + 1;
            end = end;
        } else {
            start = start;
            end = middle;
        }
    }

    return -1;
}

