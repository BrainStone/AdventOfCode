#include "day1.hpp"

#include <algorithm>
#include <tuple>
#include <vector>

std::tuple<std::vector<int>, std::vector<int>> read_lists(std::istream& input, bool sort = false) {
	std::vector<int> list1, list2;
	int num1, num2;

	while (true) {
		input >> num1 >> num2;

		if (!input) break;

		list1.push_back(num1);
		list2.push_back(num2);
	}

	if (sort) {
		std::sort(list1.begin(), list1.end());
		std::sort(list2.begin(), list2.end());
	}

	return {list1, list2};
}

std::string day1_1(std::istream& input) {
	auto [list1, list2] = read_lists(input, true);

	int diff = 0;

	for (size_t i = 0; i < list1.size(); ++i) {
		diff += std::abs(list1[i] - list2[i]);
	}

	return std::to_string(diff);
}

std::string day1_2(std::istream& input) {
	auto [list1, list2] = read_lists(input, true);

	int similarity = 0;
	auto it = list2.begin();
	auto end = list2.end();

	for (int val : list1) {
		while (*it < val) {
			if (++it == end) goto end;
		}

		while (*it == val) {
			similarity += val;

			if (++it == end) goto end;
		}
	}

end:

	return std::to_string(similarity);
}
