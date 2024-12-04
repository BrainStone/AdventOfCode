#include "day2.hpp"

#include <algorithm>
#include <limits>
#include <vector>

#include "../range_helper.hpp"

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

std::string day2_1(std::istream& input) {
	int safe_reports = 0;

	int last_val, cur_val;
	int diff;
	bool increasing;

	while (true) {
	next_report:

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

template <ranges::range_of<int> R>
    requires std::ranges::viewable_range<R>
bool is_report_safe(R&& report) {
	auto differences = report | std::views::pairwise_transform([](int a, int b) { return b - a; });

	return std::ranges::all_of(differences, [](int val) { return val >= 1 && val <= 3; }) ||
	       std::ranges::all_of(differences, [](int val) { return val <= -1 && val >= -3; });
}

std::string day2_2(std::istream& input) {
	// Instead of adjusting the above code, we're changing the approach. Mainly because due to edge cases the above code
	// would be a nightmare to adjust. But also because solving problems differently is fun.
	int safe_reports = 0;
	std::vector<int> report;
	int val;

	while (true) {
		report.clear();

		input >> val;

		if (!input) break;

		report.push_back(val);

		while (input.peek() != '\n') {
			input >> val;
			report.push_back(val);
		}

		const size_t report_length = report.size();

		for (size_t i = 0; i < report_length; ++i) {
			if (is_report_safe(report | views::skip_nth(i))) {
				++safe_reports;
				break;
			}
		}
	}

	return std::to_string(safe_reports);
}
