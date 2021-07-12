#include "dynamic_program/max_coins.h"

#include<utility>

namespace sakabatou_algorithm {
namespace dynamic_program {

int stoneGame(const std::vector<int>& piles) {
  int n = piles.size();
  std::vector<std::vector<std::pair<int, int>>>
      dp(n, std::vector<std::pair<int, int>>(n, std::pair<int, int>{0, 0}));
  for (int i = 0; i < n; i++) {
    dp[i][i].first = piles[i];
    dp[i][i].second = 0;
  }
  for (int l = 1; l < n; l++) {
    for (int i = n - 1; i >= 0; i--) {
      int j = l + i;
      if (j >= n) continue;
      int select_left = piles[i] + dp[i + 1][j].second;
      int select_right = piles[j] + dp[i][j - 1].second;
      if (select_left > select_right) {
        dp[i][j].first = select_left;
        dp[i][j].second = dp[i + 1][j].first;
      } else {
        dp[i][j].first = select_right;
        dp[i][j].second = dp[i][j - 1].first;
      }
    }
  }
  return dp[0][n - 1].first - dp[0][n - 1].second;
}

} // dynamic_program
} // sakabatou_algorithm
