// application of mono-stack

#pragma once

#include <queue>
#include <vector>

namespace sakabatou_algorithm {
namespace data_structure {

class MonotonicQueue {
 public:
  void push(int n);
  int max();
  void pop(int n);

 private:
  std::deque<int> q_;
};

std::vector<int> maxSlideWindow(const std::vector<int>& nums, const int k);

} // data_structure
} // sakabatou_algorithm