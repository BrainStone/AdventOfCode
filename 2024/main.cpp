#include <filesystem>
#include <iostream>

#include "solutions/day1.hpp"
#include "solutions/day2.hpp"
#include "solutions/day3.hpp"
#include "util.hpp"

#define PROBLEM_DAY(problem) {#problem "_1", day##problem##_1}, {#problem "_2", day##problem##_2},

// Mapping of all solutions
const std::unordered_map<std::string, std::function<std::string(std::istream&)>> solutions{PROBLEM_DAY(1) PROBLEM_DAY(2)
                                                                                               PROBLEM_DAY(3)};

int main(int argc, char** argv) {
	// Change working dir to be relative to ourselves
	std::filesystem::path exec{__FILE__};
	std::filesystem::path exec_dir{exec.parent_path()};

	std::filesystem::current_path(exec_dir);

	std::string problem;

	if (argc <= 1) {
		std::cout << "Which problem to run (format <day>_<problem>, like 12_2): ";
		std::cin >> problem;
		std::cout << std::endl;
	} else {
		problem = argv[1];
		std::cout << "Selected problem day" << problem << " from CLI params." << std::endl;
	}

	std::string solution{solutions.at(problem)(*open_input(problem))};

	std::cout << "\n\nSolution for day" << problem << ": " << solution << std::endl;

	return 0;
}
