#pragma once

#include <unordered_set>

namespace sakabatou_algorithm {
namespace dynamic_program {

int coin_change_recur(const std::unordered_set<int>& coin_set, const int amount);

int coin_change_iter(const std::unordered_set<int>& coin_set, const int amount);

} // dynamic_program
} // sakabatou_algorithm
