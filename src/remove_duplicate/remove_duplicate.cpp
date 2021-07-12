#include "remove_duplicate/remove_duplicate.h"

#include <stack>
#include <algorithm>

namespace sakabatou_algorithm {
namespace remove_duplicate {

std::string removeDuplicateLetters(std::string s) {
  std::vector<int> letter_cnt(256, 0);
  for (const char& c : s) {
    letter_cnt[c]++;
  }

  std::vector<bool> letter_finded(256, false);
  std::stack<char> stack;
  for (const char& c : s) {
    letter_cnt[c]--;

    if (letter_finded[c]) continue;

    while (!stack.empty() && c < stack.top() && letter_cnt[stack.top()] > 0) {
      letter_finded[stack.top()] = false;
      stack.pop();
    }

    stack.push(c);
    letter_finded[c] = true;
  }

  std::string result;
  result.reserve(stack.size());
  while (!stack.empty()) {
    result.push_back(stack.top());
    stack.pop();
  }
  std::reverse(result.begin(), result.end());
  return result;
}

int removeDuplicateInOrderedArray(std::vector<int> nums) {
  if (nums.empty()) return 0;

  int slow = 0, fast = 0;
  while (fast < nums.size()) {
    if (nums[slow] != nums[fast]) {
      slow++;
      if (slow != fast) {
        nums[slow] = nums[fast];
      }
    }
    fast++;
  }

  return slow + 1;
}

ListNode* removeDuplicateInOrderedList(ListNode* head) {
  if (head == nullptr) return nullptr;

  ListNode *slow = head, *fast = head;
  while (fast != nullptr) {
    if (slow->val != fast->val) {
      slow->next = fast;
      slow = slow->next;
    }
    fast = fast->next;
  }

  slow->next = nullptr;
  return head;
}

int removeItem(std::vector<int> nums, int val) {
  if (nums.empty()) return 0;

  int left = 0, right = nums.size() - 1;
  while (left <= right) {
    if (nums[left] == val) {
      while (nums[right] == val && left < right) {
        right--;
      }

      if (left == right)
        break;

      std::swap(nums[left], nums[right]);
    }
    left++;
  }
  return left;
}

void moveZeroes(std::vector<int>& nums) {
  if (nums.empty()) {
    return;
  }
  int slow = 0, fast = 0;
  while (fast < nums.size()) {
    if (nums[fast] != 0) {
      nums[slow] = nums[fast];
      slow++;
    }
    fast++;
  }
  while (slow < nums.size()) {
    nums[slow++] = 0;
  }
}

} // remove_duplicate
} // sakabatou_algorithm
