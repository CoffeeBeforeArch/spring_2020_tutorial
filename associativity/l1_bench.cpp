// This program shows off cache associativity using C++
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <vector>

using std::generate;
using std::vector;

// Benchmark for showing cache associativity
static void L1_Bench(benchmark::State &s) {
  // Const step size (4kB)
  const int step = 1 << 10;

  // Use a variable array size
  int size = 1 << s.range(0);
  vector<int> v(size);

  // Number of accesses
  const int MAX_ITER = 1 << 20;

  // Profile the runtime of different step sizes
  while (s.KeepRunning()) {
    int i = 0;
    for (int iter = 0; iter < MAX_ITER; iter++) {
      v[i]++;
      // Reset if we go off the end of the array
      i += step;
      if (i >= size) i = 0;
    }
  }
}
// Register the benchmark
BENCHMARK(L1_Bench)->DenseRange(13, 16)->Unit(benchmark::kMillisecond);

// Benchmark main function
BENCHMARK_MAIN();
