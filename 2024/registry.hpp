#pragma once

#include <concepts>
#include <functional>
#include <istream>
#include <string>
#include <unordered_map>

class solution_registry {
public:
	using string_function = std::function<std::string(std::istream&)>;

	static solution_registry& instance();

	void register_solution(const std::string& name, const string_function& func);

	template <std::integral T>
	void register_solution(const std::string& name, const std::function<T(std::istream&)>& func) {
		register_solution(name, [func](std::istream& input) { return std::to_string(func(input)); });
	}

	template <std::integral T>
	void register_solution(const std::string& name, T (*func)(std::istream&)) {
		register_solution(name, std::function<T(std::istream&)>{func});
	}

	const string_function& get_solution(const std::string& problem) const;

private:
	std::unordered_map<std::string, string_function> solutions;

	// Make the constructor private to enforce singleton
	solution_registry() = default;
};

#define REGISTER_SOLUTION(name, func)                                 \
	static bool _##name##_registered = [] {                           \
		solution_registry::instance().register_solution(#name, func); \
		return true;                                                  \
	}();

#define REGISTER_DAY(problem_day)                            \
	REGISTER_SOLUTION(problem_day##_1, day##problem_day##_1) \
	REGISTER_SOLUTION(problem_day##_2, day##problem_day##_2)
