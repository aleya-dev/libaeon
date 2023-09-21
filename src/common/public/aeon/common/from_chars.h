// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string_view.h>
#include <system_error>
#include <cstdint>

namespace aeon::Common
{

template <typename CharT>
struct FromCharsResult
{
    const CharT *Ptr;
    std::errc Ec;
};

auto FromChars(const char *first, const char *last, std::int32_t &value, const int base = 10)
    -> FromCharsResult<char>;
auto FromChars(const char *first, const char *last, std::int64_t &value, const int base = 10)
    -> FromCharsResult<char>;
auto FromChars(const char *first, const char *last, std::uint32_t &value, const int base = 10)
    -> FromCharsResult<char>;
auto FromChars(const char *first, const char *last, std::uint64_t &value, const int base = 10)
    -> FromCharsResult<char>;

auto FromChars(const char8_t *first, const char8_t *last, std::int32_t &value, const int base = 10)
    -> FromCharsResult<char8_t>;
auto FromChars(const char8_t *first, const char8_t *last, std::int64_t &value, const int base = 10)
    -> FromCharsResult<char8_t>;
auto FromChars(const char8_t *first, const char8_t *last, std::uint32_t &value, const int base = 10)
    -> FromCharsResult<char8_t>;
auto FromChars(const char8_t *first, const char8_t *last, std::uint64_t &value, const int base = 10)
    -> FromCharsResult<char8_t>;

auto FromChars(const char *first, const char *last, float &value) -> FromCharsResult<char>;
auto FromChars(const char *first, const char *last, double &value) -> FromCharsResult<char>;
auto FromChars(const char *first, const char *last, long double &value) -> FromCharsResult<char>;

auto FromChars(const char8_t *first, const char8_t *last, float &value) -> FromCharsResult<char8_t>;
auto FromChars(const char8_t *first, const char8_t *last, double &value) -> FromCharsResult<char8_t>;
auto FromChars(const char8_t *first, const char8_t *last, long double &value) -> FromCharsResult<char8_t>;

template <typename T>
inline auto FromChars(const StringView str, T &value) -> FromCharsResult<char>
{
    return FromChars(std::data(str), std::data(str) + std::size(str), value);
}

template <typename T>
inline auto FromChars(const StringView str, T &value, const int base) -> FromCharsResult<char>
{
    return FromChars(std::data(str), std::data(str) + std::size(str), value, base);
}

} // namespace aeon::Common
