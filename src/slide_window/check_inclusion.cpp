#include "slide_window/check_inclusion.h"

#include <unordered_map>

namespace sakabatou_algorithm {
namespace slide_window {

bool check_inclusion(const std::string& source, const std::string& target) {
  std::unordered_map<char, int> needs, windows;
  for (const auto& c : target) {
    needs[c]++;
  }

  int left = 0, right = 0;
  int valid = 0;
  while (right < source.size()) {
    char c = source[right++];

    if (needs.count(c)) {
      windows[c]++;
      if (windows[c] == needs[c]) {
        valid++;
      }
    }

    while(right - left >= target.size()) {
      if (valid == target.size()) {
        return true;
      }

      char d = source[left++];
      if (needs.count(d)) {
        windows[d]--;
        if (windows[d] < needs[d]) {
          valid--;
        }
      }
    }
  }

  return false;
}

std::vector<int> check_all_inclusion(const std::string& source, const std::string& target) {
  std::vector<int> result;

  std::unordered_map<char, int> needs, window;
  for (const auto& c : target) {
    needs[c]++;
  }

  int left = 0, right = 0;
  int valid = 0;
  while (right < source.size()) {
    char c = source[right++];
    if (needs.count(c)) {
      window[c]++;
      if (window[c] == needs[c]) {
        valid++;
      }
    }

    while (right - left >= target.size()) {
      if (valid == needs.size()) {
        result.push_back(left);
      }

      char d = source[left++];
      if (needs.count(d)) {
        window[d]--;
        if (window[d] < needs[d]) {
          valid--;
        }
      }
    }
  }

  return result;
}

} // slide_window
} // sakabatou_algorithm
