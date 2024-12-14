#pragma once

#include <array>
#include <functional>
#include <istream>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

using wrapped_istream = std::unique_ptr<std::istream, std::function<void(std::istream*)>>;
using point = std::array<long long, 2>;

constexpr point INVALID_POINT{-1, -1};
constexpr point NORTH{-1, 0};
constexpr point EAST{0, 1};
constexpr point SOUTH{1, 0};
constexpr point WEST{0, -1};
constexpr std::array<point, 4> CARDINAL_DIRS{NORTH, EAST, SOUTH, WEST};

wrapped_istream open_input(const std::string& problem);

template <>
struct std::hash<point> {
	constexpr std::size_t operator()(const point& p) const noexcept {
		std::size_t h1 = std::hash<point::value_type>{}(p[0]);
		std::size_t h2 = std::hash<point::value_type>{}(p[1]);
		return h1 + 0x9e3779b9U + (h2 << 6) + (h2 >> 2);
	}
};

template <typename T1, typename T2>
struct std::hash<std::pair<T1, T2>> {  // NOLINT(*-dcl58-cpp)
	constexpr std::size_t operator()(const std::pair<T1, T2>& p) const noexcept {
		std::size_t h1 = std::hash<T1>{}(p.first);
		std::size_t h2 = std::hash<T2>{}(p.second);
		return h1 + 0x9e3779b9U + (h2 << 6) + (h2 >> 2);
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

constexpr point operator*(point::value_type lhs, const point& rhs) {
	return {lhs * rhs[0], lhs * rhs[1]};
}

constexpr point operator*(const point& lhs, point::value_type rhs) {
	return rhs * lhs;
}

constexpr point& operator*=(point& lhs, point::value_type rhs) {
	lhs[0] *= rhs;
	lhs[1] *= rhs;

	return lhs;
}

constexpr point operator/(const point& lhs, point::value_type rhs) {
	return {lhs[0] / rhs, lhs[1] / rhs};
}

constexpr point& operator/=(point& lhs, point::value_type rhs) {
	lhs[0] /= rhs;
	lhs[1] /= rhs;

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
