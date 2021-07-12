#include "dynamic_program/longest_common_subsquence.h"

#include <vector>
#include <algorithm>

namespace sakabatou_algorithm {
namespace dynamic_program {

int longest_common_subsquence(std::string s1, std::string s2) {
  int m = s1.length(), n = s2.length();
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (s1[i] == s2[j]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  return dp[m][n];
}

} // dynamic_program
} // sakabatou_algorithm
