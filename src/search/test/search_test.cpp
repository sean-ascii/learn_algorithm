#include <gtest/gtest.h>

#include "search/binary_search.h"
#include "search/bfs.h"

// using namespace sakabatou_algorithm::search;

// TEST(SearchTest, binary_search_test) {
//   std::vector<int> nums{1, 2, 4, 5, 6};
//   ASSERT_EQ(1, binary_search(nums, 2));
//   ASSERT_EQ(-1, binary_search(nums, 3));
//   ASSERT_EQ(-1, binary_search(nums, 8));
// }

// TEST(SearchTest, left_bound_search_test) {
//   std::vector<int> nums{1, 2, 2, 2, 3};
//   ASSERT_EQ(1, left_bound(nums, 2));
//   ASSERT_EQ(4, left_bound(nums, 3));
//   ASSERT_EQ(0, left_bound(nums, 0));
//   ASSERT_EQ(5, left_bound(nums, 6));
// }

// TEST(SearchTest, right_bound_search_test) {
//   std::vector<int> nums{1, 2, 2, 2, 3};
//   ASSERT_EQ(3, right_bound(nums, 2));
//   ASSERT_EQ(4, right_bound(nums, 3));
//   ASSERT_EQ(0, right_bound(nums, 0));
//   ASSERT_EQ(5, right_bound(nums, 6));
// }

// TEST(SearchTest, eat_speed_test) {
//   std::vector<int> piles1{3, 6, 7, 11};
//   ASSERT_EQ(4, minEatingSpeed(piles1, 8));
//   std::vector<int> piles2{30, 11, 23, 4, 20};
//   ASSERT_EQ(30, minEatingSpeed(piles2, 5));
// }

// TEST(SearchTest, ship_test) {
//   std::vector<int> weights{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//   ASSERT_EQ(15, shipWithDays(weights, 5));
// }

TEST(SearchTest, bfs_min_depth_test) {
  using namespace sakabatou_algorithm::search::bfs;
  Node* node1 = new Node(3);
  Node* node2 = new Node(9);
  Node* node3 = new Node(20);
  Node* node4 = new Node(15);
  Node* node5 = new Node(7);
  node1->left = node2;
  node1->right = node3;
  node3->left = node4;
  node3->right = node5;
  ASSERT_EQ(2, minDepth(node1));
}

TEST(SearchTest, bfs_open_lock_test) {
  using namespace sakabatou_algorithm::search::bfs;
  std::vector<std::string> deadends1{"0201", "0101", "0102", "1212", "2002"};
  std::string target1 = "0202";
  ASSERT_EQ(6, openLock(deadends1, target1));

  std::vector<std::string> deadends2{"8888"};
  std::string target2 = "0009";
  ASSERT_EQ(1, openLock(deadends2, target2));

  std::vector<std::string> deadends3{"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
  std::string target3 = "8888";
  ASSERT_EQ(-1, openLock(deadends3, target3));
}

TEST(SearchTest, bfs_open_lock_bidirection_test) {
  using namespace sakabatou_algorithm::search::bfs;
  std::vector<std::string> deadends1{"0201", "0101", "0102", "1212", "2002"};
  std::string target1 = "0202";
  ASSERT_EQ(6, openLockBiDirection(deadends1, target1));

  std::vector<std::string> deadends2{"8888"};
  std::string target2 = "0009";
  ASSERT_EQ(1, openLockBiDirection(deadends2, target2));

  std::vector<std::string> deadends3{"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
  std::string target3 = "8888";
  ASSERT_EQ(-1, openLockBiDirection(deadends3, target3));
}

TEST(SearchTest, bfs_slide_puzzle_test) {
  using namespace sakabatou_algorithm::search::bfs;
  std::vector<std::vector<int>> board1{{4, 1, 2}, {5, 0, 3}};
  ASSERT_EQ(5, slidePuzzle(board1));
  std::vector<std::vector<int>> board2{{1, 2, 3}, {5, 4, 0}};
  ASSERT_EQ(-1, slidePuzzle(board2));
}