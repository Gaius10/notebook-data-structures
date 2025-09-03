#include <stdio.h>
#include "../lib/actions.h"

int rec_search(int search, int arr[], unsigned start, unsigned end);

int recursive_binary_search(int search, int arr[], unsigned int arr_len) {
    return rec_search(search, arr, 0, arr_len);
}

int rec_search(int search, int arr[], unsigned start, unsigned end) {
    if (start >= end) return -1;

    unsigned middle = (start + end) / 2;

    if (arr[middle] == search) {
        return middle;
    }

    unsigned new_start;
    unsigned new_end;

    if (arr[middle] > search) {
        new_start = 0;
        new_end = middle;
    } else {
        new_start = middle;
        new_end = end;
    }

    return rec_search(search, arr, new_start, new_end);
}

