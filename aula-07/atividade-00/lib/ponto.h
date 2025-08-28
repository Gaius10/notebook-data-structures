
#ifndef PONTO_H
#define PONTO_H

typedef struct {
    float x;
    float y;
} Ponto;

Ponto* cria_ponto(float x, float y);

void libera_ponto(Ponto *p);
void acessa_ponto(Ponto* p, float *x, float *y);
void atribui_ponto(Ponto *p, float x, float y);

float distancia(Ponto *p1, Ponto *p2);
float distancia_origem(Ponto *p);

void imprime_ponto(Ponto *p);

int pontos_iguais(Ponto *p1, Ponto *p2);

#endif

