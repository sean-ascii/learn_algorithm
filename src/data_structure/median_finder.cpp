#include "data_structure/median_finder.h"

namespace sakabatou_algorithm {
namespace data_structure {

MedianFinder::MedianFinder() {}

void MedianFinder::addNum(int num) {
  if (small_.size() >= large_.size()) {
    small_.push(num);
    large_.push(small_.top());
    small_.pop();
  } else {
    large_.push(num);
    small_.push(large_.top());
    large_.pop();
  }
}

double MedianFinder::findMedian() {
  if (small_.size() < large_.size()) {
    return large_.top();
  } else if (small_.size() > large_.size()) {
    return small_.top();
  } else {
    return (large_.top() + small_.top()) / 2.0;
  }
}

} // data_structure
} // sakabatou_algorithm