#pragma once

#include <unordered_map>
#include <list>

namespace sakabatou_algorithm {
namespace data_structure {
namespace LRU {

struct Node {
  Node(int key, int value) : key(key), value(value) {}
  int key, value;
};

class LRUCache {
 public:
  LRUCache(int capacity);

  void put(int key, int value);
  int get(int key);

 private:
  void makeRecently(int key);
  void addRecently(int key, int value);
  void deleteKey(int key);
  void removeLastRecently();

 private:
  int capacity_;
  std::unordered_map<int, std::list<Node>::iterator> map_;
  std::list<Node> cache_;
};

} // LRU
} // data_structure
} // sakabatou_algorithm
