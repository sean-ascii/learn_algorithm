#pragma once

#include <vector>

namespace sakabatou_algorithm {
namespace dynamic_program {

// max val with limit capacity
int zero_one_knapsack(const std::vector<int>& wt, const std::vector<int>& val, const int capacity);

// partition into two parts with same sum
bool can_partition(const std::vector<int>& nums);

// coin change(every coin with unlimit numbers), how many ways
int coin_change_1(const int amount, const std::vector<int>& coins);

// coin change(every coin with unlimit numbers), which has the least coin number
int coin_change_2(const int amount, const std::vector<int>& coins);

} // dynamic_program
} // sakabatou_algorithm
