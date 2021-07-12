#include <gtest/gtest.h>

#include "sort/sort.h"

#include <iostream>

TEST(SortTest, fast_sort_test) {
  using namespace sakabatou_algorithm::sort;
  std::vector<int> nums{4, 1, 6, 3, 2, 5};
  fastSort(nums);
  for (const auto& n : nums) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}

TEST(SortTest, heap_sort_test) {
  using namespace sakabatou_algorithm::sort;
  std::vector<int> nums{4, 1, 6, 3, 2, 5};
  heapSort(nums);
  for (const auto& n : nums) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}

TEST(SortTest, merge_sort_top_down_test) {
  using namespace sakabatou_algorithm::sort;
  std::vector<int> nums{4, 1, 6, 3, 2, 5};
  mergeSortTopDown(nums);
  for (const auto& n : nums) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}

TEST(SortTest, merge_sort_bottom_up_test) {
  using namespace sakabatou_algorithm::sort;
  std::vector<int> nums{4, 1, 6, 3, 2, 5};
  mergeSortBottomUp(nums);
  for (const auto& n : nums) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}
