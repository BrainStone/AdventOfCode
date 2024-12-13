#include <algorithm>
#include <list>
#include <ranges>

#include "../registry.hpp"

constexpr int EMPTY = -1;

void read_disk(std::istream& input, const std::function<void(int, int)>& disk_processor) {
	int id = 0;
	int count;
	bool empty = false;

	while (true) {
		count = input.get() - '0';
		if (!input.good()) break;
		if (!(count >= 0 && count <= 9)) continue;

		disk_processor(empty ? EMPTY : id, count);

		empty = !empty;
		if (empty) ++id;
	}
}

void append_to_vector(std::vector<int>& vec, int val, int count) {
	std::ranges::for_each(std::views::repeat(val, count), [&vec](auto val) { vec.push_back(val); });
}

long long calculate_checksum(const std::vector<int>& disk) {
	long long checksum = 0;

	for (int i = 0; i < disk.size(); ++i) {
		if (disk[i] == EMPTY) continue;

		checksum += i * disk[i];
	}

	return checksum;
}

long long day9_1(std::istream& input) {
	std::vector<int> disk;

	read_disk(input, [&](int id, int count) { append_to_vector(disk, id, count); });

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
	// Representing the disk in a compressed format, the pair represents ID and count
	std::list<std::pair<int, int>> compact_disk;

	read_disk(input, [&](int id, int count) {
		if (count > 0) compact_disk.emplace_back(id, count);
	});

	const auto rend = compact_disk.rend();
	auto back = compact_disk.rbegin();
	while (back->first == EMPTY) ++back;
	int move_id = back->first;

	for (; back != rend; ++back) {
		if (back->first != move_id) continue;
		--move_id;

		// Search from the beginning of the list up to current search pointer (reversing a backwards iterator creates a
		// forward iterator)
		auto fitting_range = std::ranges::find_if(
		    std::ranges::subrange{back, rend} | std::views::reverse,
		    [count = back->second](const auto& entry) { return entry.first == EMPTY && entry.second >= count; });

		if (fitting_range == back.base()) continue;

		compact_disk.insert(fitting_range, *back);
		if (fitting_range->second == back->second) {
			compact_disk.erase(fitting_range);
		} else {
			fitting_range->second -= back->second;
		}

		// auto before_back = std::next(back);
		auto before_back = std::next(back);

		if ((before_back != rend) && (before_back->first == EMPTY)) {
			before_back->second += back->second;
			// Weird stuff happens when erasing with backwards iterators
			// - You erase the element *after* it.
			// - The current pointer invalidates and the iterator that would point to the element you wanted to delete
			//   now points to the element before it (what you called the erase call with) This has to do with the fact
			//   that.
			// backwards iterators are one off essentially. Really weird behavior, but works fine
			compact_disk.erase(before_back.base());
		} else {
			back->first = EMPTY;
		}

		auto after_back = std::prev(back);
		if ((after_back != rend) && (after_back->first == EMPTY)) {
			back->second += after_back->second;
			// Same weirdness, we delete the element after the pointer. The current pointer invalidates and the one
			// pointing to element after now points to the current, so we swap it in the end.
			compact_disk.erase(back.base());
			back = after_back;
		}
	}

	std::vector<int> disk;

	for (const auto& [id, length] : compact_disk) {
		append_to_vector(disk, id, length);
	}

	return calculate_checksum(disk);
}

REGISTER_DAY(9)
