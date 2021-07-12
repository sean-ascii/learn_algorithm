#include <gtest/gtest.h>

#include "back_track/back_track.h"

using namespace sakabatou_algorithm::back_track;

// TEST(BackTrackTest, permute_test) {
//   std::vector<int> nums{1, 2, 3};
//   std::vector<std::vector<int>> result = permute(nums);
//   for (const auto& track : result) {
//     for (const auto& i : track) {
//       std::cout << i << " ";
//     }
//     std::cout << std::endl;
//   }
// }

// TEST(BackTrackTest, n_queen_test) {
//   std::vector<std::vector<std::string>> result = solveNQueens(8);
//   std::cout << "size: " << result.size() << std::endl;
//   for (const auto& r : result) {
//     for (const auto& s : r) {
//       std::cout << s << std::endl;
//     }
//     std::cout << std::endl;
//   }
// }

// TEST(BackTrackTest, subsets_test) {
//   std::vector<int> nums{1, 2, 3};
//   std::vector<std::vector<int>> result = subsets(nums);
//   for (const auto& r : result) {
//     for (const auto& n : r) {
//       std::cout << n << ' ';
//     }
//     std::cout << std::endl;
//   }
// }

// TEST(BackTrackTest, combine_test) {
//   std::vector<std::vector<int>> result = combine(4, 2);
//   for (const auto& r : result) {
//     for (const auto& n : r) {
//       std::cout << n << ' ';
//     }
//     std::cout << std::endl;
//   }
// }

// TEST(BackTrackTest, sudoku_test) {
//   std::vector<std::vector<char>> board(9, std::vector<char>(9, '.'));
//   solveSudoku(board);
//   for (const auto& row : board) {
//     for (const auto& e : row) {
//       std::cout << e << " ";
//     }
//     std::cout << std::endl;
//   }
// }

TEST(BackTrackTest, parenthesis_test) {
  std::vector<std::string> result = generateParenthesis(3);
  for (const auto& r : result) {
    std::cout << r << std::endl;
  }
}