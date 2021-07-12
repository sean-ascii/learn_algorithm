#include "data_structure/reverse_list.h"

namespace sakabatou_algorithm {
namespace data_structure {
namespace list {

ListNode* reverse(ListNode* head) {
  if (!head || !head->next) return head;

  ListNode* new_head = reverse(head->next);
  head->next->next = head;
  head->next = nullptr;
  return new_head;
}

ListNode* reverseN(ListNode* head, int n, ListNode** successor) {
  if (n == 1) {
    *successor = head->next;
    return head;
  }

  ListNode* new_head = reverseN(head->next, n - 1, successor);
  head->next->next = head;
  head->next = *successor;
  return new_head;
}

ListNode* reverseN(ListNode* head, int n) {
  ListNode* successor = nullptr;
  return reverseN(head, n, &successor);
}

ListNode* reverseRange(ListNode* head, int m, int n) {
  if (m == 1) {
    return reverseN(head, n);
  }

  ListNode* new_head = reverseRange(head->next, m - 1, n - 1);
  head->next = new_head;
  return head;
}

ListNode* reverseByIter(ListNode* head) {
  ListNode *pre = nullptr, *cur = head, *next = head;
  while (cur != nullptr) {
    next = cur->next;
    cur->next = pre;
    pre = cur;
    cur = next;
  }
  return pre;
}

ListNode* reverseRangeByIter(ListNode* a, ListNode* b) {
  ListNode *pre = nullptr, *next = a, *cur = a;
  while (cur != b) {
    next = cur->next;
    cur->next = pre;
    pre = cur;
    cur = next;
  }
  return pre;
}

ListNode* reverseKGroup(ListNode* head, int k) {
  ListNode *a = head, *b = head;
  int cnt = k;
  while (--cnt && b) {
    b = b->next;
  }
  if (b == nullptr) return head;
  b = b->next;
  ListNode *new_head = reverseRangeByIter(a, b);
  a->next = reverseKGroup(b, k);
  return new_head;
}

bool traverse(ListNode* right, ListNode** left) {
  if (!right) return true;
  bool res = traverse(right->next, left);
  res = res && (right->val == (*left)->val);
  (*left) = (*left)->next;
  return res;
}

bool isPalindrome(ListNode* head) {
  ListNode* left = head;
  return traverse(head, &left);
}

} // list
} // data_structure
} // sakabatou_algorithm
