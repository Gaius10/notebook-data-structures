#include <stdio.h>
#include "../lib/queue.h"

#define OP_EXIT 0
#define OP_ADD_1 1
#define OP_ADD_2 2
#define OP_PROCESS 3

void process(Queue* main_queue, Queue* secondary_queue);

int main() {
    int success;
    unsigned op;
    int arg;

    Queue* q1 = create_queue();
    Queue* q2 = create_queue();

    do {
        success = scanf("%u", &op);
        if (success != 1) {
            printf("Erro ao ler operação.\n");
            return 1;
        }

        switch (op) {
            case OP_ADD_1:
                success = scanf("%d", &arg);
                if (success != 1) {
                    printf("Erro ao ler argumento (add_1).\n");
                    return 1;
                }

                insert(q1, arg);
                break;
            case OP_ADD_2:
                success = scanf("%d", &arg);
                if (success != 1) {
                    printf("Erro ao ler argumento (add_2).\n");
                    return 1;
                }

                insert(q2, arg);
                break;
            case OP_PROCESS:
                process(q2, q1);
                process(q2, q1);
                process(q1, q2);
                break;
        }
    } while (op != OP_EXIT);

    return 0;
}

void process(Queue* main_queue, Queue* secondary_queue) {
    int success;
    int buffer;

    success = shift(main_queue, &buffer);
    if (success == -1) {
        success = shift(secondary_queue, &buffer);
    }

    if (success == 1) {
        printf("%d\n", buffer);
    }
}

