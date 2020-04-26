#include <boost/program_options.hpp>
#include <iostream>
#include <string>

#include "read_flags.hpp"

namespace po = boost::program_options;

// Messages
char USAGE[] =
"Usage: pathFinding [--algorithm=<algorithm>] [--output=<file>] FILE\nOptions";
char HELP[] = "prompt this help.";
char ALGO[] = "choose algorithm:\n- dijkstra (default)";
char OUTPUT[] = "output file. Default to stdout.";
char INPUT[] = "input map file.";

void read_flags(int argc, char *argv[]) {
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

  if (vm.count("help") || vm["input"].empty()) {
    std::cout << desc << std::endl;
  } else {

    if (vm.count("algorithm")) {
      std::cout << "Algorithm was set to "
                << vm["algorithm"].as<std::string>() << std::endl;
    } else {
      std::cout << "Compression level was not set." << std::endl;
    }

    if (vm.count("output")) {
      std::cout << "Output file set to "
                << vm["output"].as<std::string>() << std::endl;
    } else {
      std::cout << "No output file. Passing to stdout." << std::endl;
    }
  }
}
