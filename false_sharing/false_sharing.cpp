// This program shows off the sever implications of false sharing in
// C++ using std::atomic and std::thread

#include <benchmark/benchmark.h>
#include <atomic>
#include <thread>

// Simple function for incrememnting an atomic int
void work(std::atomic<int>& a) {
  for (int i = 0; i < 100000; i++) {
    a++;
  }
}

// Simple single-threaded function that calls work 4 times
void single_thread() {
  std::atomic<int> a;
  a = 0;

  work(a);
  work(a);
  work(a);
  work(a);
}

// A simple benchmark that runs our single-threaded implementation
static void singleThread(benchmark::State& s) {
  while (s.KeepRunning()) {
    single_thread();
  }
}
BENCHMARK(singleThread)->Unit(benchmark::kMillisecond);

// Tries to parallelize the work across multiple threads
// However, each core invalidates the other cores copies on a write
// This is an EXTREME example of poorly thought out code
void same_var() {
  std::atomic<int> a;
  a = 0;

  // Create four threads and use a lambda to launch work
  std::thread t1([&]() { work(a); });
  std::thread t2([&]() { work(a); });
  std::thread t3([&]() { work(a); });
  std::thread t4([&]() { work(a); });

  // Join the threads
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}

// A simple benchmark that runs our single-threaded implementation
static void directSharing(benchmark::State& s) {
  while (s.KeepRunning()) {
    same_var();
  }
}
BENCHMARK(directSharing)->UseRealTime()->Unit(benchmark::kMillisecond);

// How well does it work if we use different atomic ints?
// Not that well! But look at the addresses! They all reside on the
// same cache line. That means we have false sharing!
// (We invalidate variables that aren't actually being accessed
// because they happen to be on the same cache line)
void diff_var() {
  std::atomic<int> a{0};
  std::atomic<int> b{0};
  std::atomic<int> c{0};
  std::atomic<int> d{0};

  // Creat four threads and use lambda to launch work
  std::thread t1([&]() { work(a); });
  std::thread t2([&]() { work(b); });
  std::thread t3([&]() { work(c); });
  std::thread t4([&]() { work(d); });

  // Join the threads
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}

// A simple benchmark that runs our single-threaded implementation
static void falseSharing(benchmark::State& s) {
  while (s.KeepRunning()) {
    diff_var();
  }
}
BENCHMARK(falseSharing)->UseRealTime()->Unit(benchmark::kMillisecond);

// We can align the struct to 64 bytes
// Now each struct will be on a different cache line
struct alignas(64) AlignedType {
  AlignedType() { val = 0; }
  std::atomic<int> val;
};

// No more invalidations, so our code should be roughly the same as the
void diff_line() {
  AlignedType a{};
  AlignedType b{};
  AlignedType c{};
  AlignedType d{};

  // Launch the four threads now using our aligned data
  std::thread t1([&]() { work(a.val); });
  std::thread t2([&]() { work(b.val); });
  std::thread t3([&]() { work(c.val); });
  std::thread t4([&]() { work(d.val); });

  // Join the threads
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}

// A simple benchmark that runs our single-threaded implementation
static void noSharing(benchmark::State& s) {
  while (s.KeepRunning()) {
    diff_line();
  }
}
BENCHMARK(noSharing)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
