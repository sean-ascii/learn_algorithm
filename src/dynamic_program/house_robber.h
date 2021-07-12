#pragma once

#include <vector>

namespace sakabatou_algorithm {
namespace dynamic_program {

// 打劫数组中的房子，不能打劫相邻房子，求最多能打劫到多少金额
int rob_1_recur(const std::vector<int>& nums);
int rob_1_dp(const std::vector<int>& nums);

// 打劫数组中的房子，不能打劫相邻房子，但是所有房子是一个环，即首尾房子相邻，求最多能打劫到多少金额
int rob_2_dp(const std::vector<int>& nums);

} // dynamic_program
} // sakabatou_algorithm
