#include "solutions/day1_1.hpp"
#include "util.hpp"

#include <filesystem>
#include <iostream>

int main() {
  // Change working dir to be relative to ourselves
  std::filesystem::path exec{__FILE__};
  std::filesystem::path exec_dir{exec.parent_path()};

  std::filesystem::current_path(exec_dir);
  
  std::cout << day1_1(*open_input("day1_1"));

  return 0;
}