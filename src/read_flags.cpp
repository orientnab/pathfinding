#include <boost/program_options.hpp>
#include <iostream>
#include <map>
#include <string>

#include "read_flags.hpp"

namespace po = boost::program_options;

// Messages
char HELP[] = "prompt this help.";
char USAGE[] =
  "Usage: pathFinding [--algorithm=<algorithm>] [--output=<file>] FILE\nOptions";

char INPUT[] = "input map file.";
char NO_INPUT[] = "missing input file.";
char OUTPUT[] = "output file. Default to stdout.";

char ALGO[] = "choose algorithm:\n- dijkstra (default)";
char ALGO_NOT_SET[] = "algorithm not set.";

int read_flags(programInput & input, int argc, char *argv[]) {
  po::options_description desc(USAGE);
  desc.add_options()
  ("help,h", HELP)
  ("algorithm,a", po::value<std::string>()->default_value("dijkstra"), ALGO)
  ("output,o", po::value<std::string>(), OUTPUT)
  ("input,i", po::value<std::string>(), INPUT);

  po::positional_options_description pos_desc;
  pos_desc.add("input", -1);

  po::command_line_parser parser{argc, argv};
  parser.options(desc).positional(pos_desc).allow_unregistered();
  po::parsed_options parsed_options = parser.run();

  po::variables_map vm;
  po::store(parsed_options, vm);
  po::notify(vm);

  // TODO: Read from stdin
  if (vm.count("help") || vm["input"].empty()) {
    std::cerr << NO_INPUT << std::endl;
    std::cout << desc << std::endl;
    return 2;
  } else {

    if (vm.count("algorithm")) {
      std::string chosenAlgorithm = vm["algorithm"].as<std::string>();
      std::transform(chosenAlgorithm.begin(), chosenAlgorithm.end(), chosenAlgorithm.begin(),
      [](unsigned char c) {
        return std::tolower(c);
      });
      if (input.algorithms.count(chosenAlgorithm) > 0) {
        input.algorithm = input.algorithms[chosenAlgorithm];
      } else {
        std::cerr << ALGO_NOT_SET << std::endl;
        return 1;
      }
    } else {
      std::cerr << ALGO_NOT_SET << std::endl;
      return 1;
    }

    if (vm.count("output")) {
      input.outputFile = vm["output"].as<std::string>();
      input.output_to_stdout = false;
    } else {
      input.output_to_stdout = true;
    }
  }
  return 0;
}
