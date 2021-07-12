#include "search/bfs.h"

#include <queue>
#include <unordered_set>

namespace sakabatou_algorithm {
namespace search {
namespace bfs {

int minDepth(Node* root) {
  if (!root) return 0;
  std::queue<Node*> q;
  // std::unordered_set<Node*> visited;
  q.push(root);
  int depth = 1;

  while (!q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; ++i) {
      Node* node = q.front();
      q.pop();
      if (node->left == nullptr && node->right == nullptr) {
        return depth;
      }
      if (!node->left) {
        q.push(node->left);
      }
      if (!node->right) {
        q.push(node->right);
      }
    }
    depth++;
  }
  return depth;
}

std::string plusOne(std::string s, int index) {
  if (s[index] == '9') {
    s[index] = '0';
  } else {
    s[index]++;
  }

  return s;
}

std::string minusOne(std::string s, int index) {
  if (s[index] == '0') {
    s[index] = '9';
  } else {
    s[index]--;
  }

  return s;
}

int openLock(std::vector<std::string> deadends, std::string target) {
  std::unordered_set<std::string> deads(deadends.begin(), deadends.end());
  std::queue<std::string> q;
  std::unordered_set<std::string> visited;
  q.push("0000");
  visited.insert("0000");
  int step = 0;

  while (!q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; ++i) {
      std::string item = q.front();
      q.pop();
      if (item == target) {
        return step;
      }
      for (int i = 0; i < 4; ++i) {
        std::string up = plusOne(item, i);
        std::string down = minusOne(item, i);
        if (!visited.count(up) && !deads.count(up)) {
          q.push(up);
          visited.insert(up);
        }
        if (!visited.count(down) && !deads.count(down)) {
          q.push(down);
          visited.insert(down);
        }
      }
    }
    step++;
  }

  return -1;
}

int openLockBiDirection(std::vector<std::string> deadends, std::string target) {
  std::unordered_set<std::string> deads(deadends.begin(), deadends.end());
  std::unordered_set<std::string> q1;
  std::unordered_set<std::string> q2;
  std::unordered_set<std::string> visited;
  q1.insert("0000");
  visited.insert(q1.begin(), q1.end());
  q2.insert(target);
  int step = 0;

  while (!q1.empty() && !q2.empty()) {
    std::unordered_set<std::string> temp;
    for (const auto& s : q1) {
      if (q2.count(s)) {
        return step;
      }

      for (int i = 0; i < 4; ++i) {
        std::string up = plusOne(s, i);
        std::string down = minusOne(s, i);

        if (!visited.count(up) && !deads.count(up)) {
          temp.insert(up);
        }
        if (!visited.count(down) && !deads.count(down)) {
          temp.insert(down);
        }
      }
    }
    step++;
    q1 = q2;
    q2 = temp;
    visited.insert(q1.begin(), q1.end());
  }
  return -1;
}

int slidePuzzle(const std::vector<std::vector<int>>& board) {
  std::queue<std::string> q;
  std::unordered_set<std::string> visited;

  std::string start;
  for (const auto& v : board) {
    for (const auto& i : v) {
      start.push_back(i + '0');
    }
  }
  q.push(start);
  visited.insert(start);
  std::string target = "123450";
  int step = 0;
  std::vector<std::vector<int>> neighbour = {
    {1, 3},
    {0, 2, 4},
    {1, 5},
    {0, 4},
    {3, 1, 5},
    {4, 2}
  };

  while (!q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; ++i) {
      std::string s = q.front();
      q.pop();
      if (s == target) {
        return step;
      }
      int idx = 0;
      for (; s[idx] != '0'; ++idx);
      for (int adj : neighbour[idx]) {
        std::string next = s;
        std::swap(next[idx], next[adj]);
        if (!visited.count(next)) {
          q.push(next);
          visited.insert(next);
        }
      }
    }
    step++;
  }

  return -1;
}

} // bfs
} // search
} // sakabatou_algorithm
