#include "day3.hpp"

#include <limits>

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

std::string day3_1(std::istream& input) {
	int prod_sum = 0;
	int num1, num2;
	std::string instruction;
	// "ul(" = 3, 3 digits, "," = 1, 3 digits -> 10
	constexpr size_t max_chars = 10;

	while (true) {
	loop_start:
		if (!input) break;

		// Reset stream to one character further than we last started
		// This is necessary, because we might have read past the next m
		input.seekg(-(int)instruction.size(), std::ios::cur);

		input.ignore(max_size, 'm');

		instruction.resize(max_chars);
		input.get(instruction.data(), max_chars + 1, ')');
		instruction.resize(input.gcount());

		if (!input || input.peek() != ')' || !instruction.starts_with("ul(")) goto loop_start;

		auto it = instruction.begin() + 3;
		const auto end = instruction.end();
		num1 = 0;

		for (size_t i = 0; i < 3; ++i) {
			if (*it == ',') {
				if (i > 0) {
					// We have digits and found the comma, continue to next number
					break;
				} else {
					// Immediately a comma, no number, continue reading
					goto loop_start;
				}
			} else if (std::isdigit(*it)) {
				num1 = num1 * 10 + (*it - '0');
			} else {
				// Nonsense character, continue reading
				goto loop_start;
			}

			++it;
		}

		if (*(it++) != ',') goto loop_start;

		num2 = 0;

		for (size_t i = 0; i < 3; ++i) {
			if (it == end) {
				if (i > 0) {
					// We have digits and found the end of string, continue to calculation
					break;
				} else {
					// Immediately end of string, no number, continue reading
					goto loop_start;
				}
			} else if (std::isdigit(*it)) {
				num2 = num2 * 10 + (*it - '0');
			} else {
				// Nonsense character, continue reading
				goto loop_start;
			}

			++it;
		}

		prod_sum += num1 * num2;
	}

	return std::to_string(prod_sum);
}

std::string day3_2(std::istream& input) {}
