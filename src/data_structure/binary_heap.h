#pragma once

#include <vector>

namespace sakabatou_algorithm {
namespace data_structure {

class PriorityQueue {
 public:
  PriorityQueue();

  int top();
  int pop();
  void push(int item);

 private:
  void swim(int i);
  void sink(int i);

  void exch(int i, int j);
  int parent(int i);
  int left(int i);
  int right(int i);

 private:
  std::vector<int> q_;
  int cnt_;

};

// https://github.com/kartikkukreja/blog-codes/blob/master/src/Indexed%20Min%20Priority%20Queue.cpp
template <typename T>
class IndexMinPQ {
 public:
  IndexMinPQ(const int max_size)
      : max_size_(max_size), size_(0),
        index_(max_size + 1, -1), value_(max_size + 1), heap_(max_size + 1) {}

  bool empty() { return size_ == 0; }
  int size() { return size_; }
  bool contains(const int i) { return index_[i] != -1; }

  int minIndex() {
    return heap_[1];
  }

  T minValue() {
    return value_[heap_[1]];
  }

  int deleteMin() {
    int min_index = heap_[1];
    swap(1, size_--);
    sink(1);
    index_[min_index] = -1;
    return min_index;
  }

  void insert(const int i, const T value) {
    size_++;
    index_[i] = size_;
    heap_[size_] = i;
    value_[i] = value;
    swim(size_);
  }

  void changeValue(const int i, const T new_value) {
    value_[i] = new_value;
    swim(index_[i]);
    sink(index_[i]);
  }

 private:
  void swap(const int i, const int j) {
    std::swap(heap_[i], heap_[j]);
    index_[heap_[i]] = i;
    index_[heap_[j]] = j;
  }

  void swim(int k) {
    while (k > 1 && value_[heap_[k]] < value_[heap_[parent(k)]]) {
      swap(k, parent(k));
      k = parent(k);
    }
  }

  void sink(int k) {
    while (left(k) <= size_) {
      int j = left(k);
      if (right(k) <= size_ && value_[heap_[right(k)]] < value_[heap_[left(k)]]) {
        j++;
      }
      if (value_[heap_[j]] >= value_[heap_[k]]) break;

      swap(k, j);
      k = j;
    }
  }

  int left(int k) { return k * 2; }
  int right(int k) { return k * 2 + 1; }
  int parent(int k) { return k / 2; }

 private:
  int max_size_;
  int size_;
  std::vector<int> index_; // index -> heap index
  std::vector<int> heap_; // heap index -> index
  std::vector<T> value_; // index -> value
};

} // data_structure
} // sakabatou_algorithm
