#include "dynamic_program/max_coins.h"

#include <algorithm>

namespace sakabatou_algorithm {
namespace dynamic_program {

int max_coins(const std::vector<int>& nums) {
  int n = nums.size();
  std::vector<int> points(n + 2);
  points[0] = points[n + 1] = 1;
  for (int i = 1; i <= n; ++i) {
    points[i] = nums[i - 1];
  }
  std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2, 0));

  for (int i = n; i >= 0; --i) {
    for (int j = i + 1; j <= n + 1; ++j) {
      for (int k = i + 1; k < j; ++k) {
        dp[i][j] = std::max(dp[i][j], points[i] * points[k] * points[j] + dp[i][k] + dp[k][j]);
      }
    }
  }

  return dp[0][n + 1];
}

} // dynamic_program
} // sakabatou_algorithm
