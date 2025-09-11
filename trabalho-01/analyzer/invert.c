#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../lib/analysis.h"
#include "../lib/algorithms.h"
#include "../lib/merge_sort.h"

void analysis_invert(
    unsigned sample_quantities[],
    unsigned sample_quantities_len,
    FILE* output_file
) {
    struct timespec start, end;
    long seconds, nanoseconds;

    int sample[MAX_SAMPLE_LEN];
    unsigned sample_len;

    for (unsigned i = 0; i < sample_quantities_len; i++) {
        sample_len = sample_quantities[i];
        for (unsigned j = 0; j < sample_len; j++) {
            sample[j] = rand();
        }

        merge_sort(sample, sample_len);

        timespec_get(&start, TIME_UTC);

        invert(sample, sample_len);

        timespec_get(&end, TIME_UTC);

        seconds = end.tv_sec - start.tv_sec;
        nanoseconds = end.tv_nsec - start.tv_nsec;

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

