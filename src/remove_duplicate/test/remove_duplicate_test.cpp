#include <gtest/gtest.h>

#include <iostream>

#include "remove_duplicate/remove_duplicate.h"

using namespace sakabatou_algorithm::remove_duplicate;

TEST(RemoveDuplicateTest, remove_duplicate_letter_test) {
  ASSERT_EQ(removeDuplicateLetters("bcabc"), "abc");
  ASSERT_EQ(removeDuplicateLetters("cbacdcbc"), "acdb");
}

TEST(RemoveDuplicateTest, remove_duplicate_in_ordered_array_test) {
  ASSERT_EQ(removeDuplicateInOrderedArray({1, 1, 2}), 2);
  ASSERT_EQ(removeDuplicateInOrderedArray({0, 0, 1, 1, 1, 2, 2, 3, 3, 4}), 5);
}

TEST(RemoveDuplicateTest, remove_item_test) {
  ASSERT_EQ(removeItem({3, 2, 2, 3}, 3), 2);
  ASSERT_EQ(removeItem({0, 1, 2, 2, 3, 0, 4, 2}, 2), 5);
}

TEST(RemoveDuplicateTest, move_zeroes_test) {
  std::vector<int> nums{0, 1, 4, 0, 2}, result{1, 4, 2, 0, 0};
  moveZeroes(nums);
  ASSERT_EQ(nums, result);
}

#include <vector>
#include <unordered_map>

TEST(sssss, ss) {
    int N = 1000, m = 5;
    std::vector<int> price{800, 400, 300, 400, 500};
    std::vector<int> val{1600, 2000, 1500, 1200, 1000};
    std::vector<int> depend{0, 1, 1, 0, 0};
    std::unordered_map<int, std::vector<int>> app_list;
    for (int i = 0; i < m; ++i) {
        if (depend[i] != 0) {
            app_list[depend[i] - 1].push_back(i);
        }
    }
    std::vector<std::vector<int>> prim_vals;
    std::vector<std::vector<int>> prim_prices;
    for (int i = 0; i < m; ++i) {
        if (depend[i] != 0) continue;
        prim_vals.push_back(std::vector<int>{0, 0, 0, 0});
        prim_prices.push_back(std::vector<int>{0, 0, 0, 0});
        prim_prices.back().at(0) = price[i];
        prim_vals.back().at(0) = val[i];

        if (!app_list.count(i)) {
            continue;
        }
        if (app_list[i].size() == 1) {
            prim_prices[i][1] = price[app_list[i][0]] + price[i];
            prim_vals[i][1] = val[app_list[i][0]] + val[i];
        } else if (app_list[i].size() == 2) {
            prim_prices[i][1] = price[app_list[i][0]] + price[i];
            prim_vals[i][1] = val[app_list[i][0]] + val[i];
            prim_prices[i][2] = price[app_list[i][1]] + price[i];
            prim_vals[i][2] = val[app_list[i][1]] + val[i];
            prim_prices[i][3] = price[app_list[i][0]] + price[app_list[i][1]] + price[i];
            prim_vals[i][3] = val[app_list[i][0]] + val[app_list[i][1]] + val[i];
        }
    }
    std::vector<std::vector<int>> dp(prim_vals.size() + 1, std::vector<int>(N + 1, 0));
    for (int i = 1; i <= prim_vals.size(); ++i) {
        for (int j = 10; j <= N; j += 10) {
            dp[i][j] = dp[i - 1][j];
            for (int k = 0; k < 4; ++k) {
                int price = prim_prices[i - 1][k];
                int val = prim_vals[i - 1][k];
                if (j - price >= 0) {
                    dp[i][j] = std::max(dp[i - 1][j - price] + val, dp[i][j]);
                }
            }
        }
    }
    std::cout << dp[prim_vals.size()][N];
}
