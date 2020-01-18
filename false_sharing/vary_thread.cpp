// This benchmark scales the number of threads in our false sharing benchmark
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <array>
#include <atomic>
#include <thread>

// Simple function for incrementing an atomic int
void work(std::atomic<int>& a, int n) {
  for (int i = 0; i < (400000 / n); i++) {
    a++;
  }
}

// Benchmark 2 threads
void bench2() {
  std::atomic<int> a{0};
  std::atomic<int> b{0};

  // Creat four threads and use lambda to launch work
  std::thread t1([&]() { work(a, 2); });
  std::thread t2([&]() { work(b, 2); });

  // Join the threads
  t1.join();
  t2.join();
}

// A simple benchmark that runs our single-threaded implementation
static void twoThreads(benchmark::State& s) {
  while (s.KeepRunning()) {
    bench2();
  }
}
BENCHMARK(twoThreads)->UseRealTime()->Unit(benchmark::kMillisecond);

// Benchmark 4 threads
void bench4() {
  std::atomic<int> a{0};
  std::atomic<int> b{0};
  std::atomic<int> c{0};
  std::atomic<int> d{0};

  // Creat four threads and use lambda to launch work
  std::thread t1([&]() { work(a, 4); });
  std::thread t2([&]() { work(b, 4); });
  std::thread t3([&]() { work(c, 4); });
  std::thread t4([&]() { work(d, 4); });

  // Join the threads
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}

// A simple benchmark that runs our single-threaded implementation
static void fourThreads(benchmark::State& s) {
  while (s.KeepRunning()) {
    bench4();
  }
}
BENCHMARK(fourThreads)->UseRealTime()->Unit(benchmark::kMillisecond);

// Benchmark 8 threads
void bench8() {
  std::atomic<int> a{0};
  std::atomic<int> b{0};
  std::atomic<int> c{0};
  std::atomic<int> d{0};
  std::atomic<int> e{0};
  std::atomic<int> f{0};
  std::atomic<int> g{0};
  std::atomic<int> h{0};

  // Creat four threads and use lambda to launch work
  std::thread t1([&]() { work(a, 8); });
  std::thread t2([&]() { work(b, 8); });
  std::thread t3([&]() { work(c, 8); });
  std::thread t4([&]() { work(d, 8); });
  std::thread t5([&]() { work(e, 8); });
  std::thread t6([&]() { work(f, 8); });
  std::thread t7([&]() { work(g, 8); });
  std::thread t8([&]() { work(h, 8); });

  // Join the threads
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
}

// A simple benchmark that runs our single-threaded implementation
static void eightThreads(benchmark::State& s) {
  while (s.KeepRunning()) {
    bench8();
  }
}
BENCHMARK(eightThreads)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
