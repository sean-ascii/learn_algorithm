#include <gtest/gtest.h>

#include "trick/trick.h"

TEST(TrickTest, subarray_sum_test) {
  using namespace sakabatou_algorithm::trick;
  ASSERT_EQ(2, subarraySum(std::vector<int>{1, 1, 1}, 2));
  ASSERT_EQ(3, subarraySum(std::vector<int>{1, 1, -1}, 1));
}

TEST(TrickTest, diff_array_test) {
  using namespace sakabatou_algorithm::trick;
  std::vector<int> nums{1, 1, 1, 1, 1};
  Difference diff(nums);
  diff.increment(1, 3, 1);
  auto diff_result = diff.result();
  std::vector<int> result{1, 2, 2, 2, 1};
  for (int i = 0; i < result.size(); ++i) {
    ASSERT_EQ(result[i], diff_result[i]);
  }
}

TEST(TrickTest, fast_select_test) {
  using namespace sakabatou_algorithm::trick;
  std::vector<int> nums{4, 1, 6, 3, 2, 5};
  ASSERT_EQ(5, findKthLargest(nums, 2));
  ASSERT_EQ(4, findKthLargest(nums, 3));
}

TEST(TrickTest, diff_way_to_compute_test) {
  using namespace sakabatou_algorithm::trick;
  std::string s = "2*3-4*5";
  std::vector<int> result = diffWaysToCompute(s);
  for (const auto& r : result) {
    std::cout << r << " ";
  }
  std::cout << std::endl;
}

TEST(TrickTest, pancake_sort_test) {
  using namespace sakabatou_algorithm::trick;
  std::vector<int> cakes{3, 2, 4, 1};
  std::vector<int> result = pancakeSort(cakes);
  for (const auto& r : result) {
    std::cout << r << " ";
  }
  std::cout << std::endl;
}

TEST(TrickTest, caculate_test) {
  using namespace sakabatou_algorithm::trick;
  std::string s = "3 * (2 - 6 / (3 - 7))";
  ASSERT_EQ(9, caculate(s));
  s = "3 + 2";
  ASSERT_EQ(5, caculate(s));
}

TEST(TrickTest, trap_test) {
  using namespace sakabatou_algorithm::trick;
  std::vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  ASSERT_EQ(6, trap(height));
}

TEST(TrickTest, longest_palindrome_test) {
  using namespace sakabatou_algorithm::trick;
  ASSERT_EQ("bab", longestPalindrome("babad"));
  ASSERT_EQ("bb", longestPalindrome("cbbd"));
}

TEST(TrickTest, is_valid_test) {
  using namespace sakabatou_algorithm::trick;
  ASSERT_TRUE(isValid("(){}[]"));
  ASSERT_FALSE(isValid("([)]"));
  ASSERT_TRUE(isValid("{()}"));
}

TEST(TrickTest, is_rectangle_cover_test) {
  using namespace sakabatou_algorithm::trick;
  std::vector<std::vector<int>> rects1 = {
    {1, 1, 3, 3}, {3, 1, 4, 2}, {3, 2, 4, 4}, {1, 3, 2, 4}, {2, 3, 3, 4}
  };
  ASSERT_TRUE(isRectangleCover(rects1));
  std::vector<std::vector<int>> rects2 = {
    {1, 1, 3, 3}, {3, 1, 4, 2}, {3, 2, 4, 4}, {1, 3, 2, 4}
  };
  ASSERT_FALSE(isRectangleCover(rects2));
}

TEST(TrickTest, exam_room_test) {
  using namespace sakabatou_algorithm::trick;
  ExamRoom room(10);
  ASSERT_EQ(0, room.seat());
  ASSERT_EQ(9, room.seat());
  ASSERT_EQ(4, room.seat());
  ASSERT_EQ(2, room.seat());
  room.leave(4);
  ASSERT_EQ(5, room.seat());
}