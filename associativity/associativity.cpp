// This program shows off cache associativity using C++
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <algorithm>
#include <cstdlib>
#include <vector>

using std::generate;
using std::vector;

// Benchmark for showing cache associativity
static void assocBench(benchmark::State &s) {
  // Use a variable step size (power of 2)
  int step = 1 << s.range(0);

  // 32 MB vector
  const int N = 1 << 23;
  vector<int> v(N);

  // Number of accesses
  const int MAX_ITER = 1 << 20;

  // Profile the runtime of different step sizes
  while (s.KeepRunning()) {
    // Perform 10k accesses
    int i = 0;
    for (int iter = 0; iter < MAX_ITER; iter++) {
      // Just increment this int
      v[i]++;

      // Reset if we go off the end of the array
      i += step;
      if (i >= N) i = 0;
    }
  }
}
// Register the benchmark
BENCHMARK(assocBench)->DenseRange(0, 9)->Unit(benchmark::kMillisecond);

// Benchmark main function
BENCHMARK_MAIN();
