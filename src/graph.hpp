#pragma once
#include <unordered_map>
#include <vector>

struct Node {
  int id;
  std::vector<int> neighbours;

  Node() {}
  Node(int id_) : id(id_) {}
  Node(int id_, std::vector<int> neighbours_) : id(id_), neighbours(neighbours_) {}

  bool operator==(const Node &p) const {
    return id == p.id;
  }
};

typedef std::unordered_map<int, Node> Graph;
