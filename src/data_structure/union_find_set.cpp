#include "data_structure/union_find_set.h"

namespace sakabatou_algorithm {
namespace data_structure {

UnionFindSet::UnionFindSet(int n) : count_(n), sizes_(n, 1) {
  parents_.reserve(n);
  for (int i = 0; i < n; ++i) {
    parents_.emplace_back(i);
  }
}

void UnionFindSet::merge(int p, int q) {
  int root_p = find(p);
  int root_q = find(q);

  if (root_p == root_q) return;

  if (sizes_[root_p] < sizes_[root_q]) {
    parents_[root_p] = root_q;
    sizes_[root_q] += sizes_[root_p];
  } else {
    parents_[root_q] = root_p;
    sizes_[root_p] += sizes_[root_q];
  }

  count_--;
}

int UnionFindSet::find(int x) {
  while (parents_[x] != x) {
    parents_[x] = parents_[parents_[x]]; // compress depth
    x = parents_[x];
  }

  return x;
}

bool UnionFindSet::connected(int p, int q) {
  return find(p) == find(q);
}


} // data_structure
} // sakabatou_algorithm
