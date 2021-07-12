#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <set>

namespace sakabatou_algorithm {
namespace trick {

// compute how many subarray with sum of k
// use trick of sum array
int subarraySum(const std::vector<int>& nums, const int k);

// use trick of difference array
class Difference {
 public:
  Difference(const std::vector<int>& nums);

  void increment(const int i, const int j, const int val);

  std::vector<int> result();

 private:
  std::vector<int> diff_;
};

// return the k-th max num
// use mind of fast sort algorithm
int findKthLargest(const std::vector<int>& nums, const int k);

// divid into sub problem
std::vector<int> diffWaysToCompute(const std::string& s);

std::vector<int> pancakeSort(std::vector<int> cakes);

// caculate basic compute, such as: 3 * (2 - 6 / (3 - 7))
int caculate(const std::string& s);

// 接雨水问题
int trap(std::vector<int>& height);

std::string longestPalindrome(const std::string& s);

// 判断括号有效性
bool isValid(const std::string& s);

bool isRectangleCover(const std::vector<std::vector<int>>& rectangles);

struct PairComp {
  bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    int length1 = p1.second - p1.first - 1;
    int length2 = p2.second - p2.first - 1;
    if ((length1 + 1) / 2 == (length2 + 1) / 2) {
      return p1.first > p2.first;
    } else {
      return length1 < length2;
    }
  }
};

class ExamRoom {
 public:
  ExamRoom(int n);

  int seat();
  void leave(int p);

 private:
  void removeSeg(const std::pair<int, int>& seg);
  void addSeg(const std::pair<int, int>& seg);

 private:
  std::set<std::pair<int, int>, PairComp> segments_;
  std::unordered_map<int, std::pair<int, int>> start_map_;
  std::unordered_map<int, std::pair<int, int>> end_map_;
  int n_;
};

} // trick
} // sakabatou_algorithm
