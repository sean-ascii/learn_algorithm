#include "data_structure/binary_heap.h"


namespace sakabatou_algorithm {
namespace data_structure {

PriorityQueue::PriorityQueue() {
  q_.resize(1);
  cnt_ = 0;
}

int PriorityQueue::top() {
  if (cnt_ < 1) return -1;

  return q_[1];
}

int PriorityQueue::pop() {
  if (cnt_ < 1) return -1;

 int max = q_[1];
 exch(1, cnt_);
 q_.pop_back();
 cnt_--;
 sink(1);
 return max;
}

void PriorityQueue::push(int item) {
  q_.push_back(item);
  cnt_++;
  swim(cnt_);
}

void PriorityQueue::swim(int i) {
  while (i > 1 && q_[parent(i)] < q_[i]) {
    exch(parent(i) , i);
    i = parent(i);
  }
}

void PriorityQueue::sink(int i) {
  while (left(i) <= cnt_) {
    int max_child_index = (right(i) <= cnt_ && q_[right(i)] > q_[left(i)]) ? right(i) : left(i);
    if (q_[i] >= q_[max_child_index]) break;

    exch(max_child_index, i);
    i = max_child_index;
  }
}

void PriorityQueue::exch(int i, int j) {
  int temp = q_[i];
  q_[i] = q_[j];
  q_[j] = temp;
}

int PriorityQueue::parent(int i) {
  return i / 2;
}

int PriorityQueue::left(int i) {
  return i * 2;
}

int PriorityQueue::right(int i) {
  return i * 2 + 1;
}

} // data_structure
} // sakabatou_algorithm
