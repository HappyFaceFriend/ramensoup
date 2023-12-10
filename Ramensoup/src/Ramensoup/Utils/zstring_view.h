#pragma once

#include <string_view>

namespace Ramensoup
{
	class zstring_view final : private std::string_view
	{
		using string_view_base = std::string_view;
	public:
		[[nodiscard]] constexpr zstring_view(const char* string) : std::string_view(string) {}
		[[nodiscard]] constexpr zstring_view(const std::string& string) : std::string_view(string) {}

		[[nodiscard]] constexpr operator std::string_view() const noexcept { return (std::string_view)*this; }
		[[nodiscard]] constexpr operator const char* () const noexcept { return std::string_view::data(); }

		[[nodiscard]] constexpr const char* c_str() const noexcept { return std::string_view::data(); }

		constexpr size_t find(const zstring_view& s, size_t pos = 0) const noexcept { return std::string_view::find(s, pos); }
		constexpr size_t rfind(const zstring_view& s, size_t pos = 0) const noexcept { return std::string_view::rfind(s, pos); }
		constexpr size_t find_first_of(const zstring_view& s, size_t pos = 0) const noexcept { return std::string_view::find_first_of(s, pos); }
		constexpr size_t find_last_of(const zstring_view& s, size_t pos = 0) const noexcept { return std::string_view::find_last_of(s, pos); }

		using string_view_base::size;
		using string_view_base::length;
		using string_view_base::max_size;
		using string_view_base::empty;

		using string_view_base::operator[];
		using string_view_base::at;
		using string_view_base::back;
		using string_view_base::front;
		using string_view_base::data;

		using string_view_base::begin;
		using string_view_base::cbegin;
		using string_view_base::end;
		using string_view_base::cend;
		using string_view_base::rbegin;
		using string_view_base::crbegin;
		using string_view_base::rend;
		using string_view_base::crend;
		
		using string_view_base::substr;
		using string_view_base::compare;
		using string_view_base::find;
		using string_view_base::rfind;
		using string_view_base::find_first_of;
		using string_view_base::find_last_of;

#if _HAS_CXX20 //C++20
		using string_view_base::starts_with;
		using string_view_base::ends_with;
#endif //C++20

	};

}