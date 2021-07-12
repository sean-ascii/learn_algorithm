#pragma once

#include <vector>
#include <string>

namespace sakabatou_algorithm {
namespace dynamic_program {

class KMP {
 public:
  KMP(const std::string& pattern);

  int search(const std::string& txt);

 private:
  std::vector<std::vector<int>> dp_;
  std::string pattern_;
};

} // dynamic_program
} // sakabatou_algorithm
