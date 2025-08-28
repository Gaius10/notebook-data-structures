#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/ponto.h"

Ponto* cria_ponto(float x, float y) {
    Ponto* p = malloc(sizeof(Ponto));
    if (p == NULL) {
        printf("Erro ao alocar novo Ponto.\n");
        exit(1);
    }

    p->x = x;
    p->y = y;

    return p;
}

void libera_ponto(Ponto *p) {
    free(p);
}

void acessa_ponto(Ponto* p, float *x, float *y) {
    if (p == NULL) {
        printf("Ponto nulo não pode ser acessado.\n");
        exit(1);
    }

    *x = p->x;
    *y = p->y;
}

void atribui_ponto(Ponto *p, float x, float y) {
    if (p == NULL) {
        printf("Ponto nulo não pode ser acessado.\n");
        exit(1);
    }

    p->x = x;
    p->y = y;
}

float distancia(Ponto *p1, Ponto *p2) {
    if (p1 == NULL) {
        printf("Ponto nulo (p1) não pode ser acessado.\n");
        exit(1);
    }

    if (p2 == NULL) {
        printf("Ponto nulo (p2) não pode ser acessado.\n");
        exit(1);
    }

    return sqrt(
        pow(p1->x - p2->x, 2) +
        pow(p1->y - p2->y, 2)
    );
}

float distancia_origem(Ponto *p) {
    if (p == NULL) {
        printf("Ponto nulo não pode ser acessado.\n");
        exit(1);
    }

    Ponto* origem = cria_ponto(0, 0);
    return distancia(p, origem);
}

void imprime_ponto(Ponto *p) {
    if (p == NULL) {
        printf("Ponto nulo não pode ser impresso.\n");
        exit(1);
    }

    printf("x = %f\n", p->x);
    printf("y = %f\n", p->y);
}

int pontos_iguais(Ponto *p1, Ponto *p2) {
    if (p1 == NULL) {
        printf("Ponto nulo (p1) não pode ser comparado.\n");
        exit(1);
    }

    if (p2 == NULL) {
        printf("Ponto nulo (p2) não pode ser comparado.\n");
        exit(1);
    }

    if (p1->x == p2->x && p1->y == p2->y) {
        return 1;
    }

    return 0;
}

