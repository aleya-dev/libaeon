// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <string>

namespace aeon::common::string_utils
{

template <typename T>
struct convert
{
};

template <>
struct convert<std::string>
{
    [[nodiscard]] static auto to(const std::string &v)
    {
        return v;
    }

    [[nodiscard]] static auto from(const std::string &v)
    {
        return v;
    }
};

template <>
struct convert<int>
{
    [[nodiscard]] static auto to(const int v)
    {
        return std::to_string(v);
    }

    [[nodiscard]] static auto from(const std::string &v)
    {
        return std::stoi(v);
    }
};

template <>
struct convert<float>
{
    [[nodiscard]] static auto to(const float v)
    {
        return std::to_string(v);
    }

    [[nodiscard]] static auto from(const std::string &v)
    {
        return std::stof(v);
    }
};

template <>
struct convert<bool>
{
    [[nodiscard]] static auto to(const bool v)
    {
        return v ? "1" : "0";
    }

    [[nodiscard]] static auto from(const std::string &v)
    {
        return v == "1" || v == "true";
    }
};

template <typename T>
struct string_type_traits
{
};

template <typename T>
struct string_type_traits<std::basic_string<T>>
{
    using basic_string_type = std::basic_string<T>;
    using basic_string_view_type = std::basic_string_view<T>;
    using char_type = T;
    using size_type = typename std::basic_string<T>::size_type;
    using difference_type = typename std::basic_string<T>::difference_type;
};

template <typename T>
struct string_type_traits<std::basic_string_view<T>>
{
    using basic_string_type = std::basic_string<T>;
    using basic_string_view_type = std::basic_string_view<T>;
    using char_type = T;
    using size_type = typename std::basic_string_view<T>::size_type;
    using difference_type = typename std::basic_string_view<T>::difference_type;
};

template <>
struct string_type_traits<char>
{
    using basic_string_type = std::basic_string<char>;
    using basic_string_view_type = std::basic_string_view<char>;
    using char_type = char;
    using size_type = std::basic_string<char>::size_type;
    using difference_type = std::basic_string<char>::difference_type;
};

template <>
struct string_type_traits<wchar_t>
{
    using basic_string_type = std::basic_string<wchar_t>;
    using basic_string_view_type = std::basic_string_view<wchar_t>;
    using char_type = wchar_t;
    using size_type = std::basic_string<wchar_t>::size_type;
    using difference_type = std::basic_string<wchar_t>::difference_type;
};

template <>
struct string_type_traits<char8_t>
{
    using basic_string_type = std::basic_string<char8_t>;
    using basic_string_view_type = std::basic_string_view<char8_t>;
    using char_type = char8_t;
    using size_type = std::basic_string<char8_t>::size_type;
    using difference_type = std::basic_string<char8_t>::difference_type;
};

template <>
struct string_type_traits<char16_t>
{
    using basic_string_type = std::basic_string<char16_t>;
    using basic_string_view_type = std::basic_string_view<char16_t>;
    using char_type = char16_t;
    using size_type = std::basic_string<char16_t>::size_type;
    using difference_type = std::basic_string<char16_t>::difference_type;
};

template <>
struct string_type_traits<char32_t>
{
    using basic_string_type = std::basic_string<char32_t>;
    using basic_string_view_type = std::basic_string_view<char32_t>;
    using char_type = char32_t;
    using size_type = std::basic_string<char32_t>::size_type;
    using difference_type = std::basic_string<char32_t>::difference_type;
};

template <int size>
struct string_type_traits<char[size]>
{
    using basic_string_type = std::basic_string<char>;
    using basic_string_view_type = std::basic_string_view<char>;
    using char_type = char;
    using size_type = std::basic_string<char>::size_type;
    using difference_type = std::basic_string<char>::difference_type;
};

template <int size>
struct string_type_traits<wchar_t[size]>
{
    using basic_string_type = std::basic_string<wchar_t>;
    using basic_string_view_type = std::basic_string_view<wchar_t>;
    using char_type = wchar_t;
    using size_type = std::basic_string<wchar_t>::size_type;
    using difference_type = std::basic_string<wchar_t>::difference_type;
};

template <int size>
struct string_type_traits<char8_t[size]>
{
    using basic_string_type = std::basic_string<char8_t>;
    using basic_string_view_type = std::basic_string_view<char8_t>;
    using char_type = char8_t;
    using size_type = std::basic_string<char8_t>::size_type;
    using difference_type = std::basic_string<char8_t>::difference_type;
};

template <int size>
struct string_type_traits<char16_t[size]>
{
    using basic_string_type = std::basic_string<char16_t>;
    using basic_string_view_type = std::basic_string_view<char16_t>;
    using char_type = char16_t;
    using size_type = std::basic_string<char16_t>::size_type;
    using difference_type = std::basic_string<char16_t>::difference_type;
};

template <int size>
struct string_type_traits<char32_t[size]>
{
    using basic_string_type = std::basic_string<char32_t>;
    using basic_string_view_type = std::basic_string_view<char32_t>;
    using char_type = char32_t;
    using size_type = std::basic_string<char32_t>::size_type;
    using difference_type = std::basic_string<char32_t>::difference_type;
};

/*!
 * Determine the most appropriate std::basic_string type for a given string-like.
 * For example:
 * const char * -> std::string
 * const wchar_t * -> std::wstring
 * char[5] -> std::string
 * std::string -> std::string
 * std::string_view -> std::string
 */
template <typename T>
using basic_string_type = typename string_type_traits<std::remove_pointer_t<std::decay_t<T>>>::basic_string_type;

/*!
 * Determine the most appropriate std::basic_string_view type for a given string-like.
 * For example:
 * const char * -> std::string_view
 * const wchar_t * -> std::wstring_view
 * char[5] -> std::string_view
 * std::string -> std::string_view
 * std::string_view -> std::string_view
 */
template <typename T>
using basic_string_view_type =
    typename string_type_traits<std::remove_pointer_t<std::decay_t<T>>>::basic_string_view_type;

/*!
 * Determine the character type for a given string-like.
 * For example:
 * const char * -> char
 * const wchar_t * -> wchar_t
 * char[5] -> char
 * std::string -> char
 * std::string_view -> char
 */
template <typename T>
using char_type = typename string_type_traits<std::remove_pointer_t<std::decay_t<T>>>::char_type;

/*!
 * Determine the string size type for a given string-like (typically std::size_t).
 * For example:
 * const char * -> std::string::size_type
 * const wchar_t * -> std::wstring::size_type
 * char[5] -> std::string::size_type
 * std::string -> std::string::size_type
 * std::string_view -> std::string_view::size_type
 */
template <typename T>
using size_type = typename string_type_traits<std::remove_pointer_t<std::decay_t<T>>>::size_type;

/*!
 * Determine the difference type for a given string-like (typically std::ptrdiff).
 * For example:
 * const char * -> std::string::difference_type
 * const wchar_t * -> std::wstring::difference_type
 * char[5] -> std::string::difference_type
 * std::string -> std::string::difference_type
 * std::string_view -> std::string_view::difference_type
 */
template <typename T>
using difference_type = typename string_type_traits<std::remove_pointer_t<std::decay_t<T>>>::difference_type;

} // namespace aeon::common::string_utils
