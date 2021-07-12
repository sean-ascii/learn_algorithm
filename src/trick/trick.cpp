#include "trick/trick.h"

#include <utility>
#include <algorithm>
#include <stack>
#include <unordered_set>
#include <sstream>

#include <iostream>
#include "common/utils.h"

namespace sakabatou_algorithm {
namespace trick {

int subarraySum(const std::vector<int>& nums, const int k) {
  int sum = 0;
  std::unordered_map<int, int> sum_cnt;
  sum_cnt[sum]++;

  int cnt = 0;
  for (int i = 0; i < nums.size(); ++i) {
    sum += nums[i];
    if (sum_cnt.count(sum - k)) {
      cnt += sum_cnt[sum - k];
    }
    sum_cnt[sum]++;
  }
  return cnt;
}

Difference::Difference(const std::vector<int>& nums) {
  if (nums.empty()) return;

  diff_.resize(nums.size());
  diff_[0] = nums[0];
  for (int i = 1; i < nums.size(); ++i) {
    diff_[i] = nums[i] - nums[i - 1];
  }
}

void Difference::increment(const int i, const int j, const int val) {
  if (i >= diff_.size()) return;

  diff_[i] += val;

  if (j + 1 >= diff_.size()) return;

  diff_[j + 1] -= val;
}

std::vector<int> Difference::result() {
  if (diff_.empty()) return {};

  std::vector<int> result;
  result.resize(diff_.size());
  result[0] = diff_[0];
  for (int i = 1; i < diff_.size(); ++i) {
    result[i] = diff_[i] + result[i - 1];
  }
  return result;
}

int partition(std::vector<int>& nums, const int lo, const int hi) {
  if (lo == hi) return lo;

  int p = nums[lo];
  int i = lo, j = hi + 1;
  while (true) {
    while (nums[++i] > p) {
      if (i == hi) break;
    }
    while (nums[--j] < p) {
      if (j == lo) break;
    }
    if (i >= j) break;
    std::swap(nums[i], nums[j]);
  }
  std::swap(nums[lo], nums[j]);

  return j;
}

int findKthLargest(const std::vector<int>& nums, const int k) {
  if (nums.size() < k) return -1;

  int target_index = k - 1;
  int lo = 0, hi = nums.size() - 1;
  std::vector<int> temp_nums = nums;
  while (lo <= hi) {
    int p = partition(temp_nums, lo, hi);
    if (p == target_index) {
      return temp_nums[p];
    } else if (p < k) {
      lo = p + 1;
    } else {
      hi = p - 1;
    }
  }
  return -1;
}

std::vector<int> diffWaysToCompute(const std::string& s) {
  std::vector<int> result;

  for (int i = 0; i < s.size(); ++i) {
    char c = s[i];
    if (c == '+' || c == '-' || c == '*') {
      std::vector<int> left = diffWaysToCompute(s.substr(0, i));
      std::vector<int> right = diffWaysToCompute(s.substr(i + 1));
      for (const int& l : left) {
        for (const int& r : right) {
          if (c == '+') {
            result.push_back(l + r);
          } else if (c == '-') {
            result.push_back(l - r);
          } else {
            result.push_back(l * r);
          }
        }
      }
    }
  }

  if (result.empty()) {
    result.push_back(std::stoi(s));
  }

  return result;
}

void pancakeSortHelper(std::vector<int>& cakes, const int n, std::vector<int>& result) {
  if (n == 1) return;

  auto iter = std::max_element(cakes.begin(), cakes.begin() + n);
  int max_index = std::distance(cakes.begin(), iter);
  if (max_index != n - 1) {
    if (max_index != 0) {
      std::reverse(cakes.begin(), iter + 1);
      result.push_back(max_index + 1);
    }
    std::reverse(cakes.begin(), cakes.begin() + n);
    result.push_back(n);
  }
  pancakeSortHelper(cakes, n - 1, result);
}

std::vector<int> pancakeSort(std::vector<int> cakes) {
  std::vector<int> result;
  pancakeSortHelper(cakes, cakes.size(), result);
  return result;
}

int caculate(const std::string& s, int& idx) {
  std::stack<int> nums;
  char sign = '+';
  int num = 0;

  while (idx < s.size()) {
    char c = s[idx++];

    if (c == ' ') continue;

    if (std::isdigit(c)) {
      num += num * 10 + (c - '0');
    }

    if (c == '(') {
      num = caculate(s, idx);
    }

    if (!std::isdigit(c) || idx == s.size()) {
      switch (sign) {
        case '+':
          {
            nums.push(num);
            break;
          }
        case '-':
          {
            nums.push(-num);
            break;
          }
        case '*':
          {
            int pre = nums.top();
            nums.pop();
            nums.push(pre * num);
            break;
          }
        case '/':
          {
            int pre = nums.top();
            nums.pop();
            nums.push(pre / num);
            break;
          }
      }
      sign = c;
      num = 0;
    }

    if (c == ')') break;
  }

  int sum = 0;
  while (!nums.empty()) {
    sum += nums.top();
    nums.pop();
  }
  return sum;
}

int caculate(const std::string& s) {
  int start_idx = 0;
  return caculate(s, start_idx);
}

int trap(std::vector<int>& height) {
  if (height.empty()) return 0;

  int result = 0;
  int left = 0, right = height.size() - 1;
  int left_max = -1, right_max = -1;
  while (left <= right) {
    left_max = std::max(left_max, height[left]);
    right_max = std::max(right_max, height[right]);

    if (left_max < right_max) {
      result += left_max - height[left];
      left++;
    } else {
      result += right_max - height[right];
      right--;
    }
  }
  return result;
}

std::string longestPalindromeHelper(const std::string& s, int left, int right) {
  while (left >= 0 && right < s.size() && s[left] == s[right]) {
    left--;
    right++;
  }

  return s.substr(left + 1, right - left - 1);
}

std::string longestPalindrome(const std::string& s) {
  std::string result;

  for (int i = 0; i < s.size(); ++i) {
    std::string s1 = longestPalindromeHelper(s, i, i);
    std::string s2 = longestPalindromeHelper(s, i, i + 1);
    if (s1.size() > result.size()) result = s1;
    if (s2.size() > result.size()) result = s2;
  }

  return result;
}

bool isValid(const std::string& s) {
  std::stack<char> left;
  for (const auto& c : s) {
    if (c == '(' || c == '[' || c == '{') {
      left.push(c);
    }

    if (c == ')') {
      if (left.empty() || left.top() != '(')
        return false;
      else
        left.pop();
    } else if (c == ']') {
      if (left.empty() || left.top() != '[')
        return false;
      else
        left.pop();
    } else if (c == '}') {
      if (left.empty() || left.top() != '{')
        return false;
      else
        left.pop();
    }
  }
  return left.empty();
}

bool isRectangleCover(const std::vector<std::vector<int>>& rectangles) {
  if (rectangles.empty()) return false;

  int x_min = std::numeric_limits<int>::max();
  int y_min = std::numeric_limits<int>::max();
  int x_max = std::numeric_limits<int>::lowest();
  int y_max = std::numeric_limits<int>::lowest();
  int total_area = 0;
  std::unordered_set<std::pair<int, int>, common::util::pair_hash> vertexs;

  for (const auto& rect : rectangles) {
    total_area += (rect[2] - rect[0]) * (rect[3] - rect[1]);
    x_min = std::min({x_min, rect[0], rect[2]});
    x_max = std::max({x_max, rect[0], rect[2]});
    y_min = std::min({y_min, rect[1], rect[3]});
    y_max = std::max({y_max, rect[1], rect[3]});

    std::pair<int, int> p1{rect[0], rect[1]};
    std::pair<int, int> p2{rect[2], rect[1]};
    std::pair<int, int> p3{rect[2], rect[3]};
    std::pair<int, int> p4{rect[0], rect[3]};

    if (vertexs.count(p1)) vertexs.erase(p1); else vertexs.insert(p1);
    if (vertexs.count(p2)) vertexs.erase(p2); else vertexs.insert(p2);
    if (vertexs.count(p3)) vertexs.erase(p3); else vertexs.insert(p3);
    if (vertexs.count(p4)) vertexs.erase(p4); else vertexs.insert(p4);
  }

  if (total_area != (x_max - x_min) * (y_max - y_min)) return false;
  if (vertexs.size() != 4) return false;
  std::pair<int, int> bottom_left{x_min, y_min};
  std::pair<int, int> bottom_right{x_max, y_min};
  std::pair<int, int> upper_left{x_min, y_max};
  std::pair<int, int> upper_right{x_max, y_max};
  if (!vertexs.count(bottom_left)) return false;
  if (!vertexs.count(bottom_right)) return false;
  if (!vertexs.count(upper_left)) return false;
  if (!vertexs.count(upper_right)) return false;

  return true;
}

ExamRoom::ExamRoom(int n) : n_(n) {
  std::pair<int, int> seg{-1, n_};
  segments_.insert(seg);
  start_map_.emplace(seg.first, seg);
  end_map_.emplace(seg.second, seg);
}

void ExamRoom::removeSeg(const std::pair<int, int>& seg) {
  start_map_.erase(seg.first);
  end_map_.erase(seg.second);
  segments_.erase(seg);
}

void ExamRoom::addSeg(const std::pair<int, int>& seg) {
  start_map_.emplace(seg.first, seg);
  end_map_.emplace(seg.second, seg);
  segments_.insert(seg);
}

int ExamRoom::seat() {
  auto longest_seg = *segments_.rbegin();
  if (longest_seg.second - longest_seg.first - 1 < 1) return -1;

  int seat;
  if (longest_seg.first == -1) {
    seat = 0;
  } else if (longest_seg.second == n_) {
    seat = n_ - 1;
  } else {
    seat = (longest_seg.second - longest_seg.first) / 2 + longest_seg.first;
  }
  std::pair<int, int> left{longest_seg.first, seat};
  std::pair<int, int> right{seat, longest_seg.second};
  removeSeg(longest_seg);
  addSeg(left);
  addSeg(right);
  return seat;
}

void ExamRoom::leave(int p) {
  if (!start_map_.count(p)) return;
  auto left = end_map_[p];
  auto right = start_map_[p];
  std::pair<int, int> new_seg{left.first, right.second};
  removeSeg(left);
  removeSeg(right);
  addSeg(new_seg);
}

} // trick
} // sakabatou_algorithm
