#include <stdio.h>
#include <stdlib.h>
#include "../lib/dsl.h"

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
    DSL* list = dsl_create();
    if (list == NULL) {
        printf("Erro ao criar lista.\n");
        return 1;
    }

    unsigned op;
    unsigned read;
    int result, arg1, arg2;

    DSL_Type* item_buffer = malloc(sizeof(DSL_Type));
    unsigned* search_pos_buffer = malloc(sizeof(unsigned));

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

                result = dsl_push(list, arg1);
                printf("%d\n", result);

                break;
            case OP_INSERT:
                read = scanf("%d %d", &arg1, &arg2);
                if (read != 2) {
                    printf("Erro ao ler argumentos (insert).\n");
                    continue;
                }

                result = dsl_insert(list, arg1, arg2);
                printf("%d\n", result);

                break;
            case OP_REMOVE:
                read = scanf("%d", &arg1);
                if (read != 1) {
                    printf("Erro ao ler argumentos (remove).\n");
                    continue;
                }

                result = dsl_remove(list, arg1, item_buffer);
                printf("%d\n", *item_buffer);

                break;
            case OP_SEEK:
                read = scanf("%d", &arg1);
                if (read != 1) {
                    printf("Erro ao ler argumentos (seek).\n");
                    continue;
                }

                result = dsl_seek(list, arg1, item_buffer);
                if (result == -1) {
                    printf("ERRO\n");
                    continue;
                }

                printf("%d\n", *item_buffer);
                break;
            case OP_SEARCH:
                read = scanf("%d", &arg1);
                if (read != 1) {
                    printf("Erro ao ler argumentos (search).\n");
                    continue;
                }

                result = dsl_search(list, arg1, search_pos_buffer);
                printf("%d\n", *search_pos_buffer);

                break;
            case OP_LEN:
                result = dsl_get_length(list);
                printf("%u\n", result);
                break;
            case OP_PRINT:
                result = dsl_print(list);
                break;
            case OP_CLEAR:
                result = dsl_clear(list);
                break;
        }
    } while (op != OP_EXIT);

    dsl_destroy(&list);
    free(item_buffer);
    free(search_pos_buffer);
    return 0;
}
