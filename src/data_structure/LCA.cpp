#include "data_structure/LCA.h"

namespace sakabatou_algorithm {
namespace data_structure {
namespace LCA {

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (root == nullptr) return nullptr;
  if (root == p || root == q) return root;

  TreeNode* left = lowestCommonAncestor(root->left, p, q);
  TreeNode* right = lowestCommonAncestor(root->right, p, q);

  if (left == nullptr && right == nullptr) return nullptr;
  if (left != nullptr && right != nullptr) return root;
  return left == nullptr ? right : left;
}

} // LCA
} // data_structure
} // sakabatou_algorithm
