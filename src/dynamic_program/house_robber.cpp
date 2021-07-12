#include "dynamic_program/house_robber.h"

// #include <algorithm>

namespace sakabatou_algorithm {
namespace dynamic_program {

int rob_1_helper(const std::vector<int>& nums, int start, std::vector<int>& memo) {
  if (start >= nums.size()) {
    return 0;
  }

  if (memo[start] != -1) return memo[start];

  int res = std::max(rob_1_helper(nums, start + 1, memo),
                     nums[start] + rob_1_helper(nums, start + 2, memo));
  memo[start] = res;
  return res;
}

int rob_1_recur(const std::vector<int>& nums) {
  int n = nums.size();
  std::vector<int> memo(n, -1);
  return rob_1_helper(nums, 0, memo);
}

int rob_1_dp(const std::vector<int>& nums) {
  int n = nums.size();
  std::vector<int> dp(n + 2, 0);
  for (int i = n - 1; i >= 0; i--) {
    dp[i] = std::max(dp[i + 1], nums[i] + dp[i + 2]);
  }
  return dp[0];
}

int rob_2_range(const std::vector<int>& nums, const int start, const int end) {
  int dp_i_1 = 0, dp_i_2 = 0;
  int dp_i = 0;
  for (int i = end; i >= start; --i) {
    dp_i = std::max(dp_i_1, dp_i_2 + nums[i]);
    dp_i_2 = dp_i_1;
    dp_i_1 = dp_i;
  }
  return dp_i;
}

int rob_2_dp(const std::vector<int>& nums) {
  int n = nums.size();
  if (n == 1) return nums[0];
  return std::max(rob_2_range(nums, 0, n - 2),
                  rob_2_range(nums, 1, n - 1));
}

} // dynamic_program
} // sakabatou_algorithm
