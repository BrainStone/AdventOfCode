#include <list>

#include "../registry.hpp"
#include "../util.hpp"

std::list<long> read_numbers(std::istream& input) {
	long number;
	std::list<long> out;

	while (input >> number) {
		out.push_back(number);
	}

	return out;
}

constexpr size_t count_digits(long num) {
	size_t digits = 0;

	do {
		num /= 10;
		++digits;
	} while (num != 0);

	return digits;
}

constexpr std::pair<long, long> split_number(long num, size_t digits) {
	constexpr std::array factors{1L,
	                             10L,
	                             100L,
	                             1000L,
	                             10000L,
	                             100000L,
	                             1000000L,
	                             10000000L,
	                             100000000L,
	                             1000000000L,
	                             10000000000L,
	                             100000000000L,
	                             1000000000000L,
	                             10000000000000L,
	                             100000000000000L,
	                             1000000000000000L,
	                             10000000000000000L,
	                             100000000000000000L,
	                             1000000000000000000L};
	const long factor = factors[digits / 2];

	return {num / factor, num % factor};
}

constexpr std::pair<long, long> split_number(long num) {
	return split_number(num, count_digits(num));
}

// NOLINTNEXTLINE(*-no-recursion)
size_t calculate_stones(long long num, unsigned short steps) {
	using steps_t = typeof(steps);
	using map_key_t = std::pair<typeof(num), steps_t>;
	static std::unordered_map<map_key_t, size_t> cache;

	// No more steps to go, it's just the one stone
	if (steps == 0) return 1;

	const map_key_t cache_key{num, steps};

	// Check the cache
	if (auto search = cache.find(cache_key); search != cache.end()) return search->second;

	// Calculate the previous steps to fill the cache
	for (unsigned short i = 1; i < steps; ++i) {
		calculate_stones(num, i);
	}

	const steps_t steps_before = steps - 1;
	size_t sum;

	if (num == 0) {
		sum = calculate_stones(1, steps_before);
	} else if (size_t digits = count_digits(num); digits % 2 == 0) {
		const auto [front, back] = split_number(num, digits);

		sum = calculate_stones(front, steps_before);
		sum += calculate_stones(back, steps_before);
	} else {
		sum = calculate_stones(num * 2024, steps_before);
	}

	cache.emplace(cache_key, sum);

	return sum;
}

int day11_1(std::istream& input) {
	constexpr int ITERATIONS = 25;

	std::list<long> numbers = read_numbers(input);
	const auto end = numbers.end();
	size_t digits;

	for (int i = 0; i < ITERATIONS; ++i) {
		for (auto it = numbers.begin(); it != end; ++it) {
			if (*it == 0) {
				*it = 1;
			} else if ((digits = count_digits(*it)) % 2 == 0) {
				const auto [front, back] = split_number(*it, digits);

				it = numbers.insert(it, front);
				++it;
				*it = back;
			} else {
				*it *= 2024;
			}
		}
	}

	return (int)numbers.size();
}

size_t day11_2(std::istream& input) {
	constexpr int ITERATIONS = 75;

	size_t sum = 0;
	std::list<long> numbers = read_numbers(input);

	for (long num : numbers) {
		sum += calculate_stones(num, ITERATIONS);
	}

	return sum;
}

REGISTER_DAY(11)
