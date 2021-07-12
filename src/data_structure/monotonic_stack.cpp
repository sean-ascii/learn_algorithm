#include "data_structure/monotonic_stack.h"

namespace sakabatou_algorithm {
namespace data_structure {

std::vector<int> nextGreaterElement(const std::vector<int>& nums) {
  std::vector<int> result(nums.size());

  std::stack<int> s;
  for (int i = nums.size() - 1; i >= 0; --i) {
    while (!s.empty() && s.top() <= nums[i]) {
      s.pop();
    }

    if (s.empty())
      result[i] = -1;
    else
      result[i] = s.top();

    s.push(nums[i]);
  }
  return result;
}

std::vector<int> dailyTemperatures(const std::vector<int>& temps) {
  std::vector<int> result(temps.size());

  std::stack<int> s;
  for (int i = temps.size() - 1; i >= 0; --i) {
    while (!s.empty() && temps[s.top()] <= temps[i]) {
      s.pop();
    }

    if (s.empty())
      result[i] = 0;
    else
      result[i] = s.top() - i;

    s.push(i);
  }
  return result;
}

std::vector<int> nextGreaterElementWithLoop(const std::vector<int>& nums) {
  std::vector<int> result(nums.size());

  std::stack<int> s;
  for (int i = nums.size() - 1; i >= 0; --i) {
    while(!s.empty() && s.top() <= nums[i])
      s.pop();

    s.push(nums[i]);
  }

  for (int i = nums.size() - 1; i >= 0; --i) {
    while(!s.empty() && s.top() <= nums[i])
      s.pop();

    if (s.empty())
      result[i] = -1;
    else
      result[i] = s.top();

    s.push(nums[i]);
  }
  return result;
}

} // data_structure
} // sakabatou_algorithm