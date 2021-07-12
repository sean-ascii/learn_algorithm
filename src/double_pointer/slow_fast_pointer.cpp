#include "double_pointer/slow_fast_pointer.h"

namespace sakabatou_algorithm {
namespace double_pointer {
namespace slow_fast_point {

bool hasCycle(Node* head) {
  Node *slow, *fast;
  slow = fast = head;

  while (fast != nullptr && fast->next != nullptr) {
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow) return true;
  }

  return false;
}

int detectCycle(Node* head) {
  Node *slow, *fast;
  slow = fast = head;

  while (fast != nullptr && fast->next != nullptr) {
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow) break;
  }

  slow = head;
  while (slow != fast) {
    slow = slow->next;
    fast = fast->next;
  }

  return slow->value;
}

Node* findMedian(Node* head) {
  Node *slow, *fast;
  slow = fast = head;

  while (fast != nullptr && fast->next != nullptr) {
    fast = fast->next->next;
    slow = slow->next;
  }

  return slow;
}

Node* lastKth(Node* head, int k) {
  Node *slow, *fast;
  slow = fast = head;
  while (k-- > 0 && fast != nullptr) {
    fast = fast->next;
  }
  if (k > -1) return nullptr;

  while (fast != nullptr) {
    slow = slow->next;
    fast = fast->next;
  }

  return slow;
}

} // slow_fast_pointer
} // double_pointer
} // sakabatou_algorithm
