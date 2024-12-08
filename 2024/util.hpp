#pragma once

#include <array>
#include <functional>
#include <istream>
#include <memory>
#include <string>

using wrapped_istream = std::unique_ptr<std::istream, std::function<void(std::istream*)>>;
using point = std::array<long long, 2>;

wrapped_istream open_input(const std::string& problem);

point operator+(const point& lhs, const point& rhs);
point& operator+=(point& lhs, const point& rhs);

point operator-(const point& lhs, const point& rhs);
point& operator-=(point& lhs, const point& rhs);

point operator*(const point& lhs, long long rhs);
point& operator*=(point& lhs, long long rhs);

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
};

std::istream& operator>>(std::istream& is, letter_grid& grid);
std::ostream& operator<<(std::ostream& os, const letter_grid& grid);
