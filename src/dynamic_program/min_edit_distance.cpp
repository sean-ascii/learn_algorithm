#include "dynamic_program/min_edit_distance.h"

#include <vector>
#include <algorithm>

namespace sakabatou_algorithm {
namespace dynamic_program {

int min_edit_distance(std::string s1, std::string s2) {
  int m = s1.length(), n = s2.length();
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
  // base case
  for (int i = 1; i <= m; ++i) {
    dp[i][0] = i;
  }
  for (int i = 1; i <= n; ++i) {
    dp[0][i] = i;
  }
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = std::min({dp[i - 1][j - 1] + 1, // replace
                             dp[i - 1][j] + 1, // delete
                             dp[i][j - 1] + 1}); // insert
      }
    }
  }
  return dp[m][n];
}

} // dynamic_program
} // sakabatou_algorithm
