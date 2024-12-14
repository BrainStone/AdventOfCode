#include <queue>
#include <unordered_set>

#include "../registry.hpp"
#include "../util.hpp"

int day12_1(std::istream& input) {
	letter_grid grid;
	input >> grid;

	int total_cost = 0;
	char current_crop;
	int perimeter;
	int area;
	std::unordered_set<point> visited_plots;
	std::unordered_set<point> plots_to_explore;

	for (point plot{0, 0}; grid.is_valid_point(plot); plot = grid.next_point(plot)) {
		if (visited_plots.contains(plot)) continue;

		current_crop = grid[plot];
		perimeter = 0;
		area = 0;
		plots_to_explore.insert(plot);

		for (point explore_plot; !plots_to_explore.empty();) {
			explore_plot = plots_to_explore.extract(plots_to_explore.begin()).value();
			visited_plots.insert(explore_plot);
			++area;

			for (const point& dir : CARDINAL_DIRS) {
				const point new_plot = explore_plot + dir;

				if (grid.is_valid_point(new_plot) && (grid[new_plot] == current_crop)) {
					if (!visited_plots.contains(new_plot)) plots_to_explore.insert(new_plot);
				} else {
					++perimeter;
				}
			}
		}

		total_cost += perimeter * area;
	}

	return total_cost;
}

int day12_2(std::istream& input) {
	return 0;
}

REGISTER_DAY(12)
