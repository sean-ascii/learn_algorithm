#include "data_structure/monotonic_queue.h"

namespace sakabatou_algorithm {
namespace data_structure {

void MonotonicQueue::push(int n) {
  while (!q_.empty() && n >= q_.back()) {
    q_.pop_back();
  }

  q_.push_back(n);
}

int MonotonicQueue::max() {
  return q_.front();
}

void MonotonicQueue::pop(int n) {
  if (n == q_.front()) {
    q_.pop_front();
  }
}

std::vector<int> maxSlideWindow(const std::vector<int>& nums, const int k) {
  if (nums.size() < k) return {};

  std::vector<int> result(nums.size() - k + 1);

  MonotonicQueue window;
  for (int i = 0; i < nums.size(); ++i) {
    if (i < k - 1) {
      window.push(nums[i]);
    } else {
      window.push(nums[i]);
      result[i - k + 1] = window.max();
      window.pop(nums[i - k + 1]);
    }
  }

  return result;
}

} // data_structure
} // sakabatou_algorithm