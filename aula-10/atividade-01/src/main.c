#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../lib/stack.h"

#define not !
#define STRING_MAX 100

int isnumeric(char* s);
int isoperand(char c);

void operate(int a, int b, char op, int* result);

int main() {
    int success;
    char arg[STRING_MAX];

    int a, b, result;

    Stack *buffer = create_stack();

    while (1) {
        success = scanf("%s", arg);
        if (success != 1) {
            break;
        }

        if (isnumeric(arg)) {
            success = push(buffer, atoi(arg));
            if (success == -1) {
                printf("Erro ao dar push (arg = %s).\n", arg);
                return 1;
            }

            continue;
        }

        if (isoperand(arg[0])) {
            success = pop(buffer, &b);
            if (success == -1) {
                printf("Erro ao recuperar topo da pilha (&a).\n");
                return 1;
            }

            success = pop(buffer, &a);
            if (success == -1) {
                printf("Erro ao recuperar topo da pilha (&b).\n");
                return 1;
            }

            operate(a, b, arg[0], &result);

            success = push(buffer, result);
            if (success == -1) {
                printf("Erro ao dar push (result).\n");
                return 1;
            }
        }
    }

    success = pop(buffer, &result);
    if (success == -1) {
        printf("Erro ao recuperar topo da pilha (result).\n");
        return 1;
    }

    printf("%d\n", result);

    return 0;
}

int isnumeric(char* s) {
    for (unsigned i = 0; s[i] != '\0'; i++) {
        if (not isdigit(s[i])) {
            return 0;
        }
    }

    return 1;
}

int isoperand(char c) {
    switch (c) {
        case '+':
        case '-':
        case '/':
        case '*':
            return 1;
        default:
            return 0;
    }
}

void operate(int a, int b, char op, int* result) {
    switch(op) {
        case '+':
           *result = a + b;
           break;
        case '-':
           *result = a - b;
           break;
        case '/':
           *result = a / b;
           break;
        case '*':
           *result = a * b;
           break;
    }
}

