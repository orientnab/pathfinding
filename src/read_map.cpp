#include "graph.hpp"
#include "program_input.hpp"
#include "read_map.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

char UNCROSSABLE_NODE = 'x';

void parse_file(const std::string& filename,
                std::vector<std::vector<char>> & map_representation);
void build_graph(std::vector<std::vector<char>> & map_representation,
                 Graph & graph_representation);

int lookupId(const int row, const int col, const int cols) {
  return row*cols + col;
}

void read_map(const programInput & input, Graph & graph_representation) {
  const std::string & filename = input.inputFile;
  std::cout << filename << std::endl;
  std::vector<std::vector<char>> map_representation;
  parse_file(filename, map_representation);
  for (auto v : map_representation) {
    for (auto c : v) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  build_graph(map_representation, graph_representation);
}

void parse_file(const std::string& filename,
                std::vector<std::vector<char>> & map_representation) {
  std::fstream mapFile;
  mapFile.open(filename, std::ios::in);
  if (mapFile.is_open()) {
    std::string line;
    for (int i = 0; getline(mapFile, line); ++i) {
      map_representation.push_back(std::vector<char>());
      for (auto c : line) {
        map_representation[i].push_back(c);
      }
    }
    mapFile.close();
  }
}

void build_graph(std::vector<std::vector<char>> & map_representation,
                 Graph & graph_representation) {
  int rows = map_representation.size();
  int cols = map_representation[0].size();
  int id = 0;
  // Create empty graph
  for (auto row : map_representation) {
    for (auto node : row) {
      graph_representation[id] = Node(id);
      id++;
    }
  }
  // Fill Nodes with neighbours
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      int currentId = lookupId(row, col, cols);
      if (map_representation[row][col] != UNCROSSABLE_NODE) {
        if (col > 0) // Left
          if (map_representation[row][col-1] != UNCROSSABLE_NODE)
            graph_representation[currentId].neighbours.push_back(lookupId(row,col-1,cols));
        if (col < cols-1) // Right
          if (map_representation[row][col+1] != UNCROSSABLE_NODE)
            graph_representation[currentId].neighbours.push_back(lookupId(row,col+1,cols));
        if (row > 0) { // Top
          if (map_representation[row-1][col] != UNCROSSABLE_NODE)
            graph_representation[currentId].neighbours.push_back(lookupId(row-1,col,cols));
          if (col > 0) // Top Left
            if (map_representation[row-1][col-1] != UNCROSSABLE_NODE)
              graph_representation[currentId].neighbours.push_back(lookupId(row-1,col-1,cols));
          if (col < cols-1) // Top Right
            if (map_representation[row-1][col+1] != UNCROSSABLE_NODE)
              graph_representation[currentId].neighbours.push_back(lookupId(row-1,col+1,cols));
        }
        if (row < rows-1) { // Bottom
          if (map_representation[row+1][col] != UNCROSSABLE_NODE)
            graph_representation[currentId].neighbours.push_back(lookupId(row+1,col,cols));
          if (col > 0) // Bottom Left
            if (map_representation[row+1][col-1] != UNCROSSABLE_NODE)
              graph_representation[currentId].neighbours.push_back(lookupId(row+1,col-1,cols));
          if (col < cols-1) // Bottom Right
            if (map_representation[row+1][col+1] != UNCROSSABLE_NODE)
              graph_representation[currentId].neighbours.push_back(lookupId(row+1,col+1,cols));
        }
      }
    }
  }
}
