#pragma once

#include <string>
#include <vector>

namespace sakabatou_algorithm {
namespace remove_duplicate {

struct ListNode {
  int val;
  ListNode* next;
};

// remove duplicate letters in string, and keep letter's order, and with min directory order
std::string removeDuplicateLetters(std::string s);

// remove duplicate item in an ordered array, and should operate in raw array
int removeDuplicateInOrderedArray(std::vector<int> nums);

// remove duplicate item in an ordered list, and should operate in raw list
ListNode* removeDuplicateInOrderedList(ListNode* head);

// remove item in an array, and should operate in raw array, but can adjust item order
int removeItem(std::vector<int> nums, int val);

// move zero to the end of array, and should operate in raw list
void moveZeroes(std::vector<int>& nums);

} // remove_duplicate
} // sakabatou_algorithm
