#include "util.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

wrapped_istream open_input(const std::string& problem) {
	std::string day = problem.substr(0, problem.find('_'));

	std::filesystem::path specific_problem_file{"inputs/day" + problem + ".txt"};
	std::filesystem::path day_problem_file{"inputs/day" + day + ".txt"};

	std::filesystem::path problem_file;

	if (is_regular_file(specific_problem_file)) {
		problem_file = specific_problem_file;
	} else if (is_regular_file(day_problem_file)) {
		problem_file = day_problem_file;
	} else {
		std::cerr << "Could not find input files " << specific_problem_file << " or " << day_problem_file
		          << "! Falling back to manual input:" << std::endl;

		return {&std::cin, [](std::istream*) {}};
	}
	
	std::cout << problem_file << std::endl;

	return {new std::ifstream{problem_file}, [](std::istream* ptr) { delete ptr; }};
}
