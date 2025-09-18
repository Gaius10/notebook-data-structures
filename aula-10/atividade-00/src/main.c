#include <stdlib.h>
#include <stdio.h>
#include "../lib/stack.h"

int main() {
    Stack *s = create_stack();
    int handle;
    int result;

    result = push(s, 1);
    if (result == -1 ) {
        printf("Erro ao dar push 1\n");
        return 1;
    }

    result = push(s, 2);
    if (result == -1 ) {
        printf("Erro ao dar push 2\n");
        return 1;
    }

    print_stack(s);

    result = pop(s, &handle);
    if (result == -1 ) {
        printf("Erro ao dar push 2\n");
        return 1;
    }

    printf("handle = %d\n", handle);
    print_stack(s);

    return 0;
}

