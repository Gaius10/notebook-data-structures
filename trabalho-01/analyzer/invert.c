#include <stdio.h>
#include <time.h>
#include <math.h>

#include "../lib/analysis.h"
#include "../lib/algorithms.h"

void analysis_invert(
    unsigned sample_quantities[],
    unsigned sample_quantities_len,
    FILE* output_file
) {
    struct timespec start, end;
    long seconds, nanoseconds;

    for (unsigned i = 0; i < sample_quantities_len; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (unsigned j = 0; j < sample_quantities[i]; j++) {
            // @todo act
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        seconds = end.tv_sec - start.tv_sec;
        nanoseconds = end.tv_nsec - start.tv.nsec;

        if (nanoseconds < 0) {
            seconds -= 1;
            nanoseconds += 1000000000;
        }

        fprintf(
            output_file,
            "%u %ld.%09ld\n",
            sample_quantities[i],
            seconds,
            nanoseconds
        );
    }
}

