#pragma once

#include <vector>
#include <string>

namespace sakabatou_algorithm {
namespace back_track {

std::vector<std::vector<std::string>> solveNQueens(int n);

std::vector<std::vector<int>> permute(const std::vector<int>& nums);

std::vector<std::vector<int>> subsets(const std::vector<int>& nums);

std::vector<std::vector<int>> combine(int n , int k);

void solveSudoku(std::vector<std::vector<char>>& board);

std::vector<std::string> generateParenthesis(int n);

} // back_track
} // sakabatou_algorithm
