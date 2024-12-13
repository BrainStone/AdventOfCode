#pragma once

#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

using wrapped_istream = std::unique_ptr<std::istream, std::function<void(std::istream*)>>;
using point = std::array<long long, 2>;

constexpr point INVALID_POINT{-1, -1};

wrapped_istream open_input(const std::string& problem);

template <>
struct std::hash<point> {
	constexpr std::size_t operator()(const point& p) const noexcept {
		std::size_t h1 = std::hash<long long>{}(p[0]);
		std::size_t h2 = std::hash<long long>{}(p[1]);
		return h1 + 0x9e3779b9 + (h2 << 6) + (h2 >> 2);
	}
};

constexpr point operator+(const point& lhs, const point& rhs) {
	return {lhs[0] + rhs[0], lhs[1] + rhs[1]};
}

constexpr point& operator+=(point& lhs, const point& rhs) {
	lhs[0] += rhs[0];
	lhs[1] += rhs[1];

	return lhs;
}

constexpr point operator-(const point& lhs, const point& rhs) {
	return {lhs[0] - rhs[0], lhs[1] - rhs[1]};
}

constexpr point& operator-=(point& lhs, const point& rhs) {
	lhs[0] -= rhs[0];
	lhs[1] -= rhs[1];

	return lhs;
}

constexpr point operator*(long long lhs, const point& rhs) {
	return {lhs * rhs[0], lhs * rhs[1]};
}

constexpr point operator*(const point& lhs, long long rhs) {
	return rhs * lhs;
}

constexpr point& operator*=(point& lhs, long long rhs) {
	lhs[0] *= rhs;
	lhs[1] *= rhs;

	return lhs;
}

std::ostream& operator<<(std::ostream& os, const point& rhs);

class letter_grid {
private:
	std::vector<std::string> grid;

	void check_line(const std::string& line) const;

public:
	letter_grid();

	void add_line(const std::string& line);
	void add_line(std::string&& line);

	[[nodiscard]] size_t width() const;
	[[nodiscard]] size_t height() const;

	[[nodiscard]] std::string& operator[](size_t row);
	[[nodiscard]] const std::string& operator[](size_t row) const;

	[[nodiscard]] char& operator[](const point& position);
	[[nodiscard]] const char& operator[](const point& position) const;

	[[nodiscard]] bool is_valid_point(const point& position) const;
	[[nodiscard]] point next_point(const point& position) const;
	[[nodiscard]] point find(char c, const point& start = {0, 0}) const;
};

std::istream& operator>>(std::istream& is, letter_grid& grid);
std::ostream& operator<<(std::ostream& os, const letter_grid& grid);
