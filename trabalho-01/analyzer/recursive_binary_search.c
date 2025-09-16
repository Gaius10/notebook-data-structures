#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../lib/analysis.h"
#include "../lib/algorithms.h"
#include "../lib/merge_sort.h"

#define RBS_BIN_SIZE 10
#define RBS_TESTS_PER_SAMPLE 500

void _rbs_sample_analysis(int sample[], unsigned sample_len, FILE* output_file);

void analysis_rbs(
    unsigned sample_quantities[],
    unsigned sample_quantities_len,
    FILE* output_file
) {
    int sample[MAX_SAMPLE_LEN];
    unsigned sample_len;

    fprintf(output_file, "sample_len,time_spent\n");

    for (unsigned i = 0; i < sample_quantities_len; i++) {
        sample_len = sample_quantities[i];
        for (unsigned j = 0; j < sample_len; j++) {
            sample[j] = rand();
        }

        merge_sort(sample, sample_len);
        
        _rbs_sample_analysis(sample, sample_len, output_file);
    }
}

void _rbs_sample_analysis(int sample[], unsigned sample_len, FILE* output_file) {
    struct timespec start, end;
    long seconds, nanoseconds;

    int searches[RBS_BIN_SIZE];

    for (unsigned k = 0; k < RBS_TESTS_PER_SAMPLE; k++) {
        for (unsigned m = 0; m < RBS_BIN_SIZE; m++) {
            searches[m] = rand();
        }

        timespec_get(&start, TIME_UTC);
        /**********************
        * CORE OF ANALYSIS
        */
        for (unsigned m = 0; m < RBS_BIN_SIZE; m++) {
            recursive_binary_search(searches[m], sample, sample_len);
        }
        /**********************/
        timespec_get(&end, TIME_UTC);

        seconds = end.tv_sec - start.tv_sec;
        nanoseconds = end.tv_nsec - start.tv_nsec;

        if (nanoseconds < 0) {
            seconds -= 1;
            nanoseconds += 1000000000;
        }

        fprintf(
            output_file,
            "%u,%ld.%09ld\n",
            sample_len,
            seconds,
            nanoseconds
        );
    }
}
