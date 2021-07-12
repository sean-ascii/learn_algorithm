#include "dynamic_program/knapsack.h"

#include <limits>
#include <cassert>
#include <numeric>

#include <iostream>

namespace sakabatou_algorithm {
namespace dynamic_program {

int zero_one_knapsack(const std::vector<int>& wt, const std::vector<int>& val, const int capacity) {
  int n = wt.size();
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= capacity; ++j) {
      if (j - wt[i - 1] < 0) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - wt[i - 1]] + val[i - 1]);
      }
    }
  }
  return dp[n][capacity];
}

bool can_partition(const std::vector<int>& nums) {
  int sum = std::accumulate(nums.begin(), nums.end(), 0);
  if (sum % 2 != 0) return false;
  sum = sum / 2;
  int n = nums.size();
  std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(sum + 1, false));
  for (int i = 0; i <= n; ++i) dp[i][0] = true;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= sum; ++j) {
      if (j - nums[i - 1] < 0) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
      }
    }
  }
  return dp[n][sum];
}

int coin_change_1(const int amount, const std::vector<int>& coins) {
  int n = coins.size();
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(amount + 1, 0));
  // base case
  for (int i = 0; i <= n; ++i) dp[i][0] = 1;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= amount; ++j) {
      if (j - coins[i - 1] < 0) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
      }
    }
  }
  return dp[n][amount];
}

int coin_change_2(const int amount, const std::vector<int>& coins) {
  int n = coins.size();
  std::vector<std::vector<int>> dp(
      n + 1, std::vector<int>(amount + 1, std::numeric_limits<int>::max()));
  // base case
  for (int i = 0; i <= n; ++i) {
    dp[i][0] = 0;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= amount; ++j) {
      if (j - coins[i - 1] < 0) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = std::min(dp[i - 1][j], dp[i][j - coins[i - 1]] + 1);
      }
    }
  }
  return (dp[n][amount] == std::numeric_limits<int>::max()) ? -1 : dp[n][amount];
}

} // dynamic_program
} // sakabatou_algorithm
