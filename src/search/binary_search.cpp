#include "search/binary_search.h"

#include <cmath>
#include <algorithm>
#include <numeric>

namespace sakabatou_algorithm {
namespace search {

int binary_search(std::vector<int> nums, int target) {
  int left = 0, right = nums.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1;
}

int left_bound(std::vector<int> nums, int target) {
  int left = 0, right = nums.size();

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] > target) {
      right = mid;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return left;
}

int right_bound(std::vector<int> nums, int target) {
  int left = 0, right = nums.size();

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  if (left == 0) {
    return 0;
  } else if (nums[left - 1] == target) {
    return left - 1;
  } else {
    return left;
  }
}

bool canFinishEat(const std::vector<int>& piles, int speed, int H) {
  int total_H = 0;
  for (int i = 0; i < piles.size(); ++i) {
    total_H += std::ceil((double)piles[i] / speed);
  }

  return total_H <= H;
}

int minEatingSpeed(const std::vector<int>& piles, int H) {
  if (H < piles.size()) return -1;

  // find max pile
  int max = 0;
  for (int i = 0; i < piles.size(); ++i) {
    if (piles[i] > max) {
      max = piles[i];
    }
  }

  // speed range
  int left = 1, right = max;
  while (left < right) {
    int mid = left + (right - left) /2;
    if (canFinishEat(piles, mid, H)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  return left;
}

bool canFinishShip(const std::vector<int>& weights, int D, int capacity) {
  int total_D = 0;
  int sum = 0;
  for (int i = 0; i < weights.size(); ++i) {
    sum += weights[i];

    if (i < weights.size() - 1 && sum + weights[i + 1] > capacity) {
      total_D++;
      sum = 0;
    }
  }

  total_D += (sum > 0 ? 1 : 0);

  return total_D <= D;
}

int shipWithDays(const std::vector<int>& weights, int D) {
  // capacity range
  int left = *(std::max_element(weights.begin(), weights.end()));
  int right = std::accumulate(weights.begin(), weights.end(), 0);

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (canFinishShip(weights, D, mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  return left;
}

} // search
} // sakabatou_algorithm
