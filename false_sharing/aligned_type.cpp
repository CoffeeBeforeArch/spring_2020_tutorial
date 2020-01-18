// This program shows how atomic integers may be allocated in C++
// By: Nick from CoffeeBeforeArch

#include <atomic>
#include <iostream>

// Our aligned atomic
struct alignas(64) AlignedType {
  AlignedType() { val = 0; }
  std::atomic<int> val;
};

int main() {
  // Now we're guaranteed that our atomics will be at least 64 bytes apart!
  AlignedType a{};
  AlignedType b{};
  AlignedType c{};
  AlignedType d{};

  // Print out the addresses
  std::cout << "Address of AlignedType a - " << &a << '\n';
  std::cout << "Address of AlignedType b - " << &b << '\n';
  std::cout << "Address of AlignedType c - " << &c << '\n';
  std::cout << "Address of AlignedType d - " << &d << '\n';

  return 0;
}
