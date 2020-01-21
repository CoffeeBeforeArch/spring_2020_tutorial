// This program shows off cache associativity using C++
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <vector>

using std::vector;

// Benchmark for showing cache associativity
static void LLC_Bench(benchmark::State &s) {
  // Const step size (512kB)
  const int step = 1 << 17;

  // Use a variable array size
  const int size = 1 << s.range(0);
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
BENCHMARK(LLC_Bench)->DenseRange(20, 30)->Unit(benchmark::kMillisecond);

// Benchmark main function
BENCHMARK_MAIN();
