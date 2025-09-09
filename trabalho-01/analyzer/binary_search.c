#include <stdio.h>
#include "../lib/analysis.h"
#include "../lib/algorithms.h"

void analysis_bs(
    unsigned sample_quantities[],
    unsigned sample_quantities_len,
    FILE* output_file
) {
    printf("Binary searching...\n");

    fprintf(
        output_file,
        "sample_quantities_len = %u\n",
        sample_quantities_len
    );

    for (unsigned i = 0; i < sample_quantities_len; i++) {
        fprintf(output_file, "%u ", sample_quantities[i]);
    }
    fprintf(output_file, "\n");
}

