#include "dynamic_program/kmp_match.h"

namespace sakabatou_algorithm {
namespace dynamic_program {

KMP::KMP(const std::string& pattern) : pattern_(pattern) {
  if (pattern_.empty()) return;

  int M = pattern_.size();
  dp_ = std::vector<std::vector<int>>(M, std::vector<int>(256, 0));
  dp_[0][pattern_[0]] = 1; // base case
  int X = 0; // 重启状态
  for (int i = 1; i < M; i++) {
    for (int c = 0; c < 256; c++) {
      dp_[i][c] = dp_[X][c];
    }
    dp_[i][pattern_[i]] = i + 1;
    // 更新重启状态
    X = dp_[X][pattern_[i]];
  }
}

int KMP::search(const std::string& txt) {
  if (pattern_.empty()) return 0;
  int M = pattern_.size();
  int N = txt.size();
  int j = 0; // 初始状态
  for (int i = 0; i < N; i++) {
    j = dp_[j][txt[i]];
    if (j == M) return i - M + 1;
  }
  return -1;
}

} // dynamic_program
} // sakabatou_algorithm
