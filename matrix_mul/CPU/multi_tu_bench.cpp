// This program is a simple benchmark for matrix multiplication to show off
// aliasing
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <cstdlib>

// Function prototypes
void base_mmul(const int *a, const int *b, int *c, const int N);

// Baseline matrix multiplication that suffers from pointer aliasing
static void baseline(benchmark::State &s) {
  // Unpack the dimension of the square matrix
  const int N = 1 << s.range(0);

  // Allocate for our matrices
  int *a = new int[N * N]();
  int *b = new int[N * N]();
  int *c = new int[N * N]();

  // Region to profile
  while (s.KeepRunning()) {
    base_mmul(a, b, c, N);
  }

  // Free our memory
  delete[] a;
  delete[] b;
  delete[] c;
}
BENCHMARK(baseline)->DenseRange(8, 10)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
