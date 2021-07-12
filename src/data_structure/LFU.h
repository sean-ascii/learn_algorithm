#pragma once

#include <unordered_map>
#include <list>

namespace sakabatou_algorithm {
namespace data_structure {
namespace LFU {

class LFUCache {
 public:
  LFUCache(int capacity);
  int get(int key);
  void put(int key, int val);

 private:
  void increaseFreq(int key);
  void removeMinFreqKey();

 private:
  int capacity_;
  std::unordered_map<int, int> key_to_val_;
  std::unordered_map<int, int> key_to_freq_;
  std::unordered_map<int, std::list<int>> freq_to_keys_;
  std::unordered_map<int, std::list<int>::iterator> key_to_freq_list_iter_;
  int min_freq_;
};

} // LFU
} // data_structure
} // sakabatou_algorithm
