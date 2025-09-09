#include <stdio.h>
#include "../lib/ssl.h"

#define OP_PUSH 1
#define OP_INSERT 2
#define OP_REMOVE 3
#define OP_SEEK 4
#define OP_SEARCH 5
#define OP_LEN 6
#define OP_PRINT 7
#define OP_CLEAR 8
#define OP_EXIT 9

int main() {
    SSL* list = ssl_create();
    if (list == NULL) {
        printf("Erro ao criar lista.\n");
        return 1;
    }

    unsigned op;
    unsigned read;
    int result, arg1, arg2;

    SSL_Type* item_buffer = NULL;
    unsigned* search_pos_buffer = NULL;

    do {
        read = scanf("%u", &op);
        if (read != 1) {
            printf("Erro ao ler operação.\n");
            continue;
        }

        switch (op) {
            case OP_PUSH:
                read = scanf("%d", &arg1);
                if (read != 1) {
                    printf("Erro ao ler argumentos (push).\n");
                    continue;
                }

                result = ssl_push(list, arg1);
                // @todo tratar result
                break;
            case OP_INSERT:
                read = scanf("%d %d", &arg1, &arg2);
                if (read != 2) {
                    printf("Erro ao ler argumentos (insert).\n");
                    continue;
                }

                result = ssl_insert(list, arg1, arg2);
                // @todo tratar result
                break;
            case OP_REMOVE:
                read = scanf("%d", &arg1);
                if (read != 1) {
                    printf("Erro ao ler argumentos (remove).\n");
                    continue;
                }

                result = ssl_remove(list, arg1, item_buffer);
                // @todo tratar result
                printf("%d\n", *item_buffer);

                break;
            case OP_SEEK:
                read = scanf("%d", &arg1);
                if (read != 1) {
                    printf("Erro ao ler argumentos (seek).\n");
                    continue;
                }

                result = ssl_seek(list, arg1, item_buffer);
                // @todo tratar result
                printf("%d\n", *item_buffer);

                break;
            case OP_SEARCH:
                read = scanf("%d", &arg1);
                if (read != 1) {
                    printf("Erro ao ler argumentos (search).\n");
                    continue;
                }

                result = ssl_search(list, arg1, search_pos_buffer);
                // @todo tratar result
                printf("%d\n", *search_pos_buffer);

                break;
            case OP_LEN:
                result = ssl_len(list);
                printf("%u\n", result);
                break;
            case OP_PRINT:
                ssl_print(list);
                break;
            case OP_CLEAR:
                ssl_clear(list);
                break;
        }

    } while (op != OP_EXIT);

    ssl_destroy(&list);
    return 0;
}

