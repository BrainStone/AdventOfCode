#pragma once

#include <ranges>
#include <type_traits>

// All template or constexpr stuff, so it needs to be in the header

namespace views {

struct skip_nth_view : std::ranges::range_adaptor_closure<skip_nth_view> {
	const size_t n;  // The index to skip

	template <std::ranges::viewable_range R>
	constexpr auto operator()(R&& range) const {
		return std::ranges::views::enumerate(range) | std::ranges::views::filter([n = this->n](const auto& pair) {
			       auto [index, value] = pair;
			       return index != n;
		       }) |
		       std::ranges::views::transform([](const auto& pair) {
			       auto [index, value] = pair;
			       return value;
		       });
	}
};

constexpr skip_nth_view skip_nth(size_t n) {
	return skip_nth_view{.n = n};
}

}  // namespace views

namespace ranges {

template <typename Range, typename T>
concept range_of =
    std::ranges::range<Range> && std::is_same_v<std::remove_cvref_t<std::ranges::range_value_t<Range>>, T>;

}  // namespace ranges
