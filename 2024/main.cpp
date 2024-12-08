#include <chrono>
#include <filesystem>
#include <iomanip>
#include <iostream>

#include "registry.hpp"
#include "util.hpp"

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

	const auto start = std::chrono::high_resolution_clock::now();
	std::string solution{solution_registry::instance().get_solution(problem)(*open_input(problem))};
	const auto end = std::chrono::high_resolution_clock::now();

	const std::chrono::duration<double> elapsed = end - start;
	std::cout << "\n\nSolution for day" << problem << ": " << solution << "\nTime elapsed: " << std::fixed
	          << std::setprecision(6) << elapsed << std::endl;

	return 0;
}
