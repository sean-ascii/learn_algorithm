#include "dynamic_program/longest_increasing_subsquence.h"

#include <algorithm>

namespace sakabatou_algorithm {
namespace dynamic_program {

int maxEnvelopes(std::vector<std::pair<int, int>> envelopes) {
  std::sort(envelopes.begin(), envelopes.end(), [](const auto& l, const auto& r){
    if (l.first != r.first) {
      return l.first < r.first;
    } else {
      return l.second > r.second;
    }
  });

  int n = envelopes.size();
  std::vector<int> dp(n + 1, 0);
  dp[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (envelopes[i - 1].second > envelopes[i - 2].second) {
      dp[i] = dp[i - 1] + 1;
    } else {
      dp[i] = dp[i - 1];
    }
  }
  return dp[n];
}

} // dynamic_program
} // sakabatou_algorithm
