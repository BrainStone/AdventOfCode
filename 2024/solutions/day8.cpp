#include <unordered_map>
#include <unordered_set>

#include "../registry.hpp"
#include "../util.hpp"

template <typename Iterator>
class distinct_ordered_pairs {
public:
	distinct_ordered_pairs(Iterator begin, Iterator end) : begin_(begin), end_(end) {}

	class iterator_wrapper {
	public:
		iterator_wrapper(Iterator first, Iterator second, Iterator begin, Iterator end)
		    : first_(first), second_(second), begin_(begin), end_(end) {
			if (first_ == second_ && first_ != end_) {
				advance_pair();
			}
		}

		bool operator!=(const iterator_wrapper& other) const {
			return first_ != other.first_ || second_ != other.second_;
		}

		iterator_wrapper& operator++() {
			advance_pair();

			return *this;
		}

		std::pair<typename std::iterator_traits<Iterator>::value_type,
		          typename std::iterator_traits<Iterator>::value_type>
		operator*() const {
			return {*first_, *second_};
		}

	private:
		Iterator first_;
		Iterator second_;
		const Iterator begin_;
		const Iterator end_;

		void advance_pair() {
			do {
				if (second_ == end_) {
					++first_;

					if (first_ != end_) {
						second_ = begin_;
					}
				} else {
					++second_;
				}
			} while (first_ != end_ && (second_ == end_ || first_ == second_));
		}
	};

	[[nodiscard]] iterator_wrapper begin() const {
		return {begin_, begin_, begin_, end_};
	}
	[[nodiscard]] iterator_wrapper end() const {
		return {end_, end_, begin_, end_};
	}

private:
	const Iterator begin_;
	const Iterator end_;
};

int count_antinodes(std::istream& input, const std::function<void(const letter_grid&, std::unordered_set<point>&,
                                                                  const point&, const point&)>& antinode_processor) {
	std::unordered_multimap<char, point> antennas;
	std::unordered_set<point> antinodes;
	letter_grid grid;
	input >> grid;

	const size_t width = grid.width();
	const size_t height = grid.height();
	char node;

	for (point cur{0, 0}; cur[0] < height; ++cur[0]) {
		for (cur[1] = 0; cur[1] < width; ++cur[1]) {
			node = grid[cur];

			if (node == '.') continue;

			antennas.emplace(node, cur);
		}
	}

	for (auto it = antennas.begin(); it != antennas.end();) {
		auto end = antennas.equal_range(it->first).second;

		for (const auto& [node1_pair, node2_pair] : distinct_ordered_pairs(it, end)) {
			const auto& node1 = node1_pair.second;
			const auto& node2 = node2_pair.second;

			antinode_processor(grid, antinodes, node1, node2);
		}

		it = end;
	}

	return (int)antinodes.size();
}

int day8_1(std::istream& input) {
	return count_antinodes(input, [](const auto& grid, auto& antinodes, const auto& node1, const auto& node2) {
		const point antinode = (2 * node1) - node2;

		if (grid.is_valid_point(antinode)) antinodes.insert(antinode);
	});
}

int day8_2(std::istream& input) {
	return count_antinodes(input, [](const auto& grid, auto& antinodes, const auto& node1, const auto& node2) {
		const point difference = node1 - node2;

		for (point antinode = node1; grid.is_valid_point(antinode); antinode += difference) {
			antinodes.insert(antinode);
		}
	});
}

REGISTER_DAY(8)
