#pragma once
#include <limits>
#include <unordered_map>
#include <vector>

struct Node {
  int id;
  std::vector<int> neighbours;

  Node(int id_) : id(id_) {}
  Node(int id_, std::vector<int> neighbours_) : id(id_), neighbours(neighbours_) {}

  bool operator==(const Node &p) const {
    return id == p.id;
  }
};

typedef std::unordered_map<int, Node> Graph;

void dijkstra(const Graph & graph, const Node & start, const Node & target);
