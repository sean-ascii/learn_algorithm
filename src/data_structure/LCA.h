#pragma once

namespace sakabatou_algorithm {
namespace data_structure {
namespace LCA {

struct TreeNode {
  TreeNode* left;
  TreeNode* right;
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);

} // LCA
} // data_structure
} // sakabatou_algorithm
