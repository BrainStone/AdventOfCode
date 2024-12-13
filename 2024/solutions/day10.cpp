#include <unordered_set>

#include "../registry.hpp"
#include "../util.hpp"

// NOLINTNEXTLINE(*-no-recursion)
void ascend(const letter_grid& grid, std::unordered_set<point>& peaks, const point& pos) {
	constexpr std::array<point, 4> dirs{point{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

	const char height = grid[pos];

	// We found a peak, add it to the list
	if (height == '9') {
		peaks.insert(pos);

		return;
	}

	const char next_height = (char)(height + 1);

	for (const point& dir : dirs) {
		const point new_pos = pos + dir;

		if (grid.is_valid_point(new_pos) && (grid[new_pos] == next_height)) ascend(grid, peaks, new_pos);
	}
}

int day10_1(std::istream& input) {
	int sum = 0;
	std::unordered_set<point> peaks;
	letter_grid grid;
	input >> grid;

	for (point pos = grid.find('0'); grid.is_valid_point(pos); pos = grid.find('0', grid.next_point(pos))) {
		peaks.clear();

		ascend(grid, peaks, pos);

		sum += (int)peaks.size();
	}

	return sum;
}

int day10_2(std::istream& input) {
	return 0;
}

REGISTER_DAY(10)
