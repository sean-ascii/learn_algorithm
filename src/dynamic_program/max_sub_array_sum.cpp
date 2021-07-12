#include "dynamic_program/max_sub_array_sum.h"

#include <limits>

namespace sakabatou_algorithm {
namespace dynamic_program {

int max_sub_array_sum(const std::vector<int>& nums) {
  if (nums.empty()) return 0;
  int n = nums.size();
  std::vector<int> dp(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    dp[i] = std::max(nums[i - 1], dp[i - 1] + nums[i - 1]);
  }

  int result = std::numeric_limits<int>::lowest();
  for (int i = 1; i <= n; ++i) {
    result = std::max(dp[i], result);
  }

  return result;
}

} // dynamic_program
} // sakabatou_algorithm
