#include "read_map.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void parse_file(const std::string& filename,
                std::vector<std::vector<char>> & map_representation);
void build_graph();

void read_map(const std::string & filename) {
  std::cout << filename << std::endl;
  std::vector<std::vector<char>> map_representation;
  parse_file(filename, map_representation);
  // for (auto v : map_representation) {
  //   for (auto c : v) {
  //     std::cout << c;
  //   }
  //   std::cout << std::endl;
  // }
  build_graph();
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

void build_graph() {
}
