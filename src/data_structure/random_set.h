#pragma once

#include <unordered_map>
#include <vector>

namespace sakabatou_algorithm {
namespace data_structure {

class RandomizedSet {
 public:
  bool insert(int val);
  bool remove(int val);
  int getRandom();

 private:
  std::unordered_map<int, int> map_;
  std::vector<int> cache_;
};

class RandomizedSetWithBlacklist {
 public:
  RandomizedSetWithBlacklist(const int N, const std::vector<int>& blacklist);
  int pick();

 private:
  int size_;
  std::unordered_map<int, int> blacklist_map_;
};

} // data_structure
} // sakabatou_algorithm
