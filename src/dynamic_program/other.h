#pragma once

#include <vector>

namespace sakabatou_algorithm {
namespace dynamic_program {

int fib_recur(int n);

int fib_iter(int n);

// 四键键盘问题，可以按n次，可选A，Ctrl-A，Ctrl-C，Ctrl-V
int maxA(int n);

// 股票买卖问题，k为限制交易次数
int maxProfit_k_2(const std::vector<int>& prices);

} // dynamic_program
} // sakabatou_algorithm
