#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <unordered_set>

#include "data_structure/LRU.h"
#include "data_structure/LFU.h"
#include "data_structure/random_set.h"
#include "data_structure/reverse_list.h"
#include "data_structure/binary_tree.h"
#include "data_structure/LCA.h"
#include "data_structure/union_find_set.h"
#include "data_structure/median_finder.h"
#include "data_structure/monotonic_stack.h"
#include "data_structure/monotonic_queue.h"
#include "data_structure/binary_heap.h"

#include <random>

using namespace sakabatou_algorithm::data_structure;

// TEST(DataStructureTest, LFU_test) {
//   LFU::LFUCache cache(2);
//   cache.put(1, 10);
//   cache.put(2, 20);

//   ASSERT_EQ(cache.get(1), 10);

//   cache.put(3, 30);

//   ASSERT_EQ(cache.get(2), -1);
// }

// TEST(DataStructureTest, LRU_test) {
//   LRU::LRUCache cache(2);
//   cache.put(1, 10);
//   cache.put(2, 20);

//   ASSERT_EQ(cache.get(1), 10);

//   cache.put(3, 30);

//   ASSERT_EQ(cache.get(2), -1);
// }

// TEST(DataStructureTest, random_set_test) {
//   using namespace sakabatou_algorithm::data_structure;
//   RandomizedSet rand_set;
//   ASSERT_TRUE(rand_set.insert(1));
//   ASSERT_FALSE(rand_set.remove(2));
//   ASSERT_TRUE(rand_set.insert(2));
//   for (int i = 0; i < 10; ++i) {
//     std::cout << rand_set.getRandom() << std::endl;
//   }
// }

// TEST(DataStructureTest, random_set_with_blacklist_test) {
//   using namespace sakabatou_algorithm::data_structure;
//   RandomizedSetWithBlacklist rand_set(5, std::vector<int>{1, 4});
//   for (int i = 0; i < 10; ++i) {
//     std::cout << rand_set.pick() << std::endl;
//   }
// }

list::ListNode* createList(int n) {
  if (n < 1) return nullptr;
  list::ListNode* head = new list::ListNode(1);
  list::ListNode* pre = head;
  for (int i = 2; i <= n; ++i) {
    list::ListNode* item = new list::ListNode(i);
    pre->next = item;
    pre = item;
  }
  pre->next = nullptr;
  return head;
}

void printList(list::ListNode* head) {
  while (head) {
    std::cout << head->val << " ";
    head = head->next;
  }
  std::cout << std::endl;
}

void clearList(list::ListNode* head) {
  while (head) {
    list::ListNode* item = head;
    head = head->next;
    delete item;
  }
}

// TEST(DataStructureTest, reverse_test) {
//   list::ListNode* head = createList(6);

//   std::cout << "before revese:" << std::endl;
//   printList(head);

//   head = list::reverse(head);

//   std::cout << "after revese:" << std::endl;
//   printList(head);

//   clearList(head);
// }

// TEST(DataStructureTest, reverse_N_test) {
//   list::ListNode* head = createList(6);

//   std::cout << "before revese:" << std::endl;
//   printList(head);

//   head = list::reverseN(head, 4);

//   std::cout << "after revese:" << std::endl;
//   printList(head);

//   clearList(head);
// }

// TEST(DataStructureTest, reverse_range_test) {
//   list::ListNode* head = createList(6);

//   std::cout << "before revese:" << std::endl;
//   printList(head);

//   head = list::reverseRange(head, 2, 4);

//   std::cout << "after revese:" << std::endl;
//   printList(head);

//   clearList(head);
// }

// TEST(DataStructureTest, reverse_by_iteration_test) {
//   list::ListNode* head = createList(6);

//   std::cout << "before revese:" << std::endl;
//   printList(head);

//   head = list::reverseByIter(head);

//   std::cout << "after revese:" << std::endl;
//   printList(head);

//   clearList(head);
// }

TEST(DataStructureTest, reverse_k_group_test) {
  list::ListNode* head = createList(7);

  std::cout << "before revese:" << std::endl;
  printList(head);

  head = list::reverseKGroup(head, 3);

  std::cout << "after revese:" << std::endl;
  printList(head);

  clearList(head);
}

// TEST(DataStructureTest, is_palindrome_test) {
//   list::ListNode* head = new list::ListNode(1);
//   list::ListNode* pre = head;
//   for (int i = 2; i <= 3; ++i) {
//     list::ListNode* item = new list::ListNode(i);
//     pre->next = item;
//     pre = item;
//   }
//   for (int i = 3; i >= 2; --i) {
//     list::ListNode* item = new list::ListNode(i);
//     pre->next = item;;
//     pre = item;
//   }
//   pre->next = nullptr;
//   std::cout << "palindrome list:" << std::endl;
//   printList(head);

//   std::cout << std::boolalpha << "is palinedrome: " << list::isPalindrome(head) << std::endl;

//   clearList(head);
// }

// void printBindaryTree(binary_tree::TreeNode* root) {
//   if (!root) return;

//   std::queue<binary_tree::TreeNode*> node_queue;
//   int current_line_cnt, next_line_cnt;

//   node_queue.push(root);
//   current_line_cnt = 1;
//   next_line_cnt = 0;
//   while (!node_queue.empty()) {
//     binary_tree::TreeNode* node = node_queue.front();
//     std::cout << node->val << " ";

//     node_queue.pop();
//     current_line_cnt--;

//     if (node->left) {
//       node_queue.push(node->left);
//       next_line_cnt++;
//     }
//     if (node->right) {
//       node_queue.push(node->right);
//       next_line_cnt++;
//     }

//     if (current_line_cnt == 0) {
//       std::cout << std::endl;
//       current_line_cnt = next_line_cnt;
//       next_line_cnt = 0;
//     }
//   }
// }

// TEST(DataStructureTest, invert_tree_test) {
//   // TODO: use create function
//   using namespace sakabatou_algorithm::data_structure::binary_tree;
//   std::vector<int> preorder{1, 2, 4, 5, 3, 6, 7};
//   std::vector<int> inorder{4, 2, 5, 1, 6, 3, 7};
//   TreeNode* root = buildTreeByPreorderInorder(preorder, inorder);
//   printBindaryTree(root);
//   invertTree(root);
//   printBindaryTree(root);
// }

// TEST(DataStructureTest, construct_max_tree_test) {
//   using namespace sakabatou_algorithm::data_structure::binary_tree;
//   std::vector<int> n{3, 2, 1, 6, 0, 5};
//   TreeNode* root = constructMaxBinaryTree(n);
//   printBindaryTree(root);
// }

// TEST(DataStructureTest, build_tree_test) {
//   using namespace sakabatou_algorithm::data_structure::binary_tree;
//   std::vector<int> preorder{3, 9, 20, 15, 7};
//   std::vector<int> inorder{9, 3, 15, 20, 7};
//   std::vector<int> postorder{9, 15, 7, 20, 3};
//   TreeNode* root = buildTreeByPreorderInorder(preorder, inorder);
//   printBindaryTree(root);
//   root = buildTreeByPostorderInorder(postorder, inorder);
//   printBindaryTree(root);
// }

// TEST(DataStructureTest, find_duplicate_subtree_test) {
//   using namespace sakabatou_algorithm::data_structure::binary_tree;
//   std::vector<int> preorder{1, 2, 4, 3, 2, 4, 4};
//   std::vector<int> inorder{4, 2, 1, 4, 2, 3, 4};
//   TreeNode* root = buildTreeByPreorderInorder(preorder, inorder);
//   printBindaryTree(root);

//   std::vector<TreeNode*> duplicate_list = findDuplicateSubtrees(root);
//   for (const auto i : duplicate_list) {
//     std::cout << i->val << " ";
//   }
//   std::cout << std::endl;
// }

// TEST(DataStructureTest, kth_smallest_in_BST_test) {
//   using namespace sakabatou_algorithm::data_structure::binary_tree;
//   std::vector<int> preorder{5, 3, 2, 1, 4, 6};
//   std::vector<int> inorder{1, 2, 3, 4, 5, 6};
//   TreeNode* root = buildTreeByPreorderInorder(preorder, inorder);
//   printBindaryTree(root);
//   int result = kthSmallestInBST(root, 3);
//   std::cout << "kth: " << result << std::endl;
// }

// TEST(DataStructureTest, bst_sum_test) {
//   using namespace sakabatou_algorithm::data_structure::binary_tree;
//   std::vector<int> preorder{4, 1, 0, 2, 3, 6, 5, 7, 8};
//   std::vector<int> inorder{0, 1, 2, 3, 4, 5, 6, 7, 8};
//   TreeNode* root = buildTreeByPreorderInorder(preorder, inorder);
//   printBindaryTree(root);
//   root = convertBSTToSumTree(root);
//   printBindaryTree(root);
// }

// TEST(DataSstructureTest, delete_in_BST_test) {
//   using namespace sakabatou_algorithm::data_structure::binary_tree;
//   std::vector<int> preorder{5, 2, 1, 4, 3, 6, 7};
//   std::vector<int> inorder{1, 2, 3, 4, 5, 6, 7};
//   TreeNode* root = buildTreeByPreorderInorder(preorder, inorder);
//   printBindaryTree(root);
//   root = deleteInBST(root, 2);
//   printBindaryTree(root);
// }

// TEST(DataStructureTest, codec_test) {
//   using namespace sakabatou_algorithm::data_structure::binary_tree;
//   std::vector<int> preorder{1, 2, 4, 3};
//   std::vector<int> inorder{2, 4, 1, 3};
//   TreeNode* root = buildTreeByPreorderInorder(preorder, inorder);
//   printBindaryTree(root);
//   std::string serialize_result = serialize(root);
//   std::cout << serialize_result << std::endl;
//   TreeNode* new_root = deserialize(serialize_result);
//   printBindaryTree(new_root);
// }

// struct PairHash {
//   template<typename T1, typename T2>
//   std::size_t operator() (const std::pair<T1, T2>& pair) const {
//     return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
//   }
// };

// bool indexValid(const std::pair<int, int>& index, int m , int n) {
//   if (index.first < 0 || index.first >= m) return false;
//   if (index.second < 0 || index.second >= n) return false;

//   return true;
// }

// // void solve(std::vector<std::vector<char>>& board, int m, int n) {
// //   if (m < 1 || n < 1) return;

// //   std::queue<std::pair<int, int>> index_open_set;
// //   std::vector<bool> visited(m * n, false);

// //   // init open set use O item on boundary
// //   for (int i = 0; i < m; ++i) {
// //     if (i == 0 || i == m -1) {
// //       for (int j = 0; j < n; ++j) {
// //         if (board[i][j] == 'O') {
// //           index_open_set.emplace(i, j);
// //           visited[i * n + j] = true;
// //         }
// //       }
// //     } else {
// //       if (board[i][0] == 'O') {
// //         index_open_set.emplace(i, 0);
// //         visited[i * n] = true;
// //       }
// //       if (n >= 1 && board[i][n - 1] == 'O') {
// //         index_open_set.emplace(i, n - 1);
// //         visited[i * n + n - 1] = true;
// //       }
// //     }
// //   }

// //   // expand use BFS
// //   while (!index_open_set.empty()) {
// //     auto index = index_open_set.front();
// //     index_open_set.pop();

// //     std::vector<std::pair<int, int>> neighbours{
// //       {index.first, index.second - 1},
// //       {index.first, index.second + 1},
// //       {index.first + 1, index.second},
// //       {index.first - 1, index.second},
// //     };
// //     for (const auto& neighbour : neighbours) {
// //       if (indexValid(neighbour, m, n) &&
// //           !visited[neighbour.first * n + neighbour.second] &&
// //           board[neighbour.first][neighbour.second] == 'O') {
// //         index_open_set.emplace(neighbour.first, neighbour.second);
// //         visited[neighbour.first * n + neighbour.second] = true;
// //       }
// //     }
// //   }

// //   for (int i = 0; i < m; ++i) {
// //     for (int j = 0; j < n; ++j) {
// //       if (!visited[i * n + j]) {
// //         board[i][j] = 'X';
// //       }
// //     }
// //   }
// // }

// // use union find set to solve game board
// void solve(std::vector<std::vector<char>>& board, int m, int n) {
//   if (m < 1 || n < 1) return;

//   UnionFindSet ufs(m * n + 1);
//   int dummy = m * n;
//   // merge 'O' on boundary with dummy item
//   for (int i = 0; i < n; ++i) {
//     if (board[0][i] == 'O')
//       ufs.merge(i, m * n);
//     if (board[m - 1][i] == 'O')
//       ufs.merge((m - 1) * n + i, dummy);
//   }
//   for (int i = 0; i < m; ++i) {
//     if (board[i][0] == 'O')
//       ufs.merge(i * n, m * n);
//     if (board[i][n - 1] == 'O')
//       ufs.merge(i * n + n - 1, dummy);
//   }

//   std::vector<std::pair<int, int>> actions{
//     {0, -1}, // upper
//     {0, 1}, // lower
//     {-1, 0}, // left
//     {1, 0}, // right
//   };

//   // merge stage
//   for (int i = 0; i < m; ++i) {
//     for (int j = 0; j < n; ++j) {
//       if (board[i][j] != 'O') continue;

//       for (const auto& action : actions) {
//         std::pair<int, int> neighbour_index{i + action.first, j + action.second};
//         if (!indexValid(neighbour_index, m, n)) continue;

//         if (board[neighbour_index.first][neighbour_index.second] == 'O')
//           ufs.merge(i * n + j, neighbour_index.first * n + neighbour_index.second);
//       }
//     }
//   }

//   for (int i = 0; i < m; ++i) {
//     for (int j = 0; j < n; ++j) {
//       if (board[i][j] == 'O' && !ufs.connected(i * n + j, dummy))
//         board[i][j] = 'X';
//     }
//   }
// }

// TEST(DataStructureTest, union_find_set_game_test) {
//   std::vector<std::vector<char>> board =
//       {{'X', 'X', 'X', 'X', 'O'},
//        {'X', 'X', 'X', 'O', 'X'},
//        {'O', 'O', 'X', 'O', 'X'},
//        {'X', 'O', 'X', 'X', 'X'}};
//   solve(board, 4, 5);
//   for (int i = 0; i < 4; ++i) {
//     for (int j = 0; j < 5; ++j) {
//       std::cout << board[i][j] << " ";
//     }
//     std::cout << std::endl;
//   }
// }

// bool equationPossible(const std::vector<std::string>& equations) {
//   UnionFindSet ufs(26);
//   for (const auto& equation : equations) {
//     if (equation.at(1) == '=') {
//       ufs.merge(equation.at(0) - 'a', equation.at(3) - 'a');
//     }
//   }
//   for (const auto& equation : equations) {
//     if (equation.at(1) == '!' &&
//         ufs.connected(equation.at(0) - 'a', equation.at(3) - 'a')) {
//       return false;
//     }
//   }
//   return true;
// }

// TEST(DataStructureTest, union_find_set_equation_test) {
//   std::vector<std::string> equations1{
//     "a==b", "b!=c", "c==a"
//   };
//   ASSERT_FALSE(equationPossible(equations1));
//   std::vector<std::string> equations2{
//     "c==c", "b==d", "x!=z"
//   };
//   ASSERT_TRUE(equationPossible(equations2));
// }

// TEST(DataStructureTest, median_finder_test) {
//   MedianFinder finder;
//   finder.addNum(1);
//   finder.addNum(2);
//   ASSERT_EQ(finder.findMedian(), 1.5);
//   finder.addNum(3);
//   ASSERT_EQ(finder.findMedian(), 2.0);
// }

// TEST(DataStructureTest, mono_stack_1) {
//   std::vector<int> nums{2, 1, 2, 4, 3};
//   std::vector<int> expected_result{4, 2, 4, -1, -1};
//   std::vector<int> result = nextGreaterElement(nums);
//   for (int i = 0; i < nums.size(); ++i) {
//     ASSERT_EQ(expected_result[i], result[i]);
//   }
// }

// TEST(DataStructureTest, mono_stack_2) {
//   std::vector<int> nums{73, 74, 75, 71, 69, 76};
//   std::vector<int> expected_result{1, 1, 3, 2, 1, 0};
//   std::vector<int> result = dailyTemperatures(nums);
//   for (int i = 0; i < nums.size(); ++i) {
//     ASSERT_EQ(expected_result[i], result[i]);
//   }
// }

// TEST(DataStructureTest, mono_stack_3) {
//   std::vector<int> nums{2, 1, 2, 4, 3};
//   std::vector<int> expected_result{4, 2, 4, -1, 4};
//   std::vector<int> result = nextGreaterElementWithLoop(nums);
//   for (int i = 0; i < nums.size(); ++i) {
//     ASSERT_EQ(expected_result[i], result[i]);
//   }
// }

// TEST(DataStructureTest, mono_queue) {
//   std::vector<int> nums{1, 3, -1, -3, 5, 3, 6, 7};
//   int k = 3;
//   std::vector<int> expected_result{3, 3, 5, 5, 6, 7};
//   std::vector<int> result = maxSlideWindow(nums, k);
//   for (int i = 0; i < result.size(); ++i) {
//     ASSERT_EQ(expected_result[i], result[i]);
//   }
// }

// TEST(DataStructureTest, binary_heap_test) {
//   PriorityQueue p1;
//   std::priority_queue<int> p2;
//   std::vector<int> data{1, 8 , 5, 6, 3, 4, 0, 9, 7, 2};
//   for (const auto i : data) {
//     p1.push(i);
//     p2.push(i);
//   }

//   for (int i = 0; i < data.size(); ++i) {
//     ASSERT_EQ(p1.top(), p2.top());
//     std::cout << p1.top() << std::endl;
//     p1.pop();
//     p2.pop();
//   }
// }