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

	return {new std::ifstream{problem_file}, [](std::istream* ptr) { delete ptr; }};
}

point operator+(const point& lhs, const point& rhs) {
	return {lhs[0] + rhs[0], lhs[1] + rhs[1]};
}

point& operator+=(point& lhs, const point& rhs) {
	lhs[0] += rhs[0];
	lhs[1] += rhs[1];

	return lhs;
}

point operator-(const point& lhs, const point& rhs) {
	return {lhs[0] - rhs[0], lhs[1] - rhs[1]};
}

point& operator-=(point& lhs, const point& rhs) {
	lhs[0] -= rhs[0];
	lhs[1] -= rhs[1];

	return lhs;
}

point operator*(const point& lhs, long long rhs) {
	return {lhs[0] * rhs, lhs[1] * rhs};
}

point& operator*=(point& lhs, long long rhs) {
	lhs[0] *= rhs;
	lhs[1] *= rhs;

	return lhs;
}

std::ostream& operator<<(std::ostream& os, const point& rhs) {
	os << '(' << rhs[0] << ',' << rhs[1] << ')';

	return os;
}

void letter_grid::check_line(const std::string& line) const {
	if (grid.empty()) return;

	const size_t width = this->width();
	const size_t length = line.size();

	if (length != width)
		throw std::length_error("Expected length of line to be " + std::to_string(width) + " but it was " +
		                        std::to_string(length));
}

letter_grid::letter_grid() : grid() {}

void letter_grid::add_line(const std::string& line) {
	check_line(line);

	grid.push_back(line);
}

void letter_grid::add_line(std::string&& line) {
	check_line(line);

	grid.push_back(line);
}

[[nodiscard]] size_t letter_grid::width() const {
	if (grid.empty()) return 0;

	return grid[0].size();
}

[[nodiscard]] size_t letter_grid::height() const {
	return grid.size();
}

[[nodiscard]] std::string& letter_grid::operator[](size_t row) {
	return grid[row];
}

[[nodiscard]] const std::string& letter_grid::operator[](size_t row) const {
	return grid[row];
}

[[nodiscard]] char& letter_grid::operator[](const point& position) {
	return grid[position[0]][position[1]];
}

[[nodiscard]] const char& letter_grid::operator[](const point& position) const {
	return grid[position[0]][position[1]];
}

[[nodiscard]] bool letter_grid::is_valid_point(const point& position) const {
	return (position[0] >= 0 && position[0] < this->height()) && (position[1] >= 0 && position[1] < this->width());
}

point letter_grid::find(char c) const {
	const size_t height = this->height();
	size_t res;

	for (point cur{0, 0}; cur[0] < height; ++cur[0]) {
		res = grid[cur[0]].find(c);

		if (res != std::string::npos) {
			cur[1] = (long long)res;

			return cur;
		}
	}

	return {-1, -1};
}

std::istream& operator>>(std::istream& is, letter_grid& grid) {
	std::string line;

	while (is.good()) {
		std::getline(is, line);

		if (line.empty()) break;

		grid.add_line(std::move(line));
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const letter_grid& grid) {
	const size_t rows = grid.height();

	for (size_t row = 0; row < rows; ++row) {
		os << grid[row] << '\n';
	}

	return os;
}
