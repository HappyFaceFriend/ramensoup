#pragma once

#include <string_view>

namespace Ramensoup
{
	class zstring_view final : private std::string_view
	{
	public:
		zstring_view(const char* string) : std::string_view(string) {}
		zstring_view(const std::string& string) : std::string_view(string) {}

		constexpr operator std::string_view() const noexcept { return (std::string_view)*this; }
		constexpr operator const char* () const noexcept { return std::string_view::data(); }

		constexpr const char* c_str() const noexcept { return std::string_view::data(); }
		constexpr const char* data() const noexcept { return std::string_view::data(); }

		constexpr const size_t length() const noexcept { return std::string_view::length(); }
		constexpr const size_t size() const noexcept { return std::string_view::size(); }

		constexpr std::string_view substr(size_t pos = 0, size_t count = npos) const { return std::string_view::substr(pos, count); }

		constexpr size_t find(const zstring_view& s, size_t pos = 0) const noexcept { return std::string_view::find(s, pos); }
		constexpr size_t find(const char* s, size_t pos = 0) const noexcept { return std::string_view::find(s, pos); }
		constexpr size_t find(char s, size_t pos = 0) const noexcept { return std::string_view::find(s, pos); }

		constexpr size_t rfind(const zstring_view& s, size_t pos = 0) const noexcept { return std::string_view::rfind(s, pos); }
		constexpr size_t rfind(const char* s, size_t pos = 0) const noexcept { return std::string_view::rfind(s, pos); }
		constexpr size_t rfind(char s, size_t pos = 0) const noexcept { return std::string_view::rfind(s, pos); }

		constexpr size_t find_first_of(const zstring_view& s, size_t pos = 0) const noexcept { return std::string_view::find_first_of(s, pos); }
		constexpr size_t find_first_of(const char* s, size_t pos = 0) const noexcept { return std::string_view::find_first_of(s, pos); }
		constexpr size_t find_first_of(char s, size_t pos = 0) const noexcept { return std::string_view::find_first_of(s, pos); }

		constexpr size_t find_last_of(const zstring_view& s, size_t pos = 0) const noexcept { return std::string_view::find_last_of(s, pos); }
		constexpr size_t find_last_of(const char* s, size_t pos = 0) const noexcept { return std::string_view::find_last_of(s, pos); }
		constexpr size_t find_last_of(char s, size_t pos = 0) const noexcept { return std::string_view::find_last_of(s, pos); }


	};

}