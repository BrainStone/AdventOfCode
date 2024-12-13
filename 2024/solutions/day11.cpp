#include <list>

#include "../registry.hpp"

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

int day11_2(std::istream& input) {
	return 0;
}

REGISTER_DAY(11)
