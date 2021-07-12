#include "dynamic_program/interval_schedule.h"

#include <algorithm>

namespace sakabatou_algorithm {
namespace dynamic_program {

int interval_schedule(std::vector<std::pair<int, int>> intervals) {
  if (intervals.empty()) return 0;
  std::sort(intervals.begin(), intervals.end(), [](const auto& l, const auto& r) {
    return l.second < r.second;
  });

  int end = intervals[0].second;
  int cnt = 1;
  for (int i = 1; i < intervals.size(); ++i) {
    if (intervals[i].first < end) continue;
    end = intervals[i].second;
    cnt++;
  }
  return cnt;
}

bool canJump(const std::vector<int>& nums) {
  int n = nums.size();
  int farthest = 0;
  for (int i = 0; i < n - 1; ++i) {
    farthest = std::max(farthest, i + nums[i]);
    if (farthest <= i) return false;
  }
  return farthest >= n - 1;
}

// use greedy method, O(n)
int minJumpStep(const std::vector<int>& nums) {
  int n = nums.size();
  int end = 0, farthest = 0;
  int cnt = 0;
  for (int i = 0; i < n - 1; ++i) {
    farthest = std::max(farthest, i + nums[i]);
    if (i == end) {
      end = farthest;
      cnt++;
    }
  }
  return cnt;
}

// use dynamic program, O(n^2)
// int minJumpStep(const std::vector<int>& nums) {
//   int n = nums.size();
//   std::vector<int> dp(n, std::numeric_limits<int>::max());
//   dp.back() = 0;

//   for (int i = n - 2; i >= 0; --i) {
//     if (i + nums[i] >= n - 1) {
//       dp[i] = 1;
//       continue;
//     }

//     for (int j = i + 1; j < n - 1 && j <= i + nums[i]; ++j) {
//       dp[i] = std::min(1 + dp[j], dp[i]);
//     }
//   }
//   return dp[0];
// }

} // dynamic_program
} // sakabatou_algorithm
