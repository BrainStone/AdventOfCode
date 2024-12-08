#include "day4.hpp"

#include <array>
#include <vector>

using point = typename std::array<long long, 2>;

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

class letter_grid {
private:
	std::vector<std::string> grid;

	void check_line(const std::string& line) const {
		if (grid.empty()) return;

		const size_t width = this->width();
		const size_t length = line.size();

		if (length != width)
			throw std::length_error("Expected length of line to be " + std::to_string(width) + " but it was " +
			                        std::to_string(length));
	}

public:
	letter_grid() : grid() {}

	void add_line(const std::string& line) {
		check_line(line);

		grid.push_back(line);
	}

	void add_line(std::string&& line) {
		check_line(line);

		grid.push_back(line);
	}

	[[nodiscard]] size_t width() const {
		if (grid.empty()) return 0;

		return grid[0].size();
	}

	[[nodiscard]] size_t height() const {
		return grid.size();
	}

	[[nodiscard]] std::string& operator[](size_t row) {
		return grid[row];
	}

	[[nodiscard]] const std::string& operator[](size_t row) const {
		return grid[row];
	}

	[[nodiscard]] char& operator[](const point& position) {
		return grid[position[0]][position[1]];
	}

	[[nodiscard]] const char& operator[](const point& position) const {
		return grid[position[0]][position[1]];
	}

	[[nodiscard]] bool is_valid_point(const point& position) const {
		return (position[0] >= 0 && position[0] < this->height()) && (position[1] >= 0 && position[1] < this->width());
	}
};

std::istream& operator>>(std::istream& is, letter_grid& grid) {
	std::string line;

	while (is.good()) {
		std::getline(is, line);

		if (line.empty()) break;

		grid.add_line(std::move(line));
	}

	return is;
}

bool contains_needle_at(const letter_grid& grid, const std::string_view& needle, const point& loc, const point& dir) {
	const size_t length = needle.size();
	const long long offset = (long long)length - 1;

	const point end_point = loc + (dir * offset);

	if (!(grid.is_valid_point(loc) && grid.is_valid_point(end_point))) return false;

	point pos = loc;

	for (size_t i = 0; i < length; ++i, pos += dir) {
		if (grid[pos] != needle[i]) return false;
	}

	return true;
}

std::string day4_1(std::istream& input) {
	letter_grid grid;
	input >> grid;

	constexpr std::string_view search{"XMAS"};
	const size_t width = grid.width();
	const size_t height = grid.height();
	constexpr std::array<point, 8> dirs{point{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

	int count = 0;

	for (point cur{0, 0}; cur[0] < height; ++cur[0]) {
		for (cur[1] = 0; cur[1] < width; ++cur[1]) {
			for (const point& dir : dirs) {
				if (contains_needle_at(grid, search, cur, dir)) ++count;
			}
		}
	}

	return std::to_string(count);
}

std::string day4_2(std::istream& input) {
	letter_grid grid;
	input >> grid;

	constexpr std::string_view search{"XMAS"};
	const size_t width = grid.width();
	const size_t height = grid.height();
	constexpr point dir_ne{-1, 1};
	constexpr point dir_se{1, 1};
	constexpr point dir_nw{-1, -1};
	constexpr point dir_sw{1, -1};

	int count = 0;

	for (point cur{1, 1}; cur[0] < height - 1; ++cur[0]) {
		for (cur[1] = 1; cur[1] < width - 1; ++cur[1]) {
			if (grid[cur] != 'A') continue;
			if (!((grid[cur + dir_ne] == 'M' && grid[cur + dir_sw] == 'S') ||
			      (grid[cur + dir_ne] == 'S' && grid[cur + dir_sw] == 'M')))
				continue;
			if (!((grid[cur + dir_nw] == 'M' && grid[cur + dir_se] == 'S') ||
			      (grid[cur + dir_nw] == 'S' && grid[cur + dir_se] == 'M')))
				continue;

			++count;
		}
	}

	return std::to_string(count);
}
