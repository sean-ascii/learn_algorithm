#pragma once

#include <string>
#include <vector>

namespace sakabatou_algorithm {
namespace slide_window {

// check if source has target element array
bool check_inclusion(const std::string& source, const std::string& target);

// check all inclusion
std::vector<int> check_all_inclusion(const std::string& source, const std::string& target);

} // slide_window
} // sakabatou_algorithm
