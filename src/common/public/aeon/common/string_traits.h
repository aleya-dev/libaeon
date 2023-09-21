// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <string>

namespace aeon::Common::StringUtils
{

template <typename T>
struct Convert
{
};

template <>
struct Convert<std::string>
{
    [[nodiscard]] static auto To(const std::string &v)
    {
        return v;
    }

    [[nodiscard]] static auto From(const std::string &v)
    {
        return v;
    }
};

template <>
struct Convert<int>
{
    [[nodiscard]] static auto To(const int v)
    {
        return std::to_string(v);
    }

    [[nodiscard]] static auto From(const std::string &v)
    {
        return std::stoi(v);
    }
};

template <>
struct Convert<float>
{
    [[nodiscard]] static auto To(const float v)
    {
        return std::to_string(v);
    }

    [[nodiscard]] static auto From(const std::string &v)
    {
        return std::stof(v);
    }
};

template <>
struct Convert<bool>
{
    [[nodiscard]] static auto To(const bool v)
    {
        return v ? "1" : "0";
    }

    [[nodiscard]] static auto From(const std::string &v)
    {
        return v == "1" || v == "true";
    }
};

template <typename T>
struct StringTypeTraits
{
};

template <typename T>
struct StringTypeTraits<std::basic_string<T>>
{
    using BasicStringType = std::basic_string<T>;
    using BasicStringViewType = std::basic_string_view<T>;
    using CharType = T;
    using SizeType = typename std::basic_string<T>::size_type;
    using DifferenceType = typename std::basic_string<T>::difference_type;
};

template <typename T>
struct StringTypeTraits<std::basic_string_view<T>>
{
    using BasicStringType = std::basic_string<T>;
    using BasicStringViewType = std::basic_string_view<T>;
    using CharType = T;
    using SizeType = typename std::basic_string_view<T>::size_type;
    using DifferenceType = typename std::basic_string_view<T>::difference_type;
};

template <>
struct StringTypeTraits<char>
{
    using BasicStringType = std::basic_string<char>;
    using BasicStringViewType = std::basic_string_view<char>;
    using CharType = char;
    using SizeType = std::basic_string<char>::size_type;
    using DifferenceType = std::basic_string<char>::difference_type;
};

template <>
struct StringTypeTraits<wchar_t>
{
    using BasicStringType = std::basic_string<wchar_t>;
    using BasicStringViewType = std::basic_string_view<wchar_t>;
    using CharType = wchar_t;
    using SizeType = std::basic_string<wchar_t>::size_type;
    using DifferenceType = std::basic_string<wchar_t>::difference_type;
};

template <>
struct StringTypeTraits<char8_t>
{
    using BasicStringType = std::basic_string<char8_t>;
    using BasicStringViewType = std::basic_string_view<char8_t>;
    using CharType = char8_t;
    using SizeType = std::basic_string<char8_t>::size_type;
    using DifferenceType = std::basic_string<char8_t>::difference_type;
};

template <>
struct StringTypeTraits<char16_t>
{
    using BasicStringType = std::basic_string<char16_t>;
    using BasicStringViewType = std::basic_string_view<char16_t>;
    using CharType = char16_t;
    using SizeType = std::basic_string<char16_t>::size_type;
    using DifferenceType = std::basic_string<char16_t>::difference_type;
};

template <>
struct StringTypeTraits<char32_t>
{
    using BasicStringType = std::basic_string<char32_t>;
    using BasicStringViewType = std::basic_string_view<char32_t>;
    using CharType = char32_t;
    using SizeType = std::basic_string<char32_t>::size_type;
    using DifferenceType = std::basic_string<char32_t>::difference_type;
};

template <int Size>
struct StringTypeTraits<char[Size]>
{
    using BasicStringType = std::basic_string<char>;
    using BasicStringViewType = std::basic_string_view<char>;
    using CharType = char;
    using SizeType = std::basic_string<char>::size_type;
    using DifferenceType = std::basic_string<char>::difference_type;
};

template <int Size>
struct StringTypeTraits<wchar_t[Size]>
{
    using BasicStringType = std::basic_string<wchar_t>;
    using BasicStringViewType = std::basic_string_view<wchar_t>;
    using CharType = wchar_t;
    using SizeType = std::basic_string<wchar_t>::size_type;
    using DifferenceType = std::basic_string<wchar_t>::difference_type;
};

template <int Size>
struct StringTypeTraits<char8_t[Size]>
{
    using BasicStringType = std::basic_string<char8_t>;
    using BasicStringViewType = std::basic_string_view<char8_t>;
    using CharType = char8_t;
    using SizeType = std::basic_string<char8_t>::size_type;
    using DifferenceType = std::basic_string<char8_t>::difference_type;
};

template <int Size>
struct StringTypeTraits<char16_t[Size]>
{
    using BasicStringType = std::basic_string<char16_t>;
    using BasicStringViewType = std::basic_string_view<char16_t>;
    using CharType = char16_t;
    using SizeType = std::basic_string<char16_t>::size_type;
    using DifferenceType = std::basic_string<char16_t>::difference_type;
};

template <int Size>
struct StringTypeTraits<char32_t[Size]>
{
    using BasicStringType = std::basic_string<char32_t>;
    using BasicStringViewType = std::basic_string_view<char32_t>;
    using CharType = char32_t;
    using SizeType = std::basic_string<char32_t>::size_type;
    using DifferenceType = std::basic_string<char32_t>::difference_type;
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
using BasicStringType = typename StringTypeTraits<std::remove_pointer_t<std::decay_t<T>>>::BasicStringType;

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
using BasicStringViewType =
    typename StringTypeTraits<std::remove_pointer_t<std::decay_t<T>>>::BasicStringViewType;

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
using CharType = typename StringTypeTraits<std::remove_pointer_t<std::decay_t<T>>>::CharType;

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
using SizeType = typename StringTypeTraits<std::remove_pointer_t<std::decay_t<T>>>::SizeType;

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
using DifferenceType = typename StringTypeTraits<std::remove_pointer_t<std::decay_t<T>>>::DifferenceType;

} // namespace aeon::Common::string_utils
