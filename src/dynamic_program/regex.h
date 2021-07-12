#pragma once

#include <string>

namespace sakabatou_algorithm {
namespace dynamic_program {

// 正则表达式匹配，支持 "." "*"
bool is_match(const std::string& text, const std::string& pattern);

} // dynamic_program
} // sakabatou_algorithm
