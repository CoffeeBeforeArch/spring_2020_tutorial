// This program shows how the prefetching impacts performance in C++
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <random>
#include <vector>

// Accesses an array sequentially in row-major fashion
static void rowMajor(benchmark::State &s) {
  // Input/output vector size
  int N = 1 << s.range(0);

  // Create our input indices
  std::vector<int> v_in(N * N);
  std::iota(begin(v_in), end(v_in), 0);

  // Create an output vector
  std::vector<int> v_out(N * N);

  // Profile a simple traversal with simple additions
  while (s.KeepRunning()) {
    for (int i = 0; i < N * N; i++) {
      v_out[v_in[i]]++;
    }
  }
}
// Register the benchmark
BENCHMARK(rowMajor)->DenseRange(10, 12)->Unit(benchmark::kMillisecond);

// Accesses an array sequentially in reverse row-major
static void reverse(benchmark::State &s) {
  // Input/output vector size
  int N = 1 << s.range(0);

  // Create our input indices
  std::vector<int> v_in(N * N);
  std::iota(begin(v_in), end(v_in), 0);
  std::reverse(begin(v_in), end(v_in));

  // Create an output vector
  std::vector<int> v_out(N * N);

  // Profile a simple traversal with simple additions
  while (s.KeepRunning()) {
    for (int i = 0; i < N * N; i++) {
      // Pre-fetch an item for later
      v_out[v_in[i]]++;
    }
  }
}
// Register the benchmark
BENCHMARK(reverse)->DenseRange(10, 12)->Unit(benchmark::kMillisecond);

// Accesses an array sequentially in row-major fashion
static void cacheLine(benchmark::State &s) {
  // Input/output vector size
  int N = 1 << s.range(0);

  // Cache line size
  const int stride = 64 / sizeof(int);

  // Create our input indices
  std::vector<int> v_in(N * N);

  // For each element in a cache line
  int index = 0;
  for (int i = 0; i < stride; i++) {
    // For each cache line in the array
    for (int j = 0; j < (N * N / stride); j++) {
      v_in[index] = j * stride + i;
      index++;
    }
  }

  // Create an output vector
  std::vector<int> v_out(N * N);

  // Profile a simple traversal with simple additions
  while (s.KeepRunning()) {
    for (int i = 0; i < N * N; i++) {
      v_out[v_in[i]]++;
    }
  }
}
// Register the benchmark
BENCHMARK(cacheLine)->DenseRange(10, 12)->Unit(benchmark::kMillisecond);

// Accesses an array sequentially in row-major fashion
static void cacheLineReverse(benchmark::State &s) {
  // Input/output vector size
  int N = 1 << s.range(0);

  // Cache line size
  const int stride = 64 / sizeof(int);

  // Create our input indices
  std::vector<int> v_in(N * N);

  // For each element in a cache line
  int index = 0;
  for (int i = 0; i < stride; i++) {
    // For each cache line in the array
    for (int j = 0; j < (N * N / stride); j++) {
      v_in[index] = j * stride + i;
      index++;
    }
  }

  // Reverse the indices
  std::reverse(begin(v_in), end(v_in));

  // Create an output vector
  std::vector<int> v_out(N * N);

  // Profile a simple traversal with simple additions
  while (s.KeepRunning()) {
    for (int i = 0; i < N * N; i++) {
      v_out[v_in[i]]++;
    }
  }
}
// Register the benchmark
BENCHMARK(cacheLineReverse)->DenseRange(10, 12)->Unit(benchmark::kMillisecond);

// Accesses an array in column-major order
static void columnMajor(benchmark::State &s) {
  // Input/output vector size
  int N = 1 << s.range(0);

  // Create our input indices
  std::vector<int> v_in(N * N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      v_in[i * N + j] = j * N + i;
    }
  }

  // Create an output vector
  std::vector<int> v_out(N * N);

  // Profile a simple traversal with simple additions
  while (s.KeepRunning()) {
    for (int i = 0; i < N * N; i++) {
      v_out[v_in[i]]++;
    }
  }
}
// Register the benchmark
BENCHMARK(columnMajor)->DenseRange(10, 12)->Unit(benchmark::kMillisecond);

// Accesses an array in randomized order
static void random(benchmark::State &s) {
  // Input/output vector size
  int N = 1 << s.range(0);

  // Create our input indices
  std::vector<int> v_in(N * N);
  std::iota(begin(v_in), end(v_in), 0);

  // Now shuffle the vector
  std::random_device rng;
  std::mt19937 urng(rng());
  std::shuffle(begin(v_in), end(v_in), urng);

  // Create an output vector
  std::vector<int> v_out(N * N);

  // Profile a simple traversal with simple additions
  while (s.KeepRunning()) {
    for (int i = 0; i < N * N; i++) {
      v_out[v_in[i]]++;
    }
  }
}
// Register the benchmark
BENCHMARK(random)->DenseRange(10, 12)->Unit(benchmark::kMillisecond);

// Accesses in a random order but try pre-fetching
static void randomPrefetch(benchmark::State &s) {
  // Input/output vector size
  int N = 1 << s.range(0);

  // Create our input indices
  std::vector<int> v_in(N * N);
  std::iota(begin(v_in), end(v_in), 0);

  // Now shuffle the vector
  std::random_device rng;
  std::mt19937 urng(rng());
  std::shuffle(begin(v_in), end(v_in), urng);

  // Create an output vector
  std::vector<int> v_out(N * N);

  // Profile a simple traversal with simple additions
  while (s.KeepRunning()) {
    for (int i = 0; i < N * N; i++) {
      // Pre-fetch an item for later
      __builtin_prefetch(&v_out[v_in[i + 7]]);
      v_out[v_in[i]]++;
    }
  }
}
// Register the benchmark
BENCHMARK(randomPrefetch)->DenseRange(10, 12)->Unit(benchmark::kMillisecond);

// Benchmark main functions
BENCHMARK_MAIN();
