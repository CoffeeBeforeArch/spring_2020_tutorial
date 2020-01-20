// This program shows off a neat optimization for fast a faster
// modulo operation in C++
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <random>
#include <vector>

using namespace std;

// Function for generating argument pairs
static void custom_args(benchmark::internal::Benchmark *b) {
  for (int i = 1 << 4; i <= 1 << 10; i <<= 2) {
    // Collect stats at 1/8, 1/2, and 7/8
    for (int j : {32, 128, 224}) {
      b = b->ArgPair(i, j);
    }
  }
}

// Baseline for intuitive modulo operation
static void baseMod(benchmark::State &s) {
  // Number of elements
  int N = s.range(0);

  // Max for mod operator
  int ceil = s.range(1);

  // Vector for input and output of modulo
  vector<int> input;
  vector<int> output;
  input.resize(N);
  output.resize(N);

  // Generate random inputs
  mt19937 rng;
  rng.seed(random_device()());
  uniform_int_distribution<int> dist(0, 255);
  for (int &i : input) {
    i = dist(rng);
  }

  while (s.KeepRunning()) {
    // Compute the modulo for each element
    for (int i = 0; i < N; i++) {
      output[i] = input[i] % ceil;
    }
  }
}
// Register the benchmark
BENCHMARK(baseMod)->Apply(custom_args);

// An unrolled version of our baseline
static void unrollMod(benchmark::State &s) {
  // Number of elements
  int N = s.range(0);

  // Max for mod operator
  int ceil = s.range(1);

  // Vector for input and output of modulo
  vector<int> input;
  vector<int> output;
  input.resize(N);
  output.resize(N);

  // Generate random inputs
  mt19937 rng;
  rng.seed(random_device()());
  uniform_int_distribution<int> dist(0, 255);
  for (int &i : input) {
    i = dist(rng);
  }

  while (s.KeepRunning()) {
    // Compute the modulo for each element
    for (int i = 0; i < N; i += 4) {
      output[i] = input[i] % ceil;
      output[i + 1] = input[i + 1] % ceil;
      output[i + 2] = input[i + 2] % ceil;
      output[i + 3] = input[i + 3] % ceil;
    }
  }
}
// Register the benchmark
BENCHMARK(unrollMod)->Apply(custom_args);

// Baseline for intuitive modulo operation
static void fastMod(benchmark::State &s) {
  // Number of elements
  int N = s.range(0);

  // Max for mod operator
  int ceil = s.range(1);

  // Vector for input and output of modulo
  vector<int> input;
  vector<int> output;
  input.resize(N);
  output.resize(N);

  // Generate random inputs
  mt19937 rng;
  rng.seed(random_device()());
  uniform_int_distribution<int> dist(0, 255);
  for (int &i : input) {
    i = dist(rng);
  }

  while (s.KeepRunning()) {
    // DON'T compute the mod for each element
    // Skip the expensive operation using a simple compare
    for (int i = 0; i < N; i++) {
      output[i] = (input[i] >= ceil) ? input[i] % ceil : input[i];
    }
  }
}
// Register the benchmark
BENCHMARK(fastMod)->Apply(custom_args);

// Baseline for intuitive modulo operation
static void fastModHint(benchmark::State &s) {
  // Number of elements
  int N = s.range(0);

  // Max for mod operator
  int ceil = s.range(1);

  // Vector for input and output of modulo
  vector<int> input;
  vector<int> output;
  input.resize(N);
  output.resize(N);

  // Generate random inputs
  mt19937 rng;
  rng.seed(random_device()());
  uniform_int_distribution<int> dist(0, 255);
  for (int &i : input) {
    i = dist(rng);
  }

  while (s.KeepRunning()) {
    // DON'T compute the mod for each element
    // Skip the expensive operation using a simple compare
    for (int i = 0; i < N; i++) {
      output[i] =
          __builtin_expect(input[i] >= ceil, 0) ? input[i] % ceil : input[i];
    }
  }
}
// Register the benchmark
BENCHMARK(fastModHint)->Apply(custom_args);

// Baseline for intuitive modulo operation
static void fastModHintBad(benchmark::State &s) {
  // Number of elements
  int N = s.range(0);

  // Max for mod operator
  int ceil = s.range(1);

  // Vector for input and output of modulo
  vector<int> input;
  vector<int> output;
  input.resize(N);
  output.resize(N);

  // Generate random inputs
  mt19937 rng;
  rng.seed(random_device()());
  uniform_int_distribution<int> dist(0, 255);
  for (int &i : input) {
    i = dist(rng);
  }

  while (s.KeepRunning()) {
    // DON'T compute the mod for each element
    // Skip the expensive operation using a simple compare
    for (int i = 0; i < N; i++) {
      output[i] =
          __builtin_expect(input[i] >= ceil, 1) ? input[i] % ceil : input[i];
    }
  }
}
// Register the benchmark
BENCHMARK(fastModHintBad)->Apply(custom_args);

// Benchmark main function
BENCHMARK_MAIN();
