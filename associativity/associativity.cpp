// This program shows off cache associativity using C++
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <algorithm>
#include <cstdlib>
#include <vector>

using std::generate;
using std::vector;

// Function for generating argument pairs
static void l1_args(benchmark::internal::Benchmark *b) {
  for (int i : {256, 512, 1024}) {
    // Collect stats at 1/8, 1/2, and 7/8
    for (int j = 1 << 13; j <= 1 << 16; j <<= 1) {
      b = b->ArgPair(i, j);
    }
  }
}

// Function for generating argument pairs
static void l2_args(benchmark::internal::Benchmark *b) {
  for (int i : {4096, 8192, 16384}) {
    // Collect stats at 1/8, 1/2, and 7/8
    for (int j = 1 << 16; j <= 1 << 28; j <<= 1) {
      b = b->ArgPair(i, j);
    }
  }
}



// Benchmark for showing cache associativity
static void L1_Bench(benchmark::State &s) {
  // Use a variable step size (power of 2)
  int step = s.range(0);
  int size = s.range(1);

  // 32 MB vector
  vector<int> v(size);

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
      if (i >= size) i = 0;
    }
  }
}
// Register the benchmark
BENCHMARK(L1_Bench)->Apply(l1_args)->Unit(benchmark::kMillisecond);

// Benchmark for showing cache associativity
static void L2_Bench(benchmark::State &s) {
  // Use a variable step size (power of 2)
  int step = s.range(0);
  int size = s.range(1);

  // 32 MB vector
  vector<int> v(size);

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
      if (i >= size) i = 0;
    }
  }
}
// Register the benchmark
BENCHMARK(L2_Bench)->Apply(l2_args)->Unit(benchmark::kMillisecond);


// Benchmark main function
BENCHMARK_MAIN();
