#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>
#include <memory>
#include <queue>
#include <utility>

#include "data_structure/binary_heap.h"

namespace sakabatou_algorithm {
namespace data_structure {
namespace Graph {

// 无向图
class Graph {
 public:
  // 初始化顶点，但不初始化边
  Graph(int size_v);
  // 通过配置文件或者标准输入构建图
  Graph(std::istream& in);

  int size_v() const { return size_v_; }
  int size_e() const { return size_e_; }

  void addEdge(int v, int w);
  std::vector<int> adj(int v) const { return adj_list_[v]; }

 private:
  int size_v_;
  int size_e_;
  std::vector<std::vector<int>> adj_list_;
};

// 查找s相关的连通性
class DepthFirstSearch {
 public:
  DepthFirstSearch(const Graph& graph, int s);

  bool marked(int v) const { return marked_[v]; }

  int count() const { return count_; }

 private:
  void dfs(const Graph& graph, int v);

 private:
  int count_; // num of vertex connected with s
  std::vector<bool> marked_;
};

// 查找s为起点的路径
class DepthFirstPaths {
 public:
  DepthFirstPaths(const Graph& graph, int s);

  bool hasPathTo(int v) const { return marked_[v]; }

  std::vector<int> pathTo(int v) const;

 private:
  void dfs(const Graph& graph, int v);

 private:
  std::vector<bool> marked_;
  std::vector<int> parents_;
  int s_;
};

// 查找s为起点的最短路径
class BreadthFirstPaths {
 public:
  BreadthFirstPaths(const Graph& graph, int s);

  bool hasPathTo(int v) const { return marked_[v]; }

  std::vector<int> pathTo(int v) const;

 private:
  void bfs(const Graph& graph, int v);

 private:
  std::vector<bool> marked_;
  std::vector<int> parent_;
  int s_;
};

// 查找无向图连通分量
class ConnectedComponents {
 public:
  ConnectedComponents(const Graph& graph);
  // 判断v和w连通性
  bool connected(int v, int w) const { return id_[v] == id_[w]; }
  // 连通分量的数量
  int count() const { return count_; }
  // 节点v所属于的连通分量的id(0 ~ count() - 1)
  int id(int v) const { return id_[v]; }

 private:
  void dfs(const Graph& graph, int v);

 private:
  std::vector<bool> marked_;
  std::vector<int> id_;
  int count_;
};

// 判断无向图是否有环
class Cycle {
 public:
  Cycle(const Graph& graph);

  bool hasCycle() const { return has_cycle_; }

 private:
  void dfs(const Graph& graph, int v, int u);

 private:
  std::vector<bool> marked_;
  bool has_cycle_;
};

// 判断二分图
class TwoColor {
 public:
  TwoColor(const Graph& graph);

  bool isBipartite() const { return is_two_color_; }

 private:
  void dfs(const Graph& graph, int v);

 private:
  std::vector<bool> marked_;
  std::vector<bool> color_;
  bool is_two_color_;
};

// 输入的节点数据为符号，根据这些符号和连接创建图
class SymbolGraph {
 public:
  SymbolGraph(std::string file_name, char delim = ' ');

  bool contains(const std::string& s) const { return st_.count(s); }
  int index(const std::string& s) const { return st_.at(s); }
  std::string name(int v) const { return keys_[v]; }
  const Graph& graph() const { return *graph_; }

 private:
  std::unordered_map<std::string, int> st_;
  std::vector<std::string> keys_;
  std::unique_ptr<Graph> graph_;
};

// 有向图
class Digraph {
 public:
  Digraph(int size_v);
  Digraph(std::istream& in);

  int size_v() const { return size_v_; }
  int size_e() const { return size_e_; }

  void addEdge(int v, int w);
  std::vector<int> adj(int v) const { return adj_list_[v]; }
  Digraph reverse() const;

 private:
  int size_v_;
  int size_e_;
  std::vector<std::vector<int>> adj_list_;
};

// 有向图可达性
class DirectedDFS {
 public:
  DirectedDFS(const Digraph& graph, int s);
  DirectedDFS(const Digraph& graph, std::vector<int> sources);

  bool marked(int v) const { return marked_[v]; }

 private:
  void dfs(const Digraph& graph, int v);

 private:
  std::vector<bool> marked_;
};

// DepthFirstDirectedPaths, BreadthFirstDirectedPaths
// 类似DepthFirstPaths, BreadthFirstPaths


// 检测有向环，并获取其中一个环
class DirectedCycle {
 public:
  DirectedCycle(const Digraph& graph);

  bool hasCycle() const { return !cycle_.empty(); }

  // 获取环
  std::vector<int> cycle() { return cycle_; }

 private:
  void dfs(const Digraph& graph, int v);

 private:
  std::vector<bool> marked_;
  std::vector<int> parent_;
  std::vector<int> cycle_;
  std::vector<bool> on_stack_;
};

// 利用一组额外空间判断是否有环
class DirectedCycle2 {
 public:
  DirectedCycle2(const Digraph& graph);

  bool hasCycle() const { return has_cycle_; }

 private:
  void dfs(const Digraph& graph, int v);

 private:
  std::vector<int> flag_; // 0-未访问,1-递归访问中,-1-确定无环
  bool has_cycle_;
};

// 有向图深度优先所有三种顺序：前序、后序、逆后序
class DepthFirstOrder {
 public:
  DepthFirstOrder(const Digraph& graph);

  std::vector<int> pre_order() const { return pre_order_; }
  std::vector<int> post_order() const { return post_order_; }
  std::vector<int> reverse_post_order() const { return reverse_post_order_; }

 private:
  void dfs(const Digraph& graph, int v);

 private:
  std::vector<bool> marked_;
  std::vector<int> pre_order_;
  std::vector<int> post_order_;
  std::vector<int> reverse_post_order_;
};

// 对于有向图，优先级限制下的调度问题等价于拓扑排序问题
// 可以先判断是否有环，然后无环再进行拓扑排序
// 有向图无环图的拓扑排序即为所有顶点的逆后序排序
class Topological {
 public:
  Topological(const Digraph& graph);

  bool isDAG() const { return !order_.empty(); }

  std::vector<int> order() const { return order_; }

 private:
  std::vector<int> order_;
};

// 利用入度进行拓扑排序，同步判断是否有环
class Topological2 {
 public:
  Topological2(const Digraph& graph);

  bool isDAG() const { return !order_.empty(); }

  std::vector<int> order() const { return order_; }

 private:
  std::vector<int> order_;
};

// Kosaraju算法
// 基本思路：用原图的逆向图进行逆拓扑排序，然后深度优先遍历可直接得到强连通分量
class StrongConnectedComponents {
 public:
  StrongConnectedComponents(const Digraph& graph);
  // 判断v和w是否连通
  bool strongConnected(int v, int w) const { return id_[v] == id_[w]; }
  // 强连通分量数量
  int count() const { return count_; }
  // 节点v所属的强连通分量id (0 ~ count() - 1)
  int id(int v) const { return id_[v]; }

 private:
  void dfs(const Digraph& graph, int v);

 private:
  std::vector<bool> marked_;
  std::vector<int> id_;
  int count_;
};

// 传递闭包：有向图的传递闭包是由相同的一组顶点组成的另一幅有向图，在传递闭包中存在
// 一条从v指向w的边当且仅当在G中w是从v可达的
class TransitiveClosure {
 public:
  TransitiveClosure(const Digraph& graph);

  bool reachable(int v, int w) { return all_[v].marked(w); }

 private:
  std::vector<DirectedDFS> all_;
};

// 加权连通无向图的最小生成树
struct Edge {
  Edge(int v_, int w_, double weight_) : either(v_), other(w_), weight(weight_) {}

  int either;
  int other;
  double weight;
};

struct EdgeCompare {
  bool operator()(const Edge* e1, const Edge* e2) {
    return e1->weight > e2->weight;
  }
};

class WeightedGraph {
 public:
  WeightedGraph(int size_v);
  WeightedGraph(std::istream& in);

  int size_v() const { return size_v_; }
  int size_e() const { return size_e_; }

  void  addEdge(int v, int w, double weight);
  std::vector<const Edge*> adj(int v) const { return adj_list_[v]; }
  std::vector<const Edge*> edges() const;

 private:
  int size_v_;
  int size_e_;
  std::vector<std::vector<const Edge*>> adj_list_;
};

class LazyPrimMST {
 public:
  LazyPrimMST(const WeightedGraph& graph);

  std::vector<const Edge*> edges() const { return mst_; }

  // 整个树的权重
  double weight() const { return weight_; }

 private:
  void visit(const WeightedGraph& graph, int v);

 private:
  std::vector<bool> marked_;
  std::vector<const Edge*> mst_;
  std::priority_queue<const Edge*, std::vector<const Edge*>, EdgeCompare> pq_;
  double weight_;
};

class PrimMST {
 public:
  PrimMST(const WeightedGraph& graph);

  std::vector<const Edge*> edges() const { return mst_; }

  double weight() const { return weight_; }

 private:
  void visit(const WeightedGraph& graph, int v);

 private:
  std::vector<bool> marked_;
  std::vector<double> distance_to_; // 节点与树的连接的最小权重
  std::vector<const Edge*> edge_to_; // 节点与树的权重最小的边
  IndexMinPQ<double> pq_;
  std::vector<const Edge*> mst_;
  double weight_;
};

class KruskalMST {
 public:
  KruskalMST(const WeightedGraph& graph);

  std::vector<const Edge*> edges() const { return mst_; }

  double weight() const { return weight_; }

 private:
  std::vector<const Edge*> mst_;
  double weight_;
};


} // Graph
} // data_structure
} // sakabatou_algorithm
