#pragma once

#include <vector>
#include <string>

namespace sakabatou_algorithm {
namespace data_structure {
namespace binary_tree{

struct TreeNode {
  TreeNode(int val) : val(val) {}
  int val;
  TreeNode *left = nullptr, *right = nullptr, *next = nullptr;
};

TreeNode* invertTree(TreeNode* root);

TreeNode* connect(TreeNode* root);

TreeNode* flaten(TreeNode* root);

TreeNode* constructMaxBinaryTree(const std::vector<int>& nums);

TreeNode* buildTreeByPreorderInorder(const std::vector<int>& preorder,
                                     const std::vector<int>& inorder);
TreeNode* buildTreeByPostorderInorder(const std::vector<int>& postorder,
                                      const std::vector<int>& inorder);

// find all the duplicate sub-tree, and return root node list, one root node for one type
std::vector<TreeNode*> findDuplicateSubtrees(TreeNode* root);

int kthSmallestInBST(TreeNode* root, int k);

TreeNode* convertBSTToSumTree(TreeNode* root);

bool isValidBST(TreeNode* root);
bool isInBST(TreeNode* root, int target);
TreeNode* insertIntoBST(TreeNode* root, int val);
TreeNode* deleteInBST(TreeNode* root, int key);

std::string serialize(TreeNode* root);
TreeNode* deserialize(std::string data);

} // binary_tree
} // data_structure
} // sakabatou_algorithm
