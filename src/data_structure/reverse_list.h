#pragma once

namespace sakabatou_algorithm {
namespace data_structure {
namespace list {

struct ListNode {
  ListNode(int val) : val(val) {}
  int val;
  ListNode* next;
};

// reverse the whole list
ListNode* reverse(ListNode* head);

// reverse first N item in list
ListNode* reverseN(ListNode* head, int n);

// reverse item range [m, n]
ListNode* reverseRange(ListNode* head, int m, int n);

// reverse the whole list by iteration
ListNode* reverseByIter(ListNode* head);

// reverse list in k group
ListNode* reverseKGroup(ListNode* head, int k);

// judge if is palindrome
bool isPalindrome(ListNode* head);

} // list
} // data_structure
} // sakabatou_algorithm
