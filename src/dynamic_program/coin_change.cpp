#include "dynamic_program/coin_change.h"

#include <limits>
#include <unordered_map>
#include <vector>

namespace sakabatou_algorithm {
namespace dynamic_program {

int coin_change_helper(const std::unordered_set<int>& coin_set, const int amount,
                       std::unordered_map<int, int>& memo) {
  if (amount == 0) return 0;
  if (amount < 0) return -1;

  if (memo.count(amount)) return memo[amount];

  int result = std::numeric_limits<int>::max();
  for (auto& coin : coin_set) {
    int sub_result = coin_change_helper(coin_set, amount - coin, memo);
    if (sub_result == -1) continue;
    result = std::min(result, 1 + sub_result);
  }

  if (result == std::numeric_limits<int>::max()) {
    memo[amount] = -1;
  } else {
    memo[amount] = result;
  }

  return memo[amount];
}

int coin_change_recur(const std::unordered_set<int>& coin_set, const int amount) {
  std::unordered_map<int, int> memo;
  return coin_change_helper(coin_set, amount, memo);
}

int coin_change_iter(const std::unordered_set<int>& coin_set, const int amount) {
  std::vector<int> dp(amount + 1, amount + 1);

  dp[0] = 0;

  for (int i = 0; i <= amount; ++i) {
    for (auto& coin : coin_set) {
      if (i - coin < 0) continue;
      dp[i] = std::min(dp[i], 1 + dp[i - coin]);
    }
  }

  return (dp[amount] == amount + 1) ? -1 : dp[amount];
}

} // dynamic_program
} // sakabatou_algorithm
