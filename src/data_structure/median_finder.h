#pragma once

#include <vector>
#include <queue>

namespace sakabatou_algorithm {
namespace data_structure {

class MedianFinder {
 public:
  MedianFinder();

  void addNum(int num);
  double findMedian();

 private:
  std::priority_queue<int> small_;
  std::priority_queue<int, std::vector<int>, std::greater<int>> large_;
};

} // data_structure
} // sakabatou_algorithm
