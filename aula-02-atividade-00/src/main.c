#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT 0
#define ADD 1
#define LIST 2
#define RANK_ONE 3

#define STRING_MAX_LEN 1000
#define NUM_NOTAS 3
#define MAX_ALUNOS 50

typedef struct {
    char nome[STRING_MAX_LEN];
    double notas[NUM_NOTAS];
    double media;
} Aluno;

int loop(Aluno alunos[], unsigned int* num_alunos);
void clear_buffer();

int add_aluno(Aluno alunos[], unsigned int* num_alunos);
int list_alunos(
    const Aluno alunos[],
    const unsigned int* num_alunos
);
int melhor_aluno(
    const Aluno alunos[],
    const unsigned int* num_alunos
);

int main() {
    unsigned int num_alunos = 0;
    Aluno alunos[MAX_ALUNOS];

    printf("Menu:\n");
    printf("%d. Adicionar aluno\n", ADD);
    printf("%d. Listar alunos\n", LIST);
    printf("%d. Mostrar aluno com a maior nota\n", RANK_ONE);
    printf("%d. Sair\n", EXIT);

    while (loop(alunos, &num_alunos));
    return 0;
}

int loop(Aluno alunos[], unsigned int* num_alunos) {
    unsigned int op;

    printf(" > ");

    if (scanf("%d", &op) != 1) {
        printf("Erro ao ler operação.\n");
        return 0;
    }

    switch (op) {
        case EXIT:
            return 0;
        case ADD:
            return add_aluno(alunos, num_alunos);
        case LIST:
            return list_alunos(alunos, num_alunos);
        case RANK_ONE:
            return melhor_aluno(alunos, num_alunos);
        default:
            printf("Operação inválida.\n");
            return 1;
    }

}

void clear_buffer() {
    int c;
    while ((c = getchar()) == '\n' && (c == EOF));
}

int add_aluno(Aluno alunos[], unsigned int* num_alunos) {
    Aluno novo;
    unsigned int sum_notas = 0;

    if (*num_alunos >= MAX_ALUNOS) {
        printf("Número máximo de alunos atingido.\n");
        return 1;
    }

    printf("Digite o nome do novo aluno: ");
    clear_buffer();
    if (fgets(novo.nome, STRING_MAX_LEN, stdin) == NULL) {
        printf("Erro ao ler nome.\n");
        return 0;
    }
    novo.nome[strlen(novo.nome) - 1] = '\0';

    printf("Digite as notas:\n");
    for (int i = 0; i < NUM_NOTAS; i++) {
        printf("Nota %d > ", i + 1);
        if (scanf("%lf", &novo.notas[i]) != 1) {
            printf("Erro ao ler nota %lf.\n", novo.notas[i]);
            return 1;
        }
        sum_notas += novo.notas[i];
    }

    novo.media = sum_notas / NUM_NOTAS;
    alunos[*num_alunos] = novo;
    *num_alunos = *num_alunos + 1;
    return 1;
}

int list_alunos(
    const Aluno alunos[],
    const unsigned int* num_alunos
) {
    printf("Numero de alunos: %d\n", *num_alunos);
    for (int i = 0; i < *num_alunos; i++) {
        printf(
            "%s\t%.2lf\n",
            alunos[i].nome,
            alunos[i].media
        );
    }

    return 1;
}

int melhor_aluno(
    const Aluno alunos[],
    const unsigned int* num_alunos
) {
    unsigned int melhor = 0;

    for (int i = 0; i < *num_alunos; i++) {
        if (alunos[i].media > alunos[melhor].media) {
            melhor = i;
        }
    }

    printf(
       "Melhor aluno: %s %.2lf\n",
       alunos[melhor].nome,
       alunos[melhor].media
    );
    return 1;
}

