#include <iostream>
#include <chrono>

int main(int argc, char** argv) {
  auto start = std::chrono::system_clock::now();
  // compute

  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << "compute consume: " << diff.count() * 1000 << " ms" <<std::endl;
  return 0;
}
