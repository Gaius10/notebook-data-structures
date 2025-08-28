#include <stdio.h>
#include "../lib/ponto.h"

#define OP_PRINT_P1 1
#define OP_PRINT_P2 2
#define OP_DISTANCE 3
#define OP_DISTANCE_ORIGIN_TO_P1 4
#define OP_DISTANCE_ORIGIN_TO_P2 5
#define OP_UPDATE_P1 6
#define OP_UPDATE_P2 7
#define OP_COMPARA 8
#define OP_EXIT 9

int main() {
    Ponto* p1 = NULL;
    Ponto* p2 = NULL;

    float x1, x2;
    float y1, y2;
    int read = 0;

    float distance = 0;
    int op;

    read = scanf("%f %f", &x1, &y1);
    if (read != 2) {
        printf("Erro ao ler coordenadas de P1.\n");
        return 1;
    }

    read = scanf("%f %f", &x2, &y2);
    if (read != 2) {
        printf("Erro ao ler coordenadas de P2.\n");
        return 1;
    }

    p1 = cria_ponto(x1, y1);
    p2 = cria_ponto(x2, y2);

    do {
        read = scanf("%d", &op);
        if (read != 1) {
            printf("Erro ao ler operação.\n");
            continue;
        }

        switch (op) {
            case OP_PRINT_P1:
                imprime_ponto(p1);
                break;
            case OP_PRINT_P2:
                imprime_ponto(p2);
                break;
            case OP_DISTANCE:
                distance = distancia(p1, p2);
                printf("%.3f\n", distance);
                break;
            case OP_DISTANCE_ORIGIN_TO_P1:
                distance = distancia_origem(p1);
                printf("%.3f\n", distance);
                break;
            case OP_DISTANCE_ORIGIN_TO_P2:
                distance = distancia_origem(p2);
                printf("%.3f\n", distance);
                break;
            case OP_UPDATE_P1:
                read = scanf("%f %f", &x1, &y1);
                if (read != 2) {
                    printf("Erro ao ler novas coordenadas P1.\n");
                    continue;
                }

                atribui_ponto(p1, x1, y1);
                break;
            case OP_UPDATE_P2:
                read = scanf("%f %f", &x2, &y2);
                if (read != 2) {
                    printf("Erro ao ler novas coordenadas P2.\n");
                    continue;
                }

                atribui_ponto(p2, x2, y2);
                break;
            case OP_COMPARA:
                printf("%d\n", pontos_iguais(p1, p2));
                break;
        }
    } while (op != OP_EXIT);

    libera_ponto(p1);
    libera_ponto(p2);

    return 0;
}

