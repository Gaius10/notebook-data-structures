#include <sys/time.h>
#include "../../lib/actions.h"

#define ITERATION_NUMBER 1000

int main() {
    struct timeval tv_start;
    struct timeval tv_end;
    struct timezone tz;

    // @todo inicializar lista de buscas (numeros aleatorios)

    gettimeofday(&tv_start, &tz);

    for (unsigned i = 0; i < ITERATION_NUMBER; i++) {
        // @todo buscar
    }

    gettimeofday(&tv_end, &tz);

    // @todo registrar tempo gasto

    return 0;
}

