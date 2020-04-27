#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "algo_dijkstra.hpp"

// Dijkstra's Algorithm
// Naive implementation: <https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm>
void dijkstra(const Graph & graph, const Node & start, const Node & target) {

  int MAX_INT = std::numeric_limits<int>::max();
  int UNDEF = -1;

  std::unordered_set<int> Q;
  Q.reserve(graph.size());
  std::unordered_map<int, int> dist;
  std::unordered_map<int, int> prev;
  dist.reserve(Q.size());
  prev.reserve(Q.size());
  for (auto node : graph) {
    if (node.first != node.second.id)
      std::cout << "Graph Formatting Error" << std::endl;
    Q.insert(node.first);
    dist[node.first] = MAX_INT;
    prev[node.first] = UNDEF;
  }
  dist[start.id] = 0;

  while (!Q.empty()) {
    int u_id = *Q.begin();
    for (auto v : Q) {
      if (dist[v] < dist[u_id])
        u_id = v;
    }
    Q.erase(u_id);
    for (int neighbour_id : graph.at(u_id).neighbours) {
      if (Q.count(neighbour_id)==1) {
        int alt = dist[u_id] + 1; // distance from u to its neighbours is 1
        if (alt < dist[neighbour_id]) {
          dist[neighbour_id] = alt;
          prev[neighbour_id] = u_id;
        }
      }
    }
  }

  std::vector<int> sequence;
  int u_id = target.id;
  if (prev[u_id] == UNDEF) {
    std::cout << "Target cannot be reached" << std::endl;
  }
  do {
    sequence.push_back(u_id);
    u_id = prev[u_id];
  } while (u_id != UNDEF);
  if (u_id != start.id) {
    std::cout << "Target cannot be reached" << std::endl;
  }

  for (auto x : sequence)
    std::cout << x << std::endl;
}


