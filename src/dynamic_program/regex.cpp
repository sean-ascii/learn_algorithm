#include "dynamic_program/regex.h"

#include "common/utils.h"

#include <vector>
#include <unordered_map>

namespace sakabatou_algorithm {
namespace dynamic_program {

bool is_match_helper(const std::string& text, const std::string& pattern,
                     int i, int j,
                     std::unordered_map<std::pair<int, int>, bool, common::util::pair_hash>& dp) {
  std::pair<int, int> index{i, j};
  if (dp.count(index)) return dp[index];
  if (j == pattern.size()) return i == text.size();
  bool first_match = (i != text.size()) && (pattern[j] == '.' || pattern[j] == text[i]);
  bool result;
  if (j < pattern.size() - 1 && pattern[j + 1] == '*') {
    result = is_match_helper(text, pattern, i, j + 2, dp) ||
             (first_match && is_match_helper(text, pattern, i + 1, j, dp));
  } else {
    result = first_match && is_match_helper(text, pattern, i + 1, j + 1, dp);
  }
  dp[index] = result;
  return result;
}

bool is_match(const std::string& text, const std::string& pattern) {
  std::unordered_map<std::pair<int, int>, bool, common::util::pair_hash> dp;
  return is_match_helper(text, pattern, 0, 0, dp);
}

} // dynamic_program
} // sakabatou_algorithm
