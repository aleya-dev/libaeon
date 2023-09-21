// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/from_chars.h>
#include <aeon_cpp_support.h>

#if (defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER) || defined(AEON_COMPILER_HAS_FROM_CHARS_DOUBLE))
#include <charconv>
#endif

#if (!defined(AEON_COMPILER_HAS_FROM_CHARS_DOUBLE))
#define _USE_MATH_DEFINES
#include <cmath>
#endif

#include <climits>

namespace aeon::Common
{

namespace Internal
{

#if (!defined(AEON_COMPILER_HAS_FROM_CHARS_FLOAT))
template <typename T, typename FuncT>
auto FromCharsInternal(const char *first, const char *last, T &value, FuncT &&func) -> FromCharsResult<char>
{
    auto end = const_cast<char *>(last);
    value = func(first, &end);

    if (value == HUGE_VAL)
        return {first, std::errc::invalid_argument};

    return {end, {}};
}
#endif

#if (!defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER))
template <typename T, typename FuncT>
auto FromCharsInternal(const char *first, const char *last, T &value, FuncT &&func, const int base)
    -> FromCharsResult<char>
{
    if (*first == '0')
        return {first + 1, {}};

    auto end = const_cast<char *>(last);
    value = func(first, &end, base);

    if (value == 0)
        return {first, std::errc::invalid_argument};

    return {end, {}};
}
#endif

} // namespace internal

auto FromChars(const char *first, const char *last, std::int32_t &value, const int base) -> FromCharsResult<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER))
    auto [ptr, ec] = std::from_chars(first, last, value, base);
    return {ptr, ec};
#else
    std::int32_t val = 0;
    const auto result = Internal::FromCharsInternal(first, last, val, strtol, base);

    if (val == LONG_MIN || val == LONG_MAX)
        return {first, std::errc::result_out_of_range};

    value = val;

    return result;
#endif
}

auto FromChars(const char *first, const char *last, std::int64_t &value, const int base) -> FromCharsResult<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER))
    auto [ptr, ec] = std::from_chars(first, last, value, base);
    return {ptr, ec};
#else
    std::int64_t val = 0;
    const auto result = Internal::FromCharsInternal(first, last, val, strtoll, base);

    if (val == LLONG_MIN || val == LLONG_MAX)
        return {first, std::errc::result_out_of_range};

    value = val;

    return result;
#endif
}

auto FromChars(const char *first, const char *last, std::uint32_t &value, const int base) -> FromCharsResult<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER))
    auto [ptr, ec] = std::from_chars(first, last, value, base);
    return {ptr, ec};
#else
    std::uint32_t val = 0;
    const auto result = Internal::FromCharsInternal(first, last, val, strtoul, base);

    if (val == ULONG_MAX)
        return {first, std::errc::result_out_of_range};

    value = val;

    return result;
#endif
}

auto FromChars(const char *first, const char *last, std::uint64_t &value, const int base) -> FromCharsResult<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER))
    auto [ptr, ec] = std::from_chars(first, last, value, base);
    return {ptr, ec};
#else
    std::uint64_t val = 0;
    const auto result = Internal::FromCharsInternal(first, last, val, strtoull, base);

    if (val == ULLONG_MAX)
        return {first, std::errc::result_out_of_range};

    value = val;

    return result;
#endif
}

auto FromChars(const char8_t *first, const char8_t *last, std::int32_t &value, const int base)
    -> FromCharsResult<char8_t>
{
    const auto result =
        FromChars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value, base);
    return {reinterpret_cast<const char8_t *>(result.Ptr), result.Ec};
}

auto FromChars(const char8_t *first, const char8_t *last, std::int64_t &value, const int base)
    -> FromCharsResult<char8_t>
{
    const auto result =
        FromChars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value, base);
    return {reinterpret_cast<const char8_t *>(result.Ptr), result.Ec};
}

auto FromChars(const char8_t *first, const char8_t *last, std::uint32_t &value, const int base)
    -> FromCharsResult<char8_t>
{
    const auto result =
        FromChars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value, base);
    return {reinterpret_cast<const char8_t *>(result.Ptr), result.Ec};
}

auto FromChars(const char8_t *first, const char8_t *last, std::uint64_t &value, const int base)
    -> FromCharsResult<char8_t>
{
    const auto result =
        FromChars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value, base);
    return {reinterpret_cast<const char8_t *>(result.Ptr), result.Ec};
}

auto FromChars(const char *first, const char *last, float &value) -> FromCharsResult<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_FLOAT))
    auto [ptr, ec] = std::from_chars(first, last, value);
    return {ptr, ec};
#else
    return Internal::FromCharsInternal(first, last, value, strtof);
#endif
}

auto FromChars(const char *first, const char *last, double &value) -> FromCharsResult<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_DOUBLE))
    auto [ptr, ec] = std::from_chars(first, last, value);
    return {ptr, ec};
#else
    return Internal::FromCharsInternal(first, last, value, strtod);
#endif
}

auto FromChars(const char *first, const char *last, long double &value) -> FromCharsResult<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_LONG_DOUBLE))
    auto [ptr, ec] = std::from_chars(first, last, value);
    return {ptr, ec};
#else
    return Internal::FromCharsInternal(first, last, value, strtold);
#endif
}

auto FromChars(const char8_t *first, const char8_t *last, float &value) -> FromCharsResult<char8_t>
{
    const auto result = FromChars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value);
    return {reinterpret_cast<const char8_t *>(result.Ptr), result.Ec};
}

auto FromChars(const char8_t *first, const char8_t *last, double &value) -> FromCharsResult<char8_t>
{
    const auto result = FromChars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value);
    return {reinterpret_cast<const char8_t *>(result.Ptr), result.Ec};
}

auto FromChars(const char8_t *first, const char8_t *last, long double &value) -> FromCharsResult<char8_t>
{
    const auto result = FromChars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value);
    return {reinterpret_cast<const char8_t *>(result.Ptr), result.Ec};
}

} // namespace aeon::Common
