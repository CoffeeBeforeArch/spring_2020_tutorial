// This program shows how atomic integers may be allocated in C++
// By: Nick from CoffeeBeforeArch

#include <atomic>
#include <iostream>

int main() {
  // If we create four atomic integers like this, there's a high probability
  // they'll wind up next to each other in memory
  std::atomic<int> a;
  std::atomic<int> b;
  std::atomic<int> c;
  std::atomic<int> d;

  // Print out the addresses
  std::cout << "Address of atomic<int> a - " << &a << '\n';
  std::cout << "Address of atomic<int> b - " << &b << '\n';
  std::cout << "Address of atomic<int> c - " << &c << '\n';
  std::cout << "Address of atomic<int> d - " << &d << '\n';

  return 0;
}
