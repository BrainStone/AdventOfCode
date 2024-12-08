#include "day5.hpp"

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

std::string day5_1(std::istream& input) {
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

std::string day5_2(std::istream& input) {
	return "";
}
