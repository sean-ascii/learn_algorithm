#include "double_pointer/left_right_pointer.h"

namespace sakabatou_algorithm {
namespace double_pointer {
namespace left_right_pointer {

std::pair<int, int> findSum(const std::vector<int>& nums, int sum) {
  int left = 0, right = nums.size() - 1;

  while (left < right) {
    int temp_sum = nums[left] + nums[right];
    if (temp_sum == sum) {
      return std::make_pair(left + 1, right + 1);
    } else if (temp_sum < sum) {
      left++;
    } else {
      right--;
    }
  }

  return std::make_pair(-1, -1);
}

void reverse(std::vector<int>& nums) {
  if (nums.size() < 2) return;
  int left = 0, right = nums.size() - 1;

  while (left < right) {
    std::swap(nums[left], nums[right]);
    left++;
    right--;
  }
}

} // left_right_pointer
} // double_pointer
} // sakabatou_algorithm
