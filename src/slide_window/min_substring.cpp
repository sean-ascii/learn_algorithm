#include "slide_window/min_substring.h"

#include <unordered_map>
#include <limits>

namespace sakabatou_algorithm {
namespace slide_window {

std::string min_substring(const std::string& source, const std::string& target) {
  std::unordered_map<char, int> needs, window;
  for (const auto& c : target) {
    needs[c]++;
  }

  int left = 0, right = 0;
  int valid = 0;
  int start = 0, length = std::numeric_limits<int>::max();

  while (right < source.size()) {
    // add c
    char c = source[right++];

    if (needs.count(c)) {
      window[c]++;
      if (window[c] == needs[c]) {
        valid++;
      }
    }

    while (valid == needs.size()) {
      if (right - left < length) {
        start = left;
        length = right - left;
      }

      // pop d
      char d = source[left++];
      if (needs.count(d)) {
        window[d]--;
        if (window[d] < needs[d]) {
          valid--;
        }
      }
    }
  }

  return length == std::numeric_limits<int>::max() ? "" : source.substr(start, length);
}

} // slide_window
} // sakabatou_algorithm
