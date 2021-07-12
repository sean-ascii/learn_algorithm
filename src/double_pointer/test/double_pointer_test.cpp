#include <gtest/gtest.h>

#include "double_pointer/slow_fast_pointer.h"
#include "double_pointer/left_right_pointer.h"


TEST(DoublePointerTest, slow_fast_pointer_test) {
  using namespace sakabatou_algorithm::double_pointer::slow_fast_point;

  Node* node1 = new Node(1);
  Node* node2 = new Node(2);
  Node* node3 = new Node(3);
  Node* node4 = new Node(4);
  Node* node5 = new Node(5);
  Node* node6 = new Node(6);

  node1->next = node2;
  node2->next = node3;
  node3->next = node4;
  node4->next = node5;
  node5->next = node6;

  ASSERT_FALSE(hasCycle(node1));

  node1->next = node2;
  node2->next = node3;
  node3->next = node4;
  node4->next = node5;
  node5->next = node6;
  node6->next = node4;

  ASSERT_TRUE(hasCycle(node1));

  ASSERT_EQ(4, detectCycle(node1));

  node6->next = nullptr;

  ASSERT_EQ(node4, findMedian(node1));

  ASSERT_EQ(node4, lastKth(node1, 3));
}

TEST(DoublePointerTest, left_right_pointer_test1) {
  using namespace sakabatou_algorithm::double_pointer::left_right_pointer;
  std::vector<int> nums{2, 7 , 11, 15};
  ASSERT_EQ(std::make_pair(1, 2), findSum(nums, 9));
  ASSERT_EQ(std::make_pair(-1, -1), findSum(nums, 10));
}

TEST(DoublePointerTest, left_right_pointer_test2) {
  using namespace sakabatou_algorithm::double_pointer::left_right_pointer;
  std::vector<int> nums{2, 7 , 11, 15};
  std::vector<int> result{15, 11 , 7, 2};
  reverse(nums);
  ASSERT_EQ(nums, result);
}
