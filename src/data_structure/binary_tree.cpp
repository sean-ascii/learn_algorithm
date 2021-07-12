#include "data_structure/binary_tree.h"

#include <cassert>
#include <unordered_map>
#include <deque>
#include <queue>
#include <iostream>

namespace sakabatou_algorithm {
namespace data_structure {
namespace binary_tree{

TreeNode* invertTree(TreeNode* root) {
  if (!root) return nullptr;
  TreeNode* left = invertTree(root->left);
  TreeNode* right = invertTree(root->right);
  root->left = right;
  root->right = left;
  return root;
}

void connectTwoTree(TreeNode* left_root, TreeNode* right_root) {
  if (!left_root || !right_root) return;

  left_root->next = right_root;

  connectTwoTree(left_root->left, left_root->right);
  connectTwoTree(right_root->left, right_root->right);

  connectTwoTree(left_root->right, right_root->left);
}

TreeNode* connect(TreeNode* root) {
  if (!root) return nullptr;
  connectTwoTree(root->left, root->right);
  return root;
}

TreeNode* flaten(TreeNode* root) {
  if (!root) return nullptr;

  TreeNode* left = flaten(root->left);
  TreeNode* right = flaten(root->right);

  root->right = left;
  root->left = nullptr;

  TreeNode* last = root;
  while (last->right != nullptr) {
    last = last->right;
  }
  last->right = right;

  return root;
}

TreeNode* constructMaxBinaryTree(const std::vector<int>& nums) {
  if (nums.empty()) return nullptr;

  int max = nums[0];
  int max_index = 0;
  for (int i = 1; i < nums.size(); ++i) {
    if (nums[i] > max) {
      max = nums[i];
      max_index = i;
    }
  }

  TreeNode* root = new TreeNode(max);
  std::vector<int> left_nums(nums.begin(), nums.begin() + max_index);
  std::vector<int> right_nums(nums.begin() + max_index + 1, nums.end());

  TreeNode* left = constructMaxBinaryTree(left_nums);
  TreeNode* right = constructMaxBinaryTree(right_nums);

  root->left = left;
  root->right = right;
  return root;
}

TreeNode* buildTreeByPreorderInorder(const std::vector<int>& preorder, const std::vector<int>& inorder) {
  if (preorder.empty()) return nullptr;
  assert(preorder.size() == inorder.size());

  TreeNode* root = new TreeNode(preorder.front());

  int inorder_root_index = -1;
  for (int i = 0; i < inorder.size(); ++i) {
    if (inorder[i] == preorder.front()) {
      inorder_root_index = i;
      break;
    }
  }
  assert(inorder_root_index >= 0);

  int left_size = inorder_root_index;

  std::vector<int> left_preorder, right_preorder, left_inorder, right_inorder;
  left_inorder.assign(inorder.begin(), inorder.begin() + inorder_root_index);
  right_inorder.assign(inorder.begin() + inorder_root_index + 1, inorder.end());
  left_preorder.assign(preorder.begin() + 1, preorder.begin() + left_size + 1);
  right_preorder.assign(preorder.begin() + left_size + 1, preorder.end());

  root->left = buildTreeByPreorderInorder(left_preorder, left_inorder);
  root->right = buildTreeByPreorderInorder(right_preorder, right_inorder);
  return root;
}

TreeNode* buildTreeByPostorderInorder(const std::vector<int>& postorder,
                                      const std::vector<int>& inorder) {
  if (postorder.empty()) return nullptr;
  assert(postorder.size() == inorder.size());

  TreeNode* root = new TreeNode(postorder.back());

  int inorder_root_index = -1;
  for (int i = 0; i < inorder.size(); ++i) {
    if (inorder[i] == postorder.back()) {
      inorder_root_index = i;
      break;
    }
  }
  assert(inorder_root_index >= 0);

  int left_size = inorder_root_index;

  std::vector<int> left_postorder, right_postorder, left_inorder, right_inorder;
  left_inorder.assign(inorder.begin(), inorder.begin() + inorder_root_index);
  right_inorder.assign(inorder.begin() + inorder_root_index + 1, inorder.end());
  left_postorder.assign(postorder.begin(), postorder.begin() + left_size);
  right_postorder.assign(postorder.begin() + left_size, postorder.end() - 1);

  root->left = buildTreeByPostorderInorder(left_postorder, left_inorder);
  root->right = buildTreeByPostorderInorder(right_postorder, right_inorder);

  return root;
}

std::unordered_map<std::string, int> subtree_occur_times;
std::vector<TreeNode*> duplicate_substree_root;

std::string serializeTree(TreeNode* root) {
  if (!root) return "#";

  std::string left = serializeTree(root->left);
  std::string right = serializeTree(root->right);
  std::string result = left + "," + right + "," + std::to_string(root->val);

  if (!subtree_occur_times.count(result)) {
    subtree_occur_times[result] = 1;
  } else if (subtree_occur_times[result] == 1) {
    duplicate_substree_root.push_back(root);
    subtree_occur_times[result]++;
  } else {
    subtree_occur_times[result]++;
  }

  return result;
}

std::vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
  serializeTree(root);
  return duplicate_substree_root;
}

int rank = 0;
int result = 0;
void inorderTraverseForKthSmallest(TreeNode* root, int k) {
  if (!root) return;
  if (rank == k) return;

  inorderTraverseForKthSmallest(root->left, k);
  rank++;
  if (rank == k) {
    result = root->val;
    return;
  }
  inorderTraverseForKthSmallest(root->right, k);
}

int kthSmallestInBST(TreeNode* root, int k) {
  inorderTraverseForKthSmallest(root, k);
  return result;
}

int sum = 0;
TreeNode* convertBSTToSumTree(TreeNode* root) {
  if (!root) return nullptr;

  convertBSTToSumTree(root->right);
  sum += root->val;
  root->val = sum;
  convertBSTToSumTree(root->left);
  return root;
}

bool isValidBST(TreeNode* root, TreeNode* min, TreeNode* max) {
  if (!root) return true;

  if (!min && root->val <= min->val) return false;
  if (!max && root->val >= max->val) return false;

  return isValidBST(root->left, min, root) &&
         isValidBST(root->right, root, max);
}

bool isValidBST(TreeNode* root) {
  return isValidBST(root, nullptr, nullptr);
}

bool isInBST(TreeNode* root, int target) {
  if (!root) return false;

  if (root->val == target) {
    return true;
  } else if (root->val > target) {
    return isInBST(root->left, target);
  } else {
    return isInBST(root->right, target);
  }
}

TreeNode* insertIntoBST(TreeNode* root, int val) {
  if (!root) {
    return new TreeNode(val);
  }

  assert(root->val != val);

  if (root->val > val) {
    root->left = insertIntoBST(root->left, val);
  } else {
    root->right = insertIntoBST(root->right, val);
  }

  return root;
}

TreeNode* getMin(TreeNode* root) {
  if (!root) return nullptr;
  if (root->left == nullptr) return root;
  return getMin(root->left);
}

TreeNode* deleteInBST(TreeNode* root, int key) {
  if (!root) return nullptr;

  if (root->val == key) {
    if (root->left == nullptr) {
      return root->right;
    }
    if (root->right == nullptr) {
      return root->left;
    }
    // left and right both not null
    TreeNode* min = getMin(root->right);
    root->val = min->val;
    root->right = deleteInBST(root->right, min->val);
  } else if (root->val > key) {
    root->left = deleteInBST(root->left, key);
  } else {
    root->right = deleteInBST(root->right, key);
  }

  return root;
}

void serializeByPreOrder(TreeNode* root, std::string& result) {
  if (!root) {
    result.append({'#'}).append({','});
    return;
  }

  result.append(std::to_string(root->val)).append({','});
  serializeByPreOrder(root->left, result);
  serializeByPreOrder(root->right, result);
}
void serializeByPostOrder(TreeNode* root, std::string& result) {
  if (!root) {
    result.append("#").append(",");
    return;
  }

  serializeByPostOrder(root->left, result);
  serializeByPostOrder(root->right, result);
  result.append(std::to_string(root->val)).append(",");
}
void serializeByIter(TreeNode* root, std::string& result) {
  if (!root) {
    return;
  }

  std::queue<TreeNode*> node_queue;
  node_queue.push(root);
  while (!node_queue.empty()) {
    TreeNode* node = node_queue.front();
    node_queue.pop();
    if (!node) {
      result.append("#").append(",");
      continue;
    }
    result.append(std::to_string(node->val)).append(",");

    node_queue.push(node->left);
    node_queue.push(node->right);
  }
  return;
}
std::string serialize(TreeNode* root) {
  std::string result;
  // serializeByPreOrder(root, result);
  // serializeByPostOrder(root, result);
  serializeByIter(root, result);
  return result;
}

std::deque<std::string> splitString(const std::string& s, const char delim) {
  std::deque<std::string> result;
  std::string::size_type pos1, pos2;
  pos2 = s.find(delim);
  pos1 = 0;
  while (pos2 != std::string::npos) {
    result.push_back(s.substr(pos1, pos2 - pos1));
    pos1 = pos2 + 1;
    pos2 = s.find(delim, pos1);
  }
  if (pos1 != s.length()) {
    result.push_back(s.substr(pos1));
  }
  return result;
}
TreeNode* deserializeByPreOrder(std::deque<std::string>& nodes) {
  if (nodes.empty()) return nullptr;

  std::string current = nodes.front();
  nodes.pop_front();
  if (current == "#") return nullptr;
  TreeNode* root = new TreeNode(std::stoi(current));
  root->left = deserializeByPreOrder(nodes);
  root->right = deserializeByPreOrder(nodes);
  return root;
}
TreeNode* deserializeByPostOrder(std::deque<std::string>& nodes) {
  if (nodes.empty()) return nullptr;

  std::string current = nodes.back();
  nodes.pop_back();
  if (current == "#") return nullptr;
  TreeNode* root = new TreeNode(std::stoi(current));

  root->right = deserializeByPostOrder(nodes);
  root->left = deserializeByPostOrder(nodes);

  return root;
}
TreeNode* deserializeByIter(std::deque<std::string>& nodes) {
  if (nodes.empty()) return nullptr;

  std::queue<TreeNode*> node_queue;
  TreeNode* root = new TreeNode(std::stoi(nodes.front()));
  node_queue.push(root);
  nodes.pop_front();
  while (!node_queue.empty()) {
    TreeNode* cur = node_queue.front();
    node_queue.pop();

    if (nodes.front() != "#") {
      cur->left = new TreeNode(std::stoi(nodes.front()));
      node_queue.push(cur->left);
    }
    nodes.pop_front();
    if (nodes.front() != "#") {
      cur->right = new TreeNode(std::stoi(nodes.front()));
      node_queue.push(cur->right);
    }
    nodes.pop_front();
  }
  return root;
}
TreeNode* deserialize(std::string data) {
  std::deque<std::string> nodes = splitString(data, ',');
  // return deserializeByPreOrder(nodes);
  // return deserializeByPostOrder(nodes);
  return deserializeByIter(nodes);
}

} // binary_tree
} // data_structure
} // sakabatou_algorithm
