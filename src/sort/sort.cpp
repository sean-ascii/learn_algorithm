#include "sort/sort.h"

#include <utility>

namespace sakabatou_algorithm {
namespace sort {

int partition(std::vector<int>& nums, const int lo, const int hi) {
  if (lo == hi) return lo;

  int p = nums[lo];
  int i = lo, j = hi + 1;
  while (true) {
    while (nums[++i] < p) {
      if (i == hi) break;
    }
    while (nums[--j] > p) {
      if (j == lo) break;
    }
    if (i >= j) break;
    std::swap(nums[i], nums[j]);
  }
  std::swap(nums[lo], nums[j]);
  return j;
}

void fastSort(std::vector<int>& nums, const int lo, const int hi) {
  if (lo >= hi) return;

  int p = partition(nums, lo, hi);
  fastSort(nums, lo, p - 1);
  fastSort(nums, p + 1, hi);
}

void fastSort(std::vector<int>& nums) {
  fastSort(nums, 0, nums.size() - 1);
}

static std::vector<int> aux;
void merge(std::vector<int>& nums, int lo, int mid, int hi) {
  for (int k = lo; k <= hi; k++) {
    aux[k] = nums[k];
  }
  int i = lo, j = mid + 1;
  for (int k = lo; k <= hi; k++) {
    if (i > mid) {
      nums[k] = aux[j++];
    } else if (j > hi) {
      nums[k] = aux[i++];
    } else if (nums[i] < nums[j]) {
      nums[k] = aux[i++];
    } else {
      nums[k] = aux[j++];
    }
  }
}

void mergeSortTopDown(std::vector<int>& nums, int lo, int hi) {
  if (lo >= hi) return;
  int mid = lo + (hi - lo) / 2;
  mergeSortTopDown(nums, lo, mid);
  mergeSortTopDown(nums, mid + 1, hi);
  merge(nums, lo, mid, hi);
}

void mergeSortTopDown(std::vector<int>& nums) {
  aux = nums;
  mergeSortTopDown(nums, 0, nums.size() - 1);
}

void mergeSortBottomUp(std::vector<int>& nums) {
  aux = nums;
  int n = nums.size();
  for (int size = 1; size < n; size *= 2) {
    for (int i = 0; i < n - size; i += 2 * size) {
      merge(nums, i, i + size - 1, std::min(i + 2 * size - 1, n - 1));
    }
  }
}

void sink(std::vector<int>& nums, int i, int last_index) {
  while (i * 2 + 1 <= last_index) {
    int j = i * 2 + 1;
    if (j + 1 <= last_index && nums[j] < nums[j + 1]) j++;
    if (nums[i] >= nums[j]) break;
    std::swap(nums[i], nums[j]);
    i = j;
  }
}

// assume that heap begin from index 0
void heapSort(std::vector<int>& nums) {
  // build heap
  int last_index = nums.size() - 1;
  for (int i = (last_index - 1) / 2; i >= 0; i--) {
    sink(nums, i, last_index);
  }
  while (last_index > 0) {
    std::swap(nums[0], nums[last_index--]);
    sink(nums, 0, last_index);
  }
}

} // sort
} // sakabatou_algorithm
