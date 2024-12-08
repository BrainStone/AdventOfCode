#include <unordered_set>

#include "../registry.hpp"
#include "../util.hpp"

int day6_1(std::istream& input) {
	int dir = 0;
	std::array<point, 4> dirs{point{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	std::unordered_set<point> unique_pos;

	letter_grid grid;
	input >> grid;

	point cur = grid.find('^');

	while (grid.is_valid_point(cur)) {
		if (grid[cur] == '#') {
			cur -= dirs[dir];
			dir = (dir + 1) % 4;
			continue;
		}

		unique_pos.insert(cur);
		cur += dirs[dir];
	}

	return (int)unique_pos.size();
}

int day6_2(std::istream& input) {
	return 0;
}

REGISTER_DAY(6)
