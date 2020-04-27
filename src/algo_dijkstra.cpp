#include <algorithm>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// #include "algo_dijkstra.hpp"

int MAX_INT = std::numeric_limits<int>::max();

struct Node {
  int id;
  std::vector<Node *> neighbours;

  bool operator==(const Node &p) const {
    return id == p.id;
  }
};
struct hash_fn {
  std::size_t operator() (const Node &node) const {
    return std::hash<int>()(node.id);
  }
};
typedef std::unordered_set<Node, hash_fn> Graph;

// Dijkstra's Algorithm
// Naive implementation: <https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm>
void dijkstra(const Graph graph, const Node start, const Node target) {
  Graph Q = graph;
  std::unordered_map<Node, int, hash_fn> dist;
  std::unordered_map<Node, Node *, hash_fn> prev;
  dist.reserve(Q.size());
  prev.reserve(Q.size());
  for (auto node : Q) {
    dist[node] = MAX_INT;
    prev[node] = nullptr;
  }
  dist[start] = 0;

  while (!Q.empty()) {
    auto u_pair = std::min_element(dist.begin(), dist.end(),
      [](const auto & n1, const auto & n2) {
        return n1.second < n2.second;
    });
    Node u = u_pair->first;
    Q.erase(u);
    for (auto neighbour : u.neighbours) {
      if (Q.count(*neighbour)==1) {
        int alt = dist[u] + 1; // distance from u to its neighbours is 1
        if (alt < dist[*neighbour]) {
          dist[*neighbour] = alt;
          prev[*neighbour] = &u;
        }
      }
    }
  }

  std::vector<Node *> sequence;
  Node u = target;
  if (prev[u] || u == start) {
    do {
      sequence.push_back(&u);
      u = *prev[u];
    } while (prev[u]);
  }
}


