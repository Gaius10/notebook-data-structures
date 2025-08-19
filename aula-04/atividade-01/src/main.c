#include <stdio.h>

#define NUM_MAX_ITENS 1000

typedef struct {
    unsigned int len;
    int items[NUM_MAX_ITENS];
} List;

List merge_sort(const List list);
List split(
    const List list,
    const unsigned int start,
    const unsigned int end
);
List merge(const List left, const List right);

void print_list(List list);

int main() {
    List unordered_list;

    for (int i = 0; i < NUM_MAX_ITENS; i++) {
        unordered_list.items[i] = 0;
    }

    if (scanf("%d", &unordered_list.len) != 1) {
        printf("Erro ao ler número de entradas.\n");
        return 1;
    }

    for (int i = 0; i < unordered_list.len; i++) {
        if (scanf("%d", &unordered_list.items[i]) != 1) {
            printf("Erro ao ler entrada %d.\n", i);
            return 1;
        }
    }

    // printf("Lista desordenada: ");
    // print_list(unordered_list);

    const List ordered_list = merge_sort(unordered_list);

    // printf("\n");
    // printf("Tamanho da lista: %d\n", unordered_list.len);
    // printf("Tamanho da lista ordenada: %d\n", ordered_list.len);

    // printf("Lista ordenada: ");
    print_list(ordered_list);

    return 0;
}

List merge_sort(const List list) {
    if (list.len == 1 || list.len == 0) {
        return list;
    }

    List left = split(list, 0, list.len/2);
    List right = split(list, list.len/2, list.len);

    left = merge_sort(left);
    right = merge_sort(right);

    List merged = merge(left, right);

    return merged;
}

List split(
    const List list,
    const unsigned int start,
    const unsigned int end
) {
    List new_list;
    new_list.len = 0;

    for (int i = start; i < end; i++) {
        new_list.items[i-start] = list.items[i];
        new_list.len += 1;
    }

    return new_list;
}

List merge(const List left, const List right) {
    List new_list;
    new_list.len = 0;

    unsigned int aux_l = 0;
    unsigned int aux_r = 0;

    while (aux_l < left.len && aux_r < right.len) {
        if (left.items[aux_l] > right.items[aux_r]) {
            new_list.items[new_list.len] = right.items[aux_r];
            aux_r += 1;
            new_list.len += 1;
            continue;
        }

        new_list.items[new_list.len] = left.items[aux_l];
        aux_l += 1;
        new_list.len += 1;
    }

    while (aux_l < left.len) {
        new_list.items[new_list.len] = left.items[aux_l];
        new_list.len += 1;
        aux_l += 1;
    }

    while (aux_r < right.len) {
        new_list.items[new_list.len] = right.items[aux_r];
        new_list.len += 1;
        aux_r += 1;
    }

    return new_list;
}

void print_list(List list) {
    for (int i = 0; i < list.len; i++) {
        printf("%d ", list.items[i]);
    }
    printf("\n");
}

