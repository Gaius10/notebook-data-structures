#include <stdlib.h>
#include <stdio.h>
#include "../lib/stack.h"

int main() {
    int success, buffer;
    unsigned decimal;
    Stack* binary = create_stack();

    success = scanf("%u", &decimal);
    if (success != 1) {
        printf("Erro ao ler número decimal.\n");
        return 1;
    }

    do {
        push(binary, decimal % 2);
        decimal /= 2;
    } while(decimal > 0);

    while (pop(binary, &buffer) != -1) {
        printf("%u", buffer);
    }
    printf("\n");

    return 0;
}

