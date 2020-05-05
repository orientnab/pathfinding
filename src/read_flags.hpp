#pragma once
#include <map>
#include <string>

struct programInput {

  enum Algos {
    dijkstra = 0,
    astar = 1
  };

  std::map<std::string, Algos> algorithms = {
    {"dijkstra", Algos::dijkstra},
    {"astar", Algos::astar}
  };

  bool input_from_stdin = false;
  bool output_to_stdout = true;
  std::string inputFile;
  std::string outputFile;
  Algos algorithm = Algos::dijkstra;

};

int read_flags(programInput & input, int argc, char *argv[]);
