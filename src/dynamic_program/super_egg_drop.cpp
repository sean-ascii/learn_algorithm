#include "dynamic_program/super_egg_drop.h"
#include "common/utils.h"

#include <unordered_map>
#include <utility>
#include <limits>

namespace sakabatou_algorithm {
namespace dynamic_program {

int superEggDropDp(
    int k, int n, std::unordered_map<std::pair<int, int>, int, common::util::pair_hash>& memo) {
  if (k == 1) return n;
  if (n == 0) return 0;
  std::pair<int, int> index{k, n};
  if (memo.count(index)) return memo[index];
  int result = std::numeric_limits<int>::max();
  for (int i = 1; i <= n; ++i) {
    result = std::min(result, 1 + std::max(superEggDropDp(k - 1, i - 1, memo),
                                           superEggDropDp(k, n - i, memo)));
  }
  memo[index] = result;
  return memo[index];
}

int superEggDrop(int k, int n) {
  std::unordered_map<std::pair<int, int>, int, common::util::pair_hash> memo;
  return superEggDropDp(k, n, memo);
}

} // dynamic_program
} // sakabatou_algorithm
