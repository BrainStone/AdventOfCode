#include <unordered_set>

#include "../registry.hpp"
#include "../util.hpp"

int calculate_trail_scores(std::istream& input,
                           const std::function<int(const letter_grid&, const point&)>& point_rater) {
	int sum = 0;
	letter_grid grid;
	input >> grid;

	for (point pos = grid.find('0'); grid.is_valid_point(pos); pos = grid.find('0', grid.next_point(pos))) {
		sum += (int)point_rater(grid, pos);
	}

	return sum;
}

// NOLINTNEXTLINE(*-no-recursion)
void ascend(const letter_grid& grid, const point& pos, const std::function<void(const point&)>& peak_handler) {
	constexpr std::array<point, 4> dirs{point{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

	const char height = grid[pos];

	// We found a peak, handle it
	if (height == '9') {
		peak_handler(pos);

		return;
	}

	const char next_height = (char)(height + 1);

	for (const point& dir : dirs) {
		const point new_pos = pos + dir;

		if (grid.is_valid_point(new_pos) && (grid[new_pos] == next_height)) ascend(grid, new_pos, peak_handler);
	}
}

int day10_1(std::istream& input) {
	std::unordered_set<point> peaks;

	return calculate_trail_scores(input, [&](const letter_grid& grid, const point& pos) {
		peaks.clear();

		ascend(grid, pos, [&](const point& peak) { peaks.insert(peak); });

		return (int)peaks.size();
	});
}

int day10_2(std::istream& input) {
	return calculate_trail_scores(input, [](const letter_grid& grid, const point& pos) {
		int sum = 0;

		ascend(grid, pos, [&](const point& peak) { ++sum; });

		return sum;
	});
}

REGISTER_DAY(10)
