// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <algorithm>
#include <array>

namespace aeon::Common
{

template <typename char_type_t, std::size_t N>
class BasicStringLiteral
{
public:
    using storage_type = char[N];

    using value_type = char_type_t;
    using reference = const char_type_t &;
    using const_reference = const char_type_t &;
    using size_type = std::size_t;

    using iterator = const char_type_t *;
    using const_iterator = const char_type_t *;

    constexpr BasicStringLiteral() noexcept
    {
        static_assert(N == 0, "String literal of size > 0 can not be empty.");
    }

    constexpr BasicStringLiteral(const char_type_t (&str)[N])
    {
        std::copy_n(str, N, value);
    }

    constexpr operator const storage_type &() const
    {
        return value;
    }

    constexpr auto size() const -> size_type
    {
        return N;
    }

    constexpr const char_type_t *data() const noexcept
    {
        return value;
    }

    constexpr const char_type_t *c_str() const noexcept
    {
        return value;
    }

    constexpr iterator begin() const noexcept
    {
        return value;
    }

    constexpr iterator end() const noexcept
    {
        return value + N;
    }

    constexpr const_iterator cbegin() const noexcept
    {
        return value;
    }

    constexpr const_iterator cend() const noexcept
    {
        return value + N;
    }

    char_type_t value[N];
};

template <typename char_type_t, std::size_t N>
BasicStringLiteral(const char_type_t (&)[N]) -> BasicStringLiteral<char_type_t, N>;

template <std::size_t N>
using StringLiteral = BasicStringLiteral<char, N>;

template <std::size_t N>
using WStringLiteral = BasicStringLiteral<wchar_t, N>;

template <std::size_t N>
using U8StringLiteral = BasicStringLiteral<char8_t, N>;

template <std::size_t N>
using U16StringLiteral = BasicStringLiteral<char16_t, N>;

template <std::size_t N>
using U32StringLiteral = BasicStringLiteral<char32_t, N>;

} // namespace aeon::Common
