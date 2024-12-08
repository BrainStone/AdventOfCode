#include <unordered_map>
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
	int possible_new_obstructions = 0;
	int dir = 0;
	std::array<point, 4> dirs{point{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	std::unordered_map<point, unsigned short> visited_pos;

	letter_grid grid;
	input >> grid;

	const point start = grid.find('^');
	point cur;

	const size_t height = grid.height();
	const size_t width = grid.width();

	for (point obs{0, 0}; obs[0] < height; ++obs[0]) {
		for (obs[1] = 0; obs[1] < width; ++obs[1]) {
			if (grid[obs] != '.') continue;

			grid[obs] = '#';
			cur = start;
			dir = 0;
			visited_pos.clear();

			while (grid.is_valid_point(cur)) {
				if (grid[cur] == '#') {
					cur -= dirs[dir];
					dir = (dir + 1) % 4;
					continue;
				}

				// We found an infinite loop if we visited a position 5 times
				// The explanation here is that through regular pathing we can be at the location at most 4 times (4
				// different directions)
				if (++visited_pos[cur] > 4) {
					++possible_new_obstructions;
					break;
				}

				cur += dirs[dir];
			}

			grid[obs] = '.';
		}
	}

	return possible_new_obstructions;
}

REGISTER_DAY(6)
