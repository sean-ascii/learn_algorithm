#pragma once

#include <vector>

namespace sakabatou_algorithm {
namespace data_structure {

class UnionFindSet {
 public:
  UnionFindSet(int n);

  // connect the parent of p and q
  void merge(int p, int q);

  // find parent of x
  int find(int x);

  int count() const { return count_; }

  bool connected(int p, int q);

 private:
  int count_; // connected set count
  std::vector<int> parents_; // parent for every node
  std::vector<int> sizes_; // size of every tree
};

} // data_structure
} // sakabatou_algorithm
