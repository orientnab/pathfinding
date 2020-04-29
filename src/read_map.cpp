#include "read_map.hpp"
#include <fstream>
#include <iostream>
#include <string>

void read_map(std::string filename) {
  parse_file(filename);
  build_graph();
}

void parse_file(std::string filename) {
  std::fstream mapFile;
  mapFile.open("tpoint.txt",std::ios::in); //open a file to perform read operation using file object
  if (mapFile.is_open()) {  //checking whether the file is open
    std::string tp;
    while(getline(mapFile, tp)) { //read data from file object and put it into string.
      std::cout << tp << "\n"; //print the data of the string
    }
    mapFile.close(); //close the file object.
  }
}
