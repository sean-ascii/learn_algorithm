#include "data_structure/random_set.h"

#include <iostream>
#include <cstdlib>

namespace sakabatou_algorithm {
namespace data_structure {

bool RandomizedSet::insert(int val) {
  if (map_.count(val)) return false;

  map_[val] = cache_.size();
  cache_.push_back(val);
  return true;
}

bool RandomizedSet::remove(int val) {
  if (!map_.count(val)) return false;

  int index = map_[val];
  if (index != cache_.size() - 1) {
    cache_[index] = cache_.back();
    map_[cache_.back()] = index;
  }
  cache_.pop_back();
  map_.erase(val);
  return true;
}

int RandomizedSet::getRandom() {
  return cache_[std::rand() % cache_.size()];
}

RandomizedSetWithBlacklist::RandomizedSetWithBlacklist(
    const int N, const std::vector<int>& blacklist) {
  size_ = N - blacklist.size();

  for (const auto& i : blacklist) {
    blacklist_map_[i] = 0;
  }

  int last = N - 1;
  for (const auto& i : blacklist) {
    if (i >= size_) continue;

    while (blacklist_map_.count(last)) {
      last--;
    }

    blacklist_map_[i] = last;
  }
}

int RandomizedSetWithBlacklist::pick() {
  int rand_index = std::rand() % size_;
  if (blacklist_map_.count(rand_index)) {
    return blacklist_map_[rand_index];
  } else {
    return rand_index;
  }
}

} // data_structure
} // sakabatou_algorithm
