#include "data_structure/LFU.h"

#include <iostream>

namespace sakabatou_algorithm {
namespace data_structure {
namespace LFU {

LFUCache::LFUCache(int capacity)
    : capacity_(capacity), min_freq_(0) {}

int LFUCache::get(int key) {
  if (!key_to_val_.count(key)) {
    return -1;
  }

  increaseFreq(key);
  return key_to_val_[key];
}

void LFUCache::put(int key, int val) {
  if (capacity_ <= 0) return;

  if (key_to_val_.count(key)) {
    key_to_val_[key] = val;
    increaseFreq(key);
    return;
  }

  if (capacity_ <= key_to_val_.size()) {
    removeMinFreqKey();
  }

  key_to_val_[key] =  val;
  key_to_freq_[key] = 1;
  if (!freq_to_keys_.count(1)) {
    freq_to_keys_[1] = {};
  }
  key_to_freq_list_iter_[key] = freq_to_keys_[1].insert(freq_to_keys_[1].end(), key);
  min_freq_ = 1;
}

void LFUCache::increaseFreq(int key) {
  int freq = key_to_freq_[key];
  key_to_freq_[key] = freq + 1;
  auto iter = key_to_freq_list_iter_[key];
  freq_to_keys_[freq].erase(iter);
  if (freq_to_keys_[freq].empty()) {
    freq_to_keys_.erase(freq);
    if (freq == min_freq_)
      min_freq_++;
  }
  if (!freq_to_keys_.count(freq + 1)) {
    freq_to_keys_[freq + 1] = {};
  }
  key_to_freq_list_iter_[key] = freq_to_keys_[freq + 1].insert(freq_to_keys_[freq + 1].end(), key);
}

void LFUCache::removeMinFreqKey() {
  auto& keys = freq_to_keys_[min_freq_];
  int key = keys.front();
  keys.erase(keys.begin());
  if (keys.empty()) {
    freq_to_keys_.erase(min_freq_);
  }
  key_to_val_.erase(key);
  key_to_freq_.erase(key);
  key_to_freq_list_iter_.erase(key);
}

} // LFU
} // data_structure
} // sakabatou_algorithm
