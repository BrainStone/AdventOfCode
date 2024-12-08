#include "day5.hpp"

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::string day5_1(std::istream& input) {
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

	int sum = 0;
	int read_page;
	std::vector<int> pages;
	std::unordered_set<int> seen;

	while (input.peek() != '\n' && input.good()) {
		pages.clear();

		do {
			input >> read_page;
			pages.push_back(read_page);
		} while (input.get() != '\n');

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
	}

	return std::to_string(sum);
}

std::string day5_2(std::istream& input) {
	return "";
}
