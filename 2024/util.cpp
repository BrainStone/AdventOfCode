#include "util.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

wrapped_istream open_input(const std::string &problem) {
  std::filesystem::path target_file{"inputs/day" + problem + ".txt"};

  if (is_regular_file(target_file)) {
    return {new std::ifstream{target_file},
            [](std::istream *ptr) { delete ptr; }};
  } else {
    std::cerr << "Could not find input file " << target_file
              << "! Falling back to manual input:" << std::endl;

    return {&std::cin, [](std::istream *) {}};
  }
}
