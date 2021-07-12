#include "back_track/back_track.h"

#include <algorithm>
#include <unordered_set>
#include <iostream>

namespace sakabatou_algorithm {
namespace back_track {

bool isValid(const std::vector<std::string>& board, int row, int col) {
  int n = board[row].size();
  for (int i = 0; i < row; ++i) {
    if (board[i][col] == 'Q')
      return false;
  }

  for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j) {
    if (board[i][j] == 'Q')
      return false;
  }

  for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
    if (board[i][j] == 'Q')
      return false;
  }
  return true;
}

void N_queens_back_track(
    std::vector<std::vector<std::string>>& result, std::vector<std::string>& board, int row) {
  if (row == board.size()) {
    result.push_back(board);
    return;
  }

  int n = board[row].size();
  for (int col = 0; col < n; ++col) {
    if (!isValid(board, row, col)) {
      continue;
    }

    board[row][col] = 'Q';
    N_queens_back_track(result, board, row + 1);
    board[row][col] = '.';
  }
}

std::vector<std::vector<std::string>> solveNQueens(int n) {
  std::vector<std::vector<std::string>> result;
  std::vector<std::string> board(n, std::string(n, '.'));

  N_queens_back_track(result, board, 0);

  return result;
}


void permute_back_track(
    std::vector<std::vector<int>>& result, const std::vector<int>& nums, std::vector<int>& track) {
  if (track.size() == nums.size()) {
    result.push_back(track);
    return;
  }

  for (const int i : nums) {
    if (std::find(track.begin(), track.end(), i) != track.end()) {
      continue;
    }

    track.push_back(i);
    permute_back_track(result, nums, track);
    track.pop_back();
  }
}

std::vector<std::vector<int>> permute(const std::vector<int>& nums) {
  std::vector<std::vector<int>> result;
  std::vector<int> track;
  permute_back_track(result, nums, track);
  return result;
}

void subsets_back_track(
    std::vector<std::vector<int>>& result, const std::vector<int>& nums, std::vector<int>& track,
    int start) {
  result.push_back(track);

  for (int i = start; i < nums.size(); ++i) {
    track.push_back(nums[i]);
    subsets_back_track(result, nums, track, i + 1);
    track.pop_back();
  }
}

std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
  std::vector<std::vector<int>> result;
  std::vector<int> track;
  subsets_back_track(result, nums, track, 0);
  return result;
}

void combine_back_track(
    std::vector<std::vector<int>>& result, std::vector<int>& track,
    const int n, const int k, int start) {
  if (track.size() == k) {
    result.push_back(track);
    return;
  }

  for (int i = start; i <= n; ++i) {
    track.push_back(i);
    combine_back_track(result, track, n, k, i + 1);
    track.pop_back();
  }
}

std::vector<std::vector<int>> combine(int n , int k) {
  std::vector<std::vector<int>> result;
  std::vector<int> track;
  combine_back_track(result, track, n, k, 1);
  return result;
}

bool isValidForSudoku(
    const std::vector<std::vector<char>>& board, const int r, const int c, const char ch) {
  for (int i = 0; i < 9; ++i) {
    if (board[r][i] == ch) return false;
    if (board[i][c] == ch) return false;
    if (board[(r / 3) * 3 + i / 3][(c / 3) * 3 + i % 3] == ch) return false;
  }

  return true;
}

bool sudoku_back_track(std::vector<std::vector<char>>& board, int r, int c) {
  int m = 9, n = 9;
  if (r == m) return true;
  if (c == n) {
    return sudoku_back_track(board, r + 1, 0);
  }
  if (board[r][c] != '.') {
    return sudoku_back_track(board, r, c + 1);
  }

  for (int ch = '1'; ch <= '9'; ++ch) {
    if (!isValidForSudoku(board, r, c, ch)) {
      continue;
    }

    board[r][c] = ch;
    if (sudoku_back_track(board, r, c + 1))
      return true;
    board[r][c] = '.';
  }
  return false;
}

void solveSudoku(std::vector<std::vector<char>>& board) {
  sudoku_back_track(board, 0, 0);
}

void parenthesis_back_track(
    std::vector<std::string>& result, std::string& track, const int n, int cnt) {
  if (track.size() == 2 * n) {
    if (cnt == 0)
      result.push_back(track);
    return;
  }

  track.push_back('(');
  parenthesis_back_track(result, track, n, cnt + 1);
  track.pop_back();

  if (cnt > 0) {
    track.push_back(')');
    parenthesis_back_track(result, track, n, cnt - 1);
    track.pop_back();
  }
}

std::vector<std::string> generateParenthesis(int n) {
  std::vector<std::string> result;
  std::string track;
  parenthesis_back_track(result, track, n, 0);
  return result;
}

} // back_track
} // sakabatou_algorithm
