#include <cinttypes>
#include <vector>

#include "../registry.hpp"

template <typename T>
constexpr bool bit_set(const T& num, unsigned short idx) {
	return (num >> idx) & 1;
}

template <typename T>
constexpr bool in_bounds(const T& value, const T& low, const T& high) {
	return (value >= low) && (value <= high);
}

long long day7_1(std::istream& input) {
	long long sum = 0;
	long long target;
	std::vector<int> values;
	std::uint64_t op_mask;
	std::uint64_t max_mask;

	int num;
	long long cur;

	while (in_bounds<int>(input.peek(), '0', '9') && input.good()) {
		input >> target;
		input.ignore();

		values.clear();

		while (input.peek() != '\n' && input.good()) {
			input >> num;
			values.push_back(num);
		}

		input.ignore();
		max_mask = 1 << values.size();

		for (op_mask = 0; op_mask < max_mask; ++op_mask) {
			cur = values[0];

			for (size_t i = 1; i < values.size(); ++i) {
				if (bit_set(op_mask, i - 1)) {
					cur *= values[i];
				} else {
					cur += values[i];
				}

				if (cur > target) break;
			}

			if (cur == target) {
				sum += target;
				break;
			}
		}
	}

	return sum;
}

int day7_2(std::istream& input) {
	return 0;
}

REGISTER_DAY(7)
