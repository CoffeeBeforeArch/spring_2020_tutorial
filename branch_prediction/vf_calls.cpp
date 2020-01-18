// This program shows the implications of run-time polymorphism
// on performance due to branch prediction

#include <benchmark/benchmark.h>
#include <algorithm>
#include <random>
#include <vector>

// A simple case of polymorphism
// One base class with a single virtual function
struct Mammal {
  virtual float getSomeNumber() const noexcept { return 1.0; }
};

struct Dog : Mammal {
  float getSomeNumber() const noexcept { return 2.0; }
};

struct Cat : Mammal {
  float getSomeNumber() const noexcept { return 3.0; }
};

// Benchmark where all same-type objects are grouped together
static void vf_sorted(benchmark::State& s) {
  // Create a vector to store mammals
  std::vector<Mammal*> zoo;

  // Use fill_n to insert many instances into the vector
  std::fill_n(std::back_inserter(zoo), 10000, new Mammal);
  std::fill_n(std::back_inserter(zoo), 10000, new Dog);
  std::fill_n(std::back_inserter(zoo), 10000, new Cat);

  // Acculate a sum here
  float sum = 0;

  // Profile here
  while (s.KeepRunning()) {
    // VF calls here are easy to predict because all instances of each type
    // are sequential in the vector
    for (auto* animal : zoo) {
      sum += animal->getSomeNumber();
    }
  }
}
BENCHMARK(vf_sorted)->Unit(benchmark::kMicrosecond);

// Benchmark where ordering of types is randomized
static void vf_unsorted(benchmark::State& s) {
  // Create a vector to store mammals
  std::vector<Mammal*> zoo;

  // Use fill_n to insert many instances into the vector
  std::fill_n(std::back_inserter(zoo), 10000, new Mammal);
  std::fill_n(std::back_inserter(zoo), 10000, new Dog);
  std::fill_n(std::back_inserter(zoo), 10000, new Cat);

  // Now shuffle the vector
  std::random_device rng;
  std::mt19937 urng(rng());
  std::shuffle(zoo.begin(), zoo.end(), urng);

  // Acculate a sum here
  float sum = 0;

  // Profile here
  while (s.KeepRunning()) {
    // VF Calls here are ~random, so the branch predictor will have
    // some trouble
    for (auto* animal : zoo) {
      sum += animal->getSomeNumber();
    }
  }
}
// Register the benchmark
BENCHMARK(vf_unsorted)->Unit(benchmark::kMicrosecond);

// Benchmark where ordering of types is striped
static void vf_striped(benchmark::State& s) {
  // Create a vector to store mammals
  std::vector<Mammal*> zoo;
  zoo.reserve(30000);

  // Fill the vector with groups of three objects
  for (int i = 0; i < 10000; i++) {
    zoo.emplace_back(new Mammal);
    zoo.emplace_back(new Dog);
    zoo.emplace_back(new Cat);
  }

  // Acculate a sum here
  float sum = 0;

  // Profile here
  while (s.KeepRunning()) {
    // VF calls occur in a pattern that is easy to predict
    for (auto* animal : zoo) {
      sum += animal->getSomeNumber();
    }
  }
}
// Register the benchmark
BENCHMARK(vf_striped)->Unit(benchmark::kMicrosecond);

// Main function
BENCHMARK_MAIN();
