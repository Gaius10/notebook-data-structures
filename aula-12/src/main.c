#include <stdio.h>
#include <stdlib.h>
#include "../lib/linked-list.h"

#define OP_INSERT_LISTA_1 1
#define OP_INSERT_LISTA_2 2
#define OP_REMOVE_LISTA_1 3
#define OP_REMOVE_LISTA_2 4
#define OP_APPEND_LISTA_1 5
#define OP_APPEND_LISTA_2 6
#define OP_PRINT_LISTA_1 7
#define OP_PRINT_LISTA_2 8
#define OP_EXIT 9

Node* cria();
void insere(Node* lista);
void remove(Node* lista);
void append(Node* antes, Node* depois);

int main() {
    Node* lista1 = NULL;
    Node* lista2 = NULL;

    unsigned op;
    unsigned success_buffer;

    do {
        success_buffer = scanf("%u", &op);
        if (success_buffer != 1) {
            printf("Erro ao ler operação.\n");
            return 1;
        }

        switch (op) {
            case OP_INSERT_LISTA_1:
                if (lista1 == NULL) {
                    lista1 = cria();
                    continue();
                }

                insere(lista1);
                break;
            case OP_INSERT_LISTA_2:
                if (lista2 == NULL) {
                    lista2 = cria();
                    continue();
                }

                insere(lista2);
                break;
            case OP_REMOVE_LISTA_1:
                remove(lista1);
                break;
            case OP_REMOVE_LISTA_2:
                remove(lista2);
                break;
            case OP_APPEND_LISTA_1:
                append(lista1, lista2);
                break;
            case OP_APPEND_LISTA_2:
                append(lista2, lista1);
                break;
            case OP_PRINT_LISTA_1:
                printl(lista1);
                break;
            case OP_PRINT_LISTA_2:
                printl(lista2);
                break;
        }
    } while (op != OP_EXIT);
}

Node* cria() {
    Node* n;
    unsigned success_buffer;
    unsigned index;
    int value;

    success_buffer = scanf("%u", &index);
    if (success_buffer != 1) {
        printf("Erro ao ler indice na criação de nova lista.\n");
        exit(1);
    }

    if (index != 0) {
        printf("Não é possível inicializar uma lista pelo %u-ésimo elemento.\n");
        exit(1);
    }

    success_buffer = scanf("%d", &value);
    if (success_buffer != 1) {
        printf("Erro ao ler elemento na criação de uma lista.\n");
        exit(1);
    }

    n = create(value);
    return n;
}

void insere(Node* lista) {
    unsigned success_buffer;
    unsigned pos;
    int value;

    success_buffer = scanf("%u", &pos);
    if (success_buffer != 1) {
        printf("Erro ao ler posição de inserção de novo valor.\n");
        exit(1);
    }

    success_buffer = scanf("%d", &value);
    if (success_buffer != 1) {
        printf("Erro ao ler valor a ser inserido na lista.\n");
        exit(1);
    }

    success_buffer = insert_at(lista, pos, value);
    if (success_buffer == -1) {
        printf("Erro ao inserir valor na lista.\n");
        exit(1);
    }
}

void remove(Node* lista) {
    unsigned success_buffer;
    unsigned pos;
    int value;

    success_buffer = scanf("%u", &pos);
    if (success_buffer != 1) {
        printf("Erro ao ler posição de remoção.\n");
        exit(1);
    }

    remove_index(lista, pos, &value);
    if (success_buffer == -1) {
        printf("Erro ao remover valor da lista.\n");
        exit(1);
    }

    printf("%d\n", value);
}

void append(Node* antes, Node* depois) {
    while (antes->next != NULL) {
        antes = antes->next;
    }

    antes->next = depois;
}
