#pragma once

namespace sakabatou_algorithm {
namespace double_pointer {
namespace slow_fast_point {

struct Node {
  Node(int value_) : value(value_), next(nullptr) {}
  int value;
  Node* next;
};

// check if link list has cycle
bool hasCycle(Node* head);

// check cycle start node, assume this link list must have cycle
int detectCycle(Node* head);

// find median of link list
Node* findMedian(Node* head);

// find the last k-th node
Node* lastKth(Node* head, int k);

} // slow_fast_pointer
} // double_pointer
} // sakabatou_algorithm
