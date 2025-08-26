#include <stdio.h>

#define ARR_MAX 1000

void merge_sort(int arr[], int start, int end);
void merge(int arr[], int start, int mid, int end);
void printl(int arr[], int start, int end);

int main() {
    int arr[ARR_MAX];
    int n = 0;
    int read;

    read = scanf("%d", &n);
    if (read != 1) {
        printf("Erro ao ler numero de entradas.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        read = scanf("%d", &arr[i]);
        if (read != 1) {
            printf("Erro ao ler entrada %d\n", i);
            return 1;
        }
    }

    // printf("Lista desordenada: ");
    // printl(arr, 0, n);

    merge_sort(arr, 0, n);

    // printf("List ordenada: ");
    // printl(arr, 0, n);

    return 0;
}

void merge_sort(int arr[], int start, int end) {
    if (end - start <= 1) return;

    printf("DIVISAO [%d,%d]\n", start, end);

    int mid = (start + end) / 2;

    merge_sort(arr, start, mid);
    merge_sort(arr, mid, end);

    merge(arr, start, mid, end);
}

void merge(int arr[], int start, int mid, int end) {
    int left_len = mid - start;
    int right_len = end - mid;

    int left[ARR_MAX];
    int right[ARR_MAX];

    int l = 0;
    int r = 0;
    int c = start;

    for (int i = start; i < mid; i++) {
        left[i-start] = arr[i];
    }

    for (int i = mid; i < end; i++) {
        right[i-mid] = arr[i];
    }

    while (l < left_len && r < right_len) {
        if (left[l] < right[r]) {
            arr[c++] = left[l++];
        } else {
            arr[c++] = right[r++];
        }
    }

    while (l < left_len) {
        arr[c++] = left[l++];
    }

    while (r < right_len) {
        arr[c++] = right[r++];
    }

    printf("INTERCALACAO [%d,%d] ", start, end);
    printl(arr, start, end);
}

void printl(int arr[], int start, int end) {
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

