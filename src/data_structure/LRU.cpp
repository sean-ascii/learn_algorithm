#include "data_structure/LRU.h"

#include <iterator>

namespace sakabatou_algorithm {
namespace data_structure {
namespace LRU {

LRUCache::LRUCache(int capacity)
    : capacity_(capacity) {}

int LRUCache::get(int key) {
  if (!map_.count(key)) {
    return -1;
  }

  makeRecently(key);
  return map_[key]->value;
}

void LRUCache::put(int key, int value) {
  if (map_.count(key)) {
    deleteKey(key);
  }

  addRecently(key, value);
}

void LRUCache::makeRecently(int key) {
  cache_.splice(cache_.begin(), cache_, map_[key]);
}

void LRUCache::addRecently(int key, int value) {
  Node* node = new Node(key, value);
  if (cache_.size() == capacity_) {
    removeLastRecently();
  }
  cache_.emplace_front(key, value);
  map_[key] = cache_.begin();
}

void LRUCache::deleteKey(int key) {
  cache_.erase(map_[key]);
  map_.erase(key);
}

void LRUCache::removeLastRecently() {
  if (cache_.size() == 0) return;
  map_.erase(cache_.back().key);
  cache_.pop_back();
}

} // LRU
} // data_structure
} // sakabatou_algorithm
