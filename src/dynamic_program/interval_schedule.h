#pragma once

#include <vector>
#include <utility>

namespace sakabatou_algorithm {
namespace dynamic_program {

// 找到所有interval序列中互不相交的最多序列数
int interval_schedule(std::vector<std::pair<int, int>> intervals);

// 根据数组中每个位置可以跳跃的距离限制，判断能否跳跃到最后一个位置
bool canJump(const std::vector<int>& nums);

// 根据数据中每个位置可以跳跃的距离限制，判断跳跃到最后一个位置所需要的最小的步数
int minJumpStep(const std::vector<int>& nums);

} // dynamic_program
} // sakabatou_algorithm
