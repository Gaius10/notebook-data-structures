#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/algorithms.h"
#include "../lib/merge_sort.h"

#define OP_INVERT 1
#define OP_SEQ_SEARCH 2
#define OP_BIN_SEARCH 3
#define OP_REC_BIN_SEARCH 4

[[gnu::hot, gnu::nonnull]]
inline long double benchmark(int (*func)(int, int *, unsigned), unsigned times,
                             int *result, int search, int *samples,
                             unsigned len) {
  struct timespec start, end;

  timespec_get(&start, TIME_UTC);

  int tmp_result;

  for (unsigned m = 0; m < times; m++) {
    tmp_result = func(search, samples, len);
  }

  timespec_get(&end, TIME_UTC);

  *result = tmp_result;

  return ((long double)(end.tv_sec - start.tv_sec) * 1e9L +
          (long double)(end.tv_nsec - start.tv_nsec)) /
         (long double)times;
}

[[gnu::hot, gnu::nonnull]]
inline long double benchmark_inv(void (*func)(int *, unsigned), unsigned times, int *samples,
                             unsigned len) {
  struct timespec start, end;

  timespec_get(&start, TIME_UTC);

  for (unsigned m = 0; m < times; m++) {
    func(samples, len);
  }

  timespec_get(&end, TIME_UTC);

  return ((long double)(end.tv_sec - start.tv_sec) * 1e9L +
          (long double)(end.tv_nsec - start.tv_nsec)) /
         (long double)times;
}

[[gnu::hot, gnu::nonnull]]
void run_benchmarks(FILE *output_file, unsigned times, int search, int *samples,
                    unsigned len) {
  long double dur;
  int result;

  for (unsigned i = 0; i < 10; i++) {
    dur = benchmark(binary_search, times, &result, search, samples, len);
    fprintf(output_file, "%s,%d,%.9Lf,%d\n", "bi", len, dur, result);

    dur = benchmark(recursive_binary_search, times, &result, search, samples,
                    len);
    fprintf(output_file, "%s,%d,%.9Lf,%d\n", "br", len, dur, result);

    dur = benchmark(sequential_search, times, &result, search, samples, len);
    fprintf(output_file, "%s,%d,%.9Lf,%d\n", "s", len, dur, result);

    dur = benchmark(sequential_search_ordered, times, &result, search, samples,
                    len);
    fprintf(output_file, "%s,%d,%.9Lf,%d\n", "so", len, dur, result);

    dur = benchmark_inv(invert, times, samples, len);
    fprintf(output_file, "%s,%d,%.9Lf,%d\n", "i", len, dur, result);
    // invert(samples, len);
  }
}

// Generate random samples between 0 and UINT16_MAX
// UINT16_MAX is arbitrary and can be changed as needed
void generate_samples(int *samples, unsigned len) {
  for (unsigned i = 0; i < len; i++) {
    samples[i] = 2 * i;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    return 1;
  }

  unsigned times = atoi(argv[1]);
  unsigned seed = atoi(argv[2]);

  FILE *output_file = fopen(argv[3], "w");
  if (output_file == NULL) {
    printf("Erro ao abrir arquivo de saída.\n");
    return 1;
  }

  fprintf(output_file, "method,elements,time,result\n");

  int samples[10000];
  unsigned quantities[] = {10, 50, 100, 500, 1000, 5000, 10000, 0};

  srand(seed);

  for (unsigned i = 0; quantities[i] != 0; i++) {
    unsigned len = quantities[i];

    generate_samples(samples, len);
    merge_sort(samples, len);

    run_benchmarks(output_file, times, INT32_MIN, samples, len);
    run_benchmarks(output_file, times, INT32_MAX, samples, len);

    for (unsigned j = 0; j < len; j++) {
      run_benchmarks(output_file, times, samples[j], samples, len);
      run_benchmarks(output_file, times, samples[j] + 1, samples, len);
    }
  }

  fclose(output_file);
  return 0;
}
