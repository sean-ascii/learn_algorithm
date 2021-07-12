#include "slide_window/longest_unrepeated_substring.h"

#include <unordered_map>
#include <limits>

namespace sakabatou_algorithm {
namespace slide_window {

std::string longest_unrepeated_substring(const std::string& source) {
  std::unordered_map<char, int> window;

  int left = 0, right = 0;
  int start = 0, length = 0;

  while (right < source.size()) {
    char c = source[right++];
    window[c]++;

    while (window[c] > 1) {
      char d = source[left++];
      window[d]--;
    }

    if (right - left > length) {
      start = left;
      length = right - left;
    }
  }

  return source.substr(start, length);
}

} // slide_window
} // sakabatou_algorithm
