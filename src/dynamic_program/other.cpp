#include "dynamic_program/other.h"

#include <vector>
#include <limits>

namespace sakabatou_algorithm {
namespace dynamic_program {

int fib_recur_helper(std::vector<int>& memo, int n) {
  if (n == 1 || n == 2) return 1;
  if (memo[n] != 0) return memo[n];
  memo[n] = fib_recur_helper(memo, n - 1) + fib_recur_helper(memo, n - 2);
  return memo[n];
}

int fib_recur(int n) {
  if (n < 1) return 0;

  std::vector<int> memo(n + 1, 0);

  return fib_recur_helper(memo, n);
}

int fib_iter(int n) {
  // std::vector<int> memo(n + 1, 0);
  // memo[1] = 1;
  // memo[2] = 1;

  // for (int i = 3; i <= n; ++i) {
  //   memo[i] = memo[i - 1] + memo[i - 2];
  // }

  // return memo[n];

  // optimize space
  if (n == 1 || n == 2) return 1;
  int pre = 1, prepre = 1;
  for (int i = 3; i <= n; ++i) {
    int sum = pre + prepre;
    prepre = pre;
    pre = sum;
  }

  return pre;
}

int maxA(int n) {
  std::vector<int> dp(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    dp[i] = 1 + dp[i - 1];
    for (int j = 2; j < i; j++) {
      dp[i] = std::max(dp[i], dp[j - 2] * (i - j + 1));
    }
  }
  return dp[n];
}

int maxProfit_k_2(const std::vector<int>& prices) {
  int n = prices.size();
  int k = 2;
  // dp[i][j][k], i-第i天，j-最多交易j次，k：0-当前手上没有股票，1-当前手上有股票
  std::vector<std::vector<std::vector<int>>>
      dp(n + 1, std::vector<std::vector<int>>(k + 1, std::vector<int>(2, 0)));
  for (int i = 0; i <= n; i++) {
    dp[i][0][0] = 0;
    dp[i][0][1] = std::numeric_limits<int>::min();
  }
  for (int i = 0; i <= k; i++) {
    dp[0][i][0] = 0;
    dp[0][i][1] = std::numeric_limits<int>::min();
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      dp[i][j][0] = std::max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
      dp[i][j][1] = std::max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i - 1]);
    }
  }
  return dp[n][k][0];
}

} // dynamic_program
} // sakabatou_algorithm
