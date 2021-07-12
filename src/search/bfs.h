#pragma once

#include <vector>
#include <string>

namespace sakabatou_algorithm {
namespace search {
namespace bfs {

struct Node {
  Node(int val_) : val(val_), left(nullptr), right(nullptr) {};
  int val;
  Node *left, *right;
};


int minDepth(Node* root);

int openLock(std::vector<std::string> deadends, std::string target);
int openLockBiDirection(std::vector<std::string> deadends, std::string target);

int slidePuzzle(const std::vector<std::vector<int>>& board);

} // bfs
} // search
} // sakabatou_algorithm
