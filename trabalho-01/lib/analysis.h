#ifndef ANALYSIS_H
#define ANALYSIS_H

#define MAX_SAMPLE_LEN 10000

void analysis_invert(
    unsigned sample_quantities[],
    unsigned sample_quantities_len,
    FILE* output
);

void analysis_ss(
    unsigned sample_quantities[],
    unsigned sample_quantities_len,
    FILE* output
);

void analysis_bs(
    unsigned sample_quantities[],
    unsigned sample_quantities_len,
    FILE* output
);

void analysis_rbs(
    unsigned sample_quantities[],
    unsigned sample_quantities_len,
    FILE* output
);

#endif

