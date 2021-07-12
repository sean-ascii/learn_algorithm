#include <gtest/gtest.h>

#include "dynamic_program/coin_change.h"
#include "dynamic_program/other.h"
#include "dynamic_program/knapsack.h"
#include "dynamic_program/max_sub_array_sum.h"
#include "dynamic_program/min_edit_distance.h"
#include "dynamic_program/max_coins.h"
#include "dynamic_program/longest_common_subsquence.h"
#include "dynamic_program/regex.h"
#include "dynamic_program/kmp_match.h"
#include "dynamic_program/interval_schedule.h"
#include "dynamic_program/house_robber.h"
#include "dynamic_program/longest_increasing_subsquence.h"
#include "dynamic_program/super_egg_drop.h"
#include "dynamic_program/game.h"

using namespace sakabatou_algorithm::dynamic_program;

TEST(DynamicProgramTest, zero_one_knapsack_test) {
  std::vector<int> weight{2, 1, 3};
  std::vector<int> value{4, 2, 3};
  ASSERT_EQ(6, zero_one_knapsack(weight, value, 4));
}

TEST(DynamicProgramTest, can_partition_test) {
  std::vector<int> nums1{1, 2, 3, 5};
  ASSERT_FALSE(can_partition(nums1));
  std::vector<int> nums2{1, 5, 11, 5};
  ASSERT_TRUE(can_partition(nums2));
}

TEST(DynamicProgramTest, coin_change_1_test) {
  std::vector<int> coins{1, 2, 5};
  int amount = 5;
  ASSERT_EQ(4, coin_change_1(amount, coins));
}

TEST(DynamicProgramTest, coin_change_2_test) {
  std::vector<int> coins{1, 2, 5};
  int amount = 11;
  ASSERT_EQ(3, coin_change_2(amount, coins));
}

TEST(DynamicProgramTest, min_edit_distance_test) {
  std::string s1 = "horse", s2 = "ros";
  ASSERT_EQ(3, min_edit_distance(s1, s2));
  s1 = "intention";
  s2 = "execution";
  ASSERT_EQ(5, min_edit_distance(s1, s2));
}

TEST(DynamicProgramTest, max_coins_test) {
  std::vector<int> nums{3, 1, 5, 8};
  ASSERT_EQ(167, max_coins(nums));
}

TEST(DynamicProgramTest, longest_common_subsquence_test) {
  std::string s1 = "abcde", s2 = "ace";
  ASSERT_EQ(3, longest_common_subsquence(s1, s2));
}

TEST(DynamicProgramTest, regex_test) {
  std::string s = "aa", p = "a*";
  ASSERT_TRUE(is_match(s, p));
  s = "ab", p = ".*";
  ASSERT_TRUE(is_match(s, p));
}

TEST(DynamicProgramTest, kmp_match_test) {
  std::string pat = "aaab", text1 = "aaacaaab", text2 = "aaaaaab";
  KMP kmp(pat);
  ASSERT_EQ(4, kmp.search(text1));
  ASSERT_EQ(3, kmp.search(text2));
}

TEST(DynamicProgramTest, interval_schedule_test) {
  std::vector<std::pair<int, int>> intervals{{2, 5}, {1, 6}, {3, 7}, {5, 8}, {10, 12}, {7, 13}};
  ASSERT_EQ(3, interval_schedule(intervals));
}

TEST(DynamicProgramTest, house_robber_test) {
  std::vector<int> nums{1, 2, 3, 1};
  ASSERT_EQ(4, rob_1_recur(nums));
  ASSERT_EQ(4, rob_1_dp(nums));

  std::vector<int> nums2{2, 3, 2};
  ASSERT_EQ(4, rob_1_dp(nums2));
  ASSERT_EQ(3, rob_2_dp(nums2));
}

TEST(DynamicProgramTest, max_envelopes_test) {
  std::vector<std::pair<int, int>> envelopes1{
    {5, 4}, {6, 4}, {6, 7}, {2, 3}
  };
  ASSERT_EQ(3, maxEnvelopes(envelopes1));
  std::vector<std::pair<int, int>> envelopes2{
    {1, 8}, {2, 3}, {5, 4}, {5, 2}, {6, 7}, {6, 4}
  };
  ASSERT_EQ(3, maxEnvelopes(envelopes2));
}

TEST(DynamicProgramTest, max_sub_array_sum_test) {
  ASSERT_EQ(6, max_sub_array_sum(std::vector<int>{-2, 1, -3, 4, -1, 2, 1, -5, 4}));
}

TEST(DynamicProgramTest, min_jump_step_test) {
  std::vector<int> nums{2, 3, 1, 1, 4};
  ASSERT_EQ(2, minJumpStep(nums));
}

TEST(DynamicProgramTest, super_egg_drop_test) {
  ASSERT_EQ(14, superEggDrop(2, 100));
  ASSERT_EQ(100, superEggDrop(1, 100));
}

TEST(DynamicProgramTest, game_test) {
  ASSERT_EQ(7, stoneGame(std::vector<int>{3, 9, 1, 2}));
  ASSERT_EQ(-96, stoneGame(std::vector<int>{1, 100, 3}));
}

TEST(DynamicProgramTest, max_a_test) {
  ASSERT_EQ(3, maxA(3));
  ASSERT_EQ(9, maxA(7));
}

TEST(DynamicProgramTest, max_profit_k_2_test) {
  ASSERT_EQ(2, maxProfit_k_2(std::vector<int>{2, 4, 1}));
  ASSERT_EQ(7, maxProfit_k_2(std::vector<int>{3, 2, 6, 5, 0, 3}));
}