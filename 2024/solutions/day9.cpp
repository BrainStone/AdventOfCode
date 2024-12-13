#include <algorithm>
#include <ranges>

#include "../registry.hpp"

constexpr int EMPTY = -1;

std::vector<int> read_disk(std::istream& input) {
	std::vector<int> disk;

	int id = 0;
	int count;
	bool empty = false;

	while (true) {
		count = input.get() - '0';
		if (!input.good()) break;
		if (!(count >= 0 && count <= 9)) continue;

		std::ranges::for_each(std::views::repeat(empty ? EMPTY : id, count),
		                      [&disk](auto val) { disk.push_back(val); });

		empty = !empty;
		if (empty) ++id;
	}

	return disk;
}

long long calculate_checksum(const std::vector<int>& disk) {
	long long checksum = 0;

	for (int i = 0; i < disk.size(); ++i) {
		if (disk[i] == EMPTY) break;

		checksum += i * disk[i];
	}

	return checksum;
}

long long day9_1(std::istream& input) {
	long long checksum = 0;
	std::vector<int> disk = read_disk(input);

	auto front = disk.begin();
	auto back = disk.end();

	while (true) {
		--back;
		while (*front != EMPTY) ++front;

		if (front >= back) break;

		*front = *back;
		*back = EMPTY;
	}

	return calculate_checksum(disk);
}

long long day9_2(std::istream& input) {
	return 0;
}

REGISTER_DAY(9)
