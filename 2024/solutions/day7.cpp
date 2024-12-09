#include <cinttypes>
#include <vector>

#include "../registry.hpp"

template <std::integral T>
constexpr bool bit_set(const T& num, unsigned short idx) {
	return (num >> idx) & 1;
}

template <std::integral T>
constexpr bool in_bounds(const T& value, const T& low, const T& high) {
	return (value >= low) && (value <= high);
}

template <std::integral T>
constexpr T concat(const T& lhs, const T& rhs) {
	T result = lhs;
	T temp = rhs;

	while (temp != 0) {
		result *= 10;
		temp /= 10;
	}

	result += rhs;

	return result;
}

void process_input(std::istream& input,
                   const std::function<void(long long, const std::vector<int>&)>& equation_processor) {
	long long target;
	std::vector<int> values;

	int num;

	while (in_bounds<int>(input.peek(), '0', '9') && input.good()) {
		input >> target;
		input.ignore();

		values.clear();

		while (input.peek() != '\n' && input.good()) {
			input >> num;
			values.push_back(num);
		}

		input.ignore();

		equation_processor(target, values);
	}
}

long long day7_1(std::istream& input) {
	long long sum = 0;

	process_input(input, [&](long long target, const std::vector<int>& values) {
		const std::uint64_t max_mask = 1 << values.size();
		long long cur;

		for (std::uint64_t op_mask = 0; op_mask < max_mask; ++op_mask) {
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
	});

	return sum;
}

enum operation { add, mul, cat };

void next_operations_set(std::vector<operation>& operations) {
	const size_t size = operations.size();

	for (size_t i = 0; i < size; ++i) {
		switch (operations[i]) {
		case operation::add:
			operations[i] = operation::mul;
			return;
		case operation::mul:
			operations[i] = operation::cat;
			return;
		case operation::cat:
			operations[i] = operation::add;
			break;
		}
	}
}

long long day7_2(std::istream& input) {
	long long sum = 0;

	process_input(input, [&](long long target, const std::vector<int>& values) {
		const size_t val_count = values.size();
		long long cur;

		for (std::vector<operation> operations{val_count, operation::add}; operations[val_count - 1] == operation::add;
		     next_operations_set(operations)) {
			cur = values[0];

			for (size_t i = 1; i < values.size(); ++i) {
				switch (operations[i - 1]) {
				case operation::add:
					cur += values[i];
					break;
				case operation::mul:
					cur *= values[i];
					break;
				case operation::cat:
					cur = concat<long long>(cur, values[i]);
					break;
				}

				if (cur > target) break;
			}

			if (cur == target) {
				sum += target;
				break;
			}
		}
	});

	return sum;
}

REGISTER_DAY(7)
