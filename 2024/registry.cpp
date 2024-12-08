#include "registry.hpp"

solution_registry& solution_registry::instance() {
	static solution_registry registry;
	return registry;
}

void solution_registry::register_solution(const std::string& name, const int_function& func) {
	solutions[name] = [func](std::istream& input) { return std::to_string(func(input)); };
}

void solution_registry::register_solution(const std::string& name, const string_function& func) {
	solutions[name] = func;
}

auto solution_registry::get_solution(const std::string& problem) const -> const string_function& {
	return solutions.at(problem);
}
