#include <filesystem>
#include <iostream>
#include <map>

#include "solutions/day1.hpp"
#include "util.hpp"

// Mapping of all solution
const std::map<std::string, std::function<std::string(std::istream&)>> solutions{{"1_1", day1_1}, {"1_2", day1_1}};

int main(int argc, char** argv) {
	// Change working dir to be relative to ourselves
	std::filesystem::path exec{__FILE__};
	std::filesystem::path exec_dir{exec.parent_path()};

	std::filesystem::current_path(exec_dir);

	std::string problem;

	if (argc < 1) {
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
