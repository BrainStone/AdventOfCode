#include "day2.hpp"

#include <limits>

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

std::string day2_1(std::istream& input) {
	int safe_reports = 0;
	int reports = 0;

	int last_val, cur_val;
	int diff;
	bool increasing;

	while (true) {
	next_report:

		++reports;
		input >> last_val;

		// Only check if reading failed, which means we reached the end of the list
		if (!input) break;

		// No further checks are necessary, because the data does indeed contain at least 2 values
		input >> cur_val;

		diff = std::abs(cur_val - last_val);

		if ((last_val == cur_val) || (diff > 3)) {
			// Unsafe report, skip to end of line
			input.ignore(max_size, '\n');
			goto next_report;
		}

		increasing = cur_val > last_val;

		while (input.peek() != '\n') {
			last_val = cur_val;
			input >> cur_val;

			diff = std::abs(cur_val - last_val);

			if (((increasing && (cur_val <= last_val)) || (!increasing && (cur_val >= last_val))) || (diff > 3)) {
				// Unsafe report, skip to end of line
				input.ignore(max_size, '\n');
				goto next_report;
			}
		}

		// No issues found in report, report is safe
		++safe_reports;
	}

	return std::to_string(safe_reports);
}

std::string day2_2(std::istream& input) {
	return "";
}
