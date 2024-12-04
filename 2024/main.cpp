#include "solutions/day1_1.hpp"
#include "util.hpp"

#include <filesystem>
#include <iostream>
#include <map>

// Mapping of all solution
const std::map<std::string, std::function<std::string(std::istream &)>>
    solutions{{"1_1", day1_1}, {"1_2", day1_1}};

int main() {
  // Change working dir to be relative to ourselves
  std::filesystem::path exec{__FILE__};
  std::filesystem::path exec_dir{exec.parent_path()};

  std::filesystem::current_path(exec_dir);

  std::string problem;
  std::cout << "Which problem to run (format <day>_<problem>, like 12_2): ";
  std::cin >> problem;
  std::cout << std::endl;

  std::string solution{solutions.at(problem)(*open_input(problem))};

  std::cout << "\n\nSolution for day" << problem << ": " << solution;

  return 0;
}