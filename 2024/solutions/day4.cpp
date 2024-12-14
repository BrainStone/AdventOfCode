#include <vector>

#include "../registry.hpp"
#include "../util.hpp"

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

int day4_1(std::istream& input) {
	letter_grid grid;
	input >> grid;

	constexpr std::string_view search{"XMAS"};
	constexpr std::array<point, 8> dirs{point{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

	int count = 0;

	for (point cur{0, 0}; grid.is_valid_point(cur); cur = grid.next_point(cur)) {
		for (const point& dir : dirs) {
			if (contains_needle_at(grid, search, cur, dir)) ++count;
		}
	}

	return count;
}

int day4_2(std::istream& input) {
	letter_grid grid;
	input >> grid;

	constexpr std::string_view search{"XMAS"};
	const size_t width = grid.width();
	const size_t height = grid.height();
	constexpr point dir_ne{NORTH + EAST};
	constexpr point dir_se{SOUTH + EAST};
	constexpr point dir_nw{NORTH + WEST};
	constexpr point dir_sw{SOUTH + WEST};

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

	return count;
}

REGISTER_DAY(4)
