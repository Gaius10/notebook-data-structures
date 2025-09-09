#include <stdlib.h>
#include <sys/time.h>
#include "../lib/actions.h"

#define ITERATIONS_NUMBER 1000

int main() {
    srand(7214);

    struct timeval tv_start;
    struct timeval tv_end;
    struct timezone tz;

    int search[ITERATIONS_NUMBER];

    for (unsigned i = 0; i < ITERATIONS_NUMBER; i++) {
        search[i] = rand();
    }

    printf("Numeros aleatorios gerados: \n");
    for (unsigned i = 0; i < ITERATIONS_NUMBER; i++) {
        printf("%d\n", search[i]);
    }

    // @todo inicializar lista de buscas (numeros aleatorios)

    // gettimeofday(&tv_start, &tz);

    // for (unsigned i = 0; i < ITERATIONS_NUMBER; i++) {
        // @todo buscar
    // }

    // gettimeofday(&tv_end, &tz);

    // @todo registrar tempo gasto

    return 0;
}

