#pragma once

#include <vector>
#include <string>

namespace sakabatou_algorithm {
namespace search {

int binary_search(std::vector<int> nums, int target);

int left_bound(std::vector<int> nums, int target);

int right_bound(std::vector<int> nums, int target);

int minEatingSpeed(const std::vector<int>& piles, int H);

int shipWithDays(const std::vector<int>& weights, int D);

} // search
} // sakabatou_algorithm
