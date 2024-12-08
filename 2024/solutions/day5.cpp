#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../registry.hpp"

void process_input(
    std::istream& input,
    const std::function<void(const std::unordered_multimap<int, int>&, const std::vector<int>&)>& pages_processor) {
	std::unordered_multimap<int, int> rules;

	int before, after;

	while (input.peek() != '\n') {
		input >> before;
		input.ignore();
		input >> after;
		input.ignore();

		rules.emplace(before, after);
	}

	// Skip empty line
	input.ignore();

	int page;
	std::vector<int> pages;

	while (input.peek() != '\n' && input.good()) {
		pages.clear();

		do {
			input >> page;
			pages.push_back(page);
		} while (input.get() != '\n');

		pages_processor(rules, pages);
	}
}

int day5_1(std::istream& input) {
	int sum = 0;
	std::unordered_set<int> seen;

	process_input(input, [&](const auto& rules, const auto& pages) {
		seen.clear();

		for (int page : pages) {
			for (auto [it, rangeEnd] = rules.equal_range(page); it != rangeEnd; ++it) {
				// We've seen the page before, which isn't allowed!
				if (seen.contains(it->second)) goto invalid_pages;
			}

			seen.insert(page);
		}

		sum += pages[pages.size() / 2];

	invalid_pages:
	});

	return std::to_string(sum);
}

// I'm sure there's a more efficient solution than just swapping the pages that violate a rule and then trying again
// until the pages are in order. But it's by far the easiest to implement.
int day5_2(std::istream& input) {
	int sum = 0;
	bool changed_order;
	std::unordered_map<int, std::vector<int>::iterator> seen;

	process_input(input, [&](const auto& rules, auto pages) {
		changed_order = false;

	check_for_out_of_order:
		seen.clear();

		for (auto page = pages.begin(); page != pages.end(); ++page) {
			for (auto [it, rangeEnd] = rules.equal_range(*page); it != rangeEnd; ++it) {
				// We've seen the page before, which isn't allowed! Reorder and start over
				if (seen.contains(it->second)) {
					std::iter_swap(page, seen[it->second]);
					changed_order = true;
					goto check_for_out_of_order;
				}
			}

			seen.emplace(*page, page);
		}

		if (changed_order) sum += pages[pages.size() / 2];
	});

	return sum;
}

REGISTER_DAY(5)
