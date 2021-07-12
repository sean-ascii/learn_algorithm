#include "data_structure/graph.h"

#include <algorithm>
#include <fstream>

#include "data_structure/union_find_set.h"

namespace sakabatou_algorithm {
namespace data_structure {
namespace Graph {

Graph::Graph(int size_v) : size_v_(size_v), size_e_(0), adj_list_(size_v) {}

Graph::Graph(std::istream& in) : size_e_(0) {
  // read from standard input or file
  int size_v, size_e;
  in >> size_v >> size_e;

  size_v_ = size_v;
  adj_list_.resize(size_v_);
  for (int i = 0; i < size_e; i++) {
    int v, w;
    in >> v >> w;
    addEdge(v, w);
  }
}

void Graph::addEdge(int v, int w) {
  adj_list_[v].push_back(w);
  adj_list_[w].push_back(v);
  size_e_++;
}

DepthFirstSearch::DepthFirstSearch(const Graph& graph, int s)
    : count_(0), marked_(graph.size_v(), false) {
  dfs(graph, s);
}

void DepthFirstSearch::dfs(const Graph& graph, int v) {
  marked_[v] = true;
  count_++;
  for (const int w : graph.adj(v)) {
    if (!marked_[w]) dfs(graph, w);
  }
}

DepthFirstPaths::DepthFirstPaths(const Graph& graph, int s)
    : marked_(graph.size_v(), false), parents_(graph.size_v(), -1), s_(s) {
  dfs(graph, s);
}

void DepthFirstPaths::dfs(const Graph& graph, int v) {
  marked_[v] = true;
  for (const int w : graph.adj(v)) {
    if (!marked_[w]) {
      parents_[w] = v;
      dfs(graph, w);
    }
  }
}

std::vector<int> DepthFirstPaths::pathTo(int v) const {
  if (!marked_[v]) return {};
  std::vector<int> path;
  int x = v;
  while (x != s_) {
    path.push_back(x);
    x = parents_[x];
  }
  path.push_back(s_);
  std::reverse(path.begin(), path.end());
  return path;
}

BreadthFirstPaths::BreadthFirstPaths(const Graph& graph, int s)
    : marked_(graph.size_v(), false), parent_(graph.size_v(), -1), s_(s) {
  bfs(graph, s);
}

void BreadthFirstPaths::bfs(const Graph& graph, int v) {
  std::queue<int> q;
  marked_[v] = true;
  q.push(v);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (const int w : graph.adj(x)) {
      if (!marked_[w]) {
        q.push(w);
        parent_[w] = x;
        marked_[w] = true;
      }
    }
  }
}

std::vector<int> BreadthFirstPaths::pathTo(int v) const {
  if (!marked_[v]) return {};
  std::vector<int> path;
  int x = v;
  while (x != s_) {
    path.push_back(x);
    x = parent_[x];
  }
  path.push_back(s_);
  std::reverse(path.begin(), path.end());
  return path;
}

ConnectedComponents::ConnectedComponents(const Graph& graph)
    : marked_(graph.size_v(), false), id_(graph.size_v(), -1), count_(0) {
  for (int i = 0; i < graph.size_v(); i++) {
    if (!marked_[i]) {
      dfs(graph, i);
      count_++;
    }
  }
}

void ConnectedComponents::dfs(const Graph& graph, int v) {
  marked_[v] = true;
  id_[v] = count_;
  for (const int w : graph.adj(v)) {
    if (!marked_[w]) dfs(graph, w);
  }
}

Cycle::Cycle(const Graph& graph)
    : marked_(graph.size_v(), false), has_cycle_(false) {
  for (int i = 0; i < graph.size_v(); i++) {
    if (!marked_[i]) {
      dfs(graph, i, i);
    }
  }
}

void Cycle::dfs(const Graph& graph, int v, int u) {
  marked_[v] = true;
  for (const int w : graph.adj(v)) {
    if (!marked_[w]) {
      dfs(graph, w, v);
    } else if (w != u) {
      has_cycle_ = true;
    }
  }
}

TwoColor::TwoColor(const Graph& graph)
    : marked_(graph.size_v(), false),
      color_(graph.size_v(), false), is_two_color_(true) {
  for (int i = 0; i < graph.size_v(); i++) {
    if (!marked_[i]) dfs(graph, i);
  }
}

void TwoColor::dfs(const Graph& graph, int v) {
  marked_[v] = true;
  for (const int w : graph.adj(v)) {
    if (!marked_[w]) {
      color_[w] = !color_[v];
      dfs(graph, w);
    } else if (color_[w] == color_[v]) {
      is_two_color_ = false;
    }
  }
}

SymbolGraph::SymbolGraph(std::string file_name, char delim) {
  std::fstream s(file_name, std::ios::in);
  std::string line;
  while (std::getline(s, line)) {
    std::vector<std::string> ss;
    // ss = split(line, delim);
    for (int i = 0; i < ss.size(); i++) {
      if (!st_.count(ss[i]))
        st_[ss[i]] = st_.size();
    }
  }
  keys_.resize(st_.size());
  for (const auto& item : st_) {
    keys_[item.second] = item.first;
  }
  graph_.reset(new Graph(keys_.size()));
  s.clear();
  s.seekg(0);
  while (std::getline(s, line)) {
    std::vector<std::string> ss;
    // ss = split(line, delimi);
    int v = st_[ss[0]];
    for (int i = 1; i < ss.size(); i++) {
      graph_->addEdge(v, st_[ss[i]]);
    }
  }
}

Digraph::Digraph(int size_v)
    : size_v_(size_v), size_e_(0), adj_list_(size_v) {}

Digraph::Digraph(std::istream& in) : size_e_(0) {
  int size_v, size_e;
  in >> size_v >> size_e;

  size_v_ = size_v;
  adj_list_.resize(size_v_);
  for (int i = 0; i < size_e; i++) {
    int v, w;
    in >> v >> w;
    addEdge(v, w);
  }
}

void Digraph::addEdge(int v, int w) {
  adj_list_[v].push_back(w);
  size_e_++;
}

Digraph Digraph::reverse() const {
  Digraph graph(size_v_);
  for (int v = 0; v < size_v_; v++) {
    for (const int w : adj_list_[v]) {
      graph.addEdge(w, v);
    }
  }
  return graph;
}

DirectedDFS::DirectedDFS(const Digraph& graph, int s)
    : marked_(graph.size_v(), false) {
  dfs(graph, s);
}

DirectedDFS::DirectedDFS(const Digraph& graph, std::vector<int> sources)
    : marked_(graph.size_v(), false) {
  for (const int i : sources) {
    if (!marked_[i]) dfs(graph, i);
  }
}

void DirectedDFS::dfs(const Digraph& graph, int v) {
  marked_[v] = true;
  for (const int w : graph.adj(v)) {
    if (!marked_[w]) dfs(graph, w);
  }
}

DirectedCycle::DirectedCycle(const Digraph& graph)
    : marked_(graph.size_v(), false), parent_(graph.size_v(), -1),
      on_stack_(graph.size_v(), false) {
  for (int v = 0; v < graph.size_v(); v++) {
    if (hasCycle()) break;
    if (!marked_[v]) dfs(graph, v);
  }
}

void DirectedCycle::dfs(const Digraph& graph, int v) {
  marked_[v] = true;
  on_stack_[v] = true;
  for (int w : graph.adj(v)) {
    if (hasCycle()) break;
    if (!marked_[w]) {
      parent_[w] = v;
      dfs(graph, w);
    } else if (on_stack_[w]) {
      int x = v;
      while (x != w) {
        cycle_.push_back(x);
        x = parent_[x];
      }
      cycle_.push_back(w);
      cycle_.push_back(v);
      std::reverse(cycle_.begin(), cycle_.end());
    }
  }
  on_stack_[v] = false;
}

DirectedCycle2::DirectedCycle2(const Digraph& graph)
    : flag_(graph.size_v(), 0), has_cycle_(false) {
  for (int v = 0; v < graph.size_v(); v++) {
    if (has_cycle_) break;
    if (flag_[v] == 0) {
      dfs(graph, v);
    }
  }
}

void DirectedCycle2::dfs(const Digraph& graph, int v) {
  flag_[v] = 1;
  for (int w : graph.adj(v)) {
    if (has_cycle_) break;
    if (flag_[w] == 0) {
      dfs(graph, w);
    } else if (flag_[w] == 1) {
      has_cycle_ = true;
    }
  }
  flag_[v] = -1;
}

DepthFirstOrder::DepthFirstOrder(const Digraph& graph)
    : marked_(graph.size_v(), false) {
  pre_order_.reserve(graph.size_v());
  post_order_.reserve(graph.size_v());
  reverse_post_order_.reserve(graph.size_v());
  for (int v = 0; v < graph.size_v(); v++) {
    if (!marked_[v]) dfs(graph, v);
  }
  reverse_post_order_.assign(post_order_.rbegin(), post_order_.rend());
}

void DepthFirstOrder::dfs(const Digraph& graph, int v) {
  marked_[v] = true;
  pre_order_.push_back(v);
  for (int w : graph.adj(v)) {
    if (!marked_[w]) dfs(graph, w);
  }
  post_order_.push_back(v);
}

Topological::Topological(const Digraph& graph) {
  DirectedCycle cycle_finder(graph);
  if (!cycle_finder.hasCycle()) {
    DepthFirstOrder dfs(graph);
    order_ = dfs.reverse_post_order();
  }
}

Topological2::Topological2(const Digraph& graph) {
  std::vector<int> indegrees(graph.size_v(), 0);
  for (int v = 0; v < graph.size_v(); v++) {
    for (int w : graph.adj(v)) {
      indegrees[w]++;
    }
  }
  std::queue<int> q; // 0入度队列
  for (int v = 0; v < graph.size_v(); v++) {
    if (indegrees[v] == 0) q.push(v);
  }

  order_.reserve(graph.size_v());
  while (!q.empty()) {
    order_.push_back(q.front());
    q.pop();
    for (int w : graph.adj(order_.back())) {
      indegrees[w]--;
      if (indegrees[w] == 0) q.push(w);
    }
  }

  // 如果最后没有0入度的节点，但是并没有完全访问到所有节点，则证明有环
  if (order_.size() != graph.size_v()) {
    order_.clear();
  }
}

StrongConnectedComponents::StrongConnectedComponents(const Digraph& graph)
    : marked_(graph.size_v(), false), id_(graph.size_v(), -1), count_(0) {
  DepthFirstOrder order(graph.reverse());
  for (int v : order.reverse_post_order()) {
    if (!marked_[v]) dfs(graph, v);
    count_++;
  }
}

void StrongConnectedComponents::dfs(const Digraph& graph, int v) {
  marked_[v] =  true;
  id_[v] = count_;
  for (int w : graph.adj(v)) {
    if (!marked_[w]) dfs(graph, w);
  }
}

TransitiveClosure::TransitiveClosure(const Digraph& graph) {
  all_.reserve(graph.size_v());
  for (int v = 0; v < graph.size_v(); v++) {
    all_.push_back(DirectedDFS(graph, v));
  }
}

WeightedGraph::WeightedGraph(int size_v)
    : size_v_(size_v), size_e_(0), adj_list_(size_v) {}

WeightedGraph::WeightedGraph(std::istream& in) : size_e_(0) {
  // read from standard input or file
  int size_v, size_e;
  in >> size_v >> size_e;

  size_v_ = size_v;
  adj_list_.resize(size_v_);
  for (int i = 0; i < size_e; i++) {
    int v, w, weight;
    in >> v >> w >> weight;
    addEdge(v, w, weight);
  }
}

void WeightedGraph::addEdge(int v, int w, double weight) {
  Edge* ev = new Edge(v, w, weight);
  Edge* ew = new Edge(w, v, weight);
  adj_list_[v].push_back(ev);
  adj_list_[w].push_back(ew);
  size_e_++;
}

std::vector<const Edge*> WeightedGraph::edges() const {
  std::vector<const Edge*> result;
  for (int v = 0; v < size_v_; v++) {
    for (auto e : adj_list_[v]) {
      if (e->either > v) result.push_back(e);
    }
  }
  return result;
}

LazyPrimMST::LazyPrimMST(const WeightedGraph& graph)
    : marked_(graph.size_v(), false), weight_(0.0) {
  visit(graph, 0);
  while (!pq_.empty()) {
    auto e = pq_.top();
    pq_.pop();
    if (marked_[e->either] && marked_[e->other]) continue;
    mst_.push_back(e);
    if (!marked_[e->either]) visit(graph, e->either);
    if (!marked_[e->other]) visit(graph, e->other);
  }

  for (auto e : mst_) {
    weight_ += e->weight;
  }
}

void LazyPrimMST::visit(const WeightedGraph& graph, int v) {
  marked_[v] = true;
  for (auto e : graph.adj(v)) {
    if (!marked_[e->either]) pq_.push(e);
  }
}

PrimMST::PrimMST(const WeightedGraph& graph)
    : marked_(graph.size_v(), false),
      distance_to_(graph.size_v(), std::numeric_limits<double>::infinity()),
      edge_to_(graph.size_v(), nullptr),
      pq_(graph.size_v()), weight_(0.0) {
  distance_to_[0] = 0.0;
  pq_.insert(0, 0.0);
  while (!pq_.empty()) {
    visit(graph, pq_.deleteMin());
  }

  for (int v = 1; v < graph.size_v(); v++) {
    mst_.push_back(edge_to_[v]);
    weight_ += distance_to_[v];
  }
}

void PrimMST::visit(const WeightedGraph& graph, int v) {
  marked_[v] = true;
  for (auto e : graph.adj(v)) {
    int w = e->other;
    if (marked_[w]) continue;
    if (e->weight < distance_to_[w]) {
      edge_to_[w] = e;
      distance_to_[w] = e->weight;
      if (pq_.contains(w))
        pq_.changeValue(w, distance_to_[w]);
      else
        pq_.insert(w, distance_to_[w]);
    }
  }
}

KruskalMST::KruskalMST(const WeightedGraph& graph)
    : weight_(0.0) {
  auto edges = graph.edges();
  std::priority_queue<const Edge*, std::vector<const Edge*>, EdgeCompare>
      pq(edges.begin(), edges.end());
  mst_.reserve(graph.size_v() - 1);
  UnionFindSet ufs(graph.size_v());
  while (!pq.empty() && mst_.size() < graph.size_v() - 1) {
    auto edge = pq.top();
    pq.pop();
    int v = edge->either, w = edge->other;
    if (ufs.connected(v, w)) continue;
    ufs.connected(v, w);
    mst_.push_back(edge);
  }

  for (auto e : mst_) {
    weight_ += e->weight;
  }
}

} // Graph
} // data_structure
} // sakabatou_algorithm