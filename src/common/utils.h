#pragma once

#include <utility>
#include <functional>
#include <vector>

namespace sakabatou_algorithm {
namespace common {
namespace util {

struct pair_hash {
  template<typename T1, typename T2>
  std::size_t operator()(const std::pair<T1, T2>& p) const {
    std::size_t seed = 0;
    seed ^= std::hash<T1>()(p.first) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    seed ^= std::hash<T1>()(p.second) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    return seed;
  }
};

struct vector_hash {
  std::size_t operator()(const std::vector<int>& v) const {
    std::hash<int> hasher;
    std::size_t seed = 0;
    for (int i : v) {
      seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }
    return seed;
  }
};

} // util
} // common
} // sakabatou_algorithm
