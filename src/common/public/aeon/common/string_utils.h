// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/container.h>
#include <aeon/common/string_concepts.h>
#include <aeon/common/string_traits.h>
#include <aeon/common/string.h>
#include <aeon/common/string_view.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

namespace aeon::Common::StringUtils
{

/*!
 * Compare 2 strings case insensitive. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto IEquals(const StringView &str1, const StringView &str2) noexcept -> bool;

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto Split(const String &str, const T delimiter, std::vector<String> &elements)
    -> std::vector<String> &;

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Returns a vector of split elements.
 */
template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto Split(const String &str, const T delim) -> std::vector<String>;

/*!
 * Split/tokenize a StringView into a vector of string_views based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto Splitsv(const StringView &str, const T delim, std::vector<StringView> &elements)
    -> std::vector<StringView>;

/*!
 * Split/tokenize a StringView into a vector of string_views based on a delimiter.
 * Returns a vector of split elements.
 */
template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto Splitsv(const StringView &str, const T delim) -> std::vector<StringView>;

/*!
 * Trim from the start of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void Ltrim(String &str);

/*!
 * Trim from the start of a StringView. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void Ltrimsv(StringView &str);

/*!
 * Trim from the ending of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void Rtrim(String &str);

/*!
 * Trim from the ending of a StringView. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void Rtrimsv(StringView &str);

/*!
 * Trim a string at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void Trim(String &str);

/*!
 * Trim a StringView at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void Trimsv(StringView &str);

/*!
 * Trim from the start of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto Ltrimmed(const StringView &str) -> String;

/*!
 * Trim from the start of a StringView. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto Ltrimmedsv(const StringView &str) -> StringView;

/*!
 * Trim from the ending of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto Rtrimmed(const StringView &str) -> String;

/*!
 * Trim from the ending of a StringView. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto Rtrimmedsv(const StringView &str) -> StringView;

/*!
 * Trim a string at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto Trimmed(const StringView &str) -> String;

/*!
 * Trim a StringView at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto Trimmedsv(const StringView &str) -> StringView;

/*!
 * Get len characters from the left of the string.
 */
[[nodiscard]] inline auto Left(const StringView &str, const StringView::size_type len) -> String;

/*!
 * Get len characters from the left of the StringView.
 */
[[nodiscard]] inline auto Leftsv(const StringView &str, const StringView::size_type len) -> StringView;

/*!
 * Get len characters from the right of the string.
 */
[[nodiscard]] inline auto Right(const StringView &str, const StringView::size_type len) -> String;

/*!
 * Get len characters from the right of the StringView.
 */
[[nodiscard]] inline auto Rightsv(const StringView &str, const StringView::size_type len) -> StringView;

/*!
 * Strip len characters at the left of the string
 */
[[nodiscard]] inline auto StrippedLeft(const StringView &str, const StringView::size_type len) -> String;

/*!
 * Strip len characters at the left of the StringView
 */
[[nodiscard]] inline auto StrippedLeftsv(const StringView &str, const StringView::size_type len) -> StringView;

/*!
 * Strip len characters at the right of the string
 */
[[nodiscard]] inline auto StrippedRight(const StringView &str, const StringView::size_type len) -> String;

/*!
 * Strip len characters at the right of the StringView
 */
[[nodiscard]] inline auto StrippedRightsv(const StringView &str, const StringView::size_type len) -> StringView;

/*!
 * Strip len characters on both sides of the string.
 */
[[nodiscard]] inline auto StrippedBoth(const StringView &str, const StringView::size_type len) -> String;

/*!
 * Strip len characters on both sides of the StringView.
 */
[[nodiscard]] inline auto StrippedBothsv(const StringView &str, const StringView::size_type len) -> StringView;

/*!
 * Strip all characters equal to c on the left side of the string.
 */
template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedLeft(const StringView &str, const T c) -> String;

/*!
 * Strip all characters equal to c on the left side of the StringView.
 */
template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedLeftsv(const StringView &str, const T c) -> StringView;

/*!
 * Strip all characters equal to c on the right side of the string.
 */
template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedRight(const StringView &str, const T c) -> String;

/*!
 * Strip all characters equal to c on the right side of the StringView.
 */
template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedRightsv(const StringView &str, const T c) -> StringView;

/*!
 * Strip all characters equal to c on both sides of the string.
 */
template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedBoth(const StringView &str, const T c) -> String;

/*!
 * Strip all characters equal to c on both sides of the StringView.
 */
template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedBothsv(const StringView &str, const T c) -> StringView;

/*!
 * Strip len characters at the left of the string
 */
inline void StripLeft(String &str, const String::size_type len);

/*!
 * Strip len characters at the left of the StringView
 */
inline void StripLeftsv(StringView &str, const StringView::size_type len);

/*!
 * Strip len characters at the right of the string
 */
inline void StripRight(String &str, const String::size_type len);

/*!
 * Strip len characters at the right of the StringView
 */
inline void StripRightsv(StringView &str, const StringView::size_type len);

/*!
 * Strip len characters on both sides of the string.
 */
inline void StripBoth(String &str, const String::size_type len);

/*!
 * Strip len characters on both sides of the StringView.
 */
inline void StripBothsv(StringView &str, const StringView::size_type len);

/*!
 * Strip all characters equal to c on the left side of the string.
 */
inline void CharStripLeft(String &str, const String::value_type c);

/*!
 * Strip all characters equal to c on the left side of the StringView.
 */
inline void CharStripLeftsv(StringView &str, const StringView::value_type c);

/*!
 * Strip all characters equal to c on the right side of the string.
 */
inline void CharStripRight(String &str, const String::value_type c);

/*!
 * Strip all characters equal to c on the right side of the StringView.
 */
inline void CharStripRightsv(StringView &str, const StringView::value_type c);

/*!
 * Strip all characters equal to c on both sides of the string.
 */
inline void CharStripBoth(String &str, const String::value_type c);

/*!
 * Strip all characters equal to c on both sides of the StringView.
 */
inline void CharStripBothsv(StringView &str, const StringView::value_type c);

/*!
 * Replace all occurrences of a string with another string.
 */
inline void Replace(String &str, const StringView &from, const StringView &to);

/*!
 * Replace all occurrences of a string with another string.
 */
[[nodiscard]] inline auto ReplaceCopy(const StringView &str, const StringView &from, const StringView &to) -> String;

/*!
 * Convert the current string to lowercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
inline void ToLower(String &str);

/*!
 * Convert the current string to lowercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
[[nodiscard]] inline auto ToLowerCopy(const StringView &str) -> String;

/*!
 * Convert the current string to uppercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
inline void ToUpper(String &str);

/*!
 * Convert the current string to uppercase based to the locale settings
 */
[[nodiscard]] inline auto ToUpperCopy(const StringView &str) -> String;

/*!
 * Check if a string begins with another string
 */
[[nodiscard]] inline auto BeginsWith(const StringView &str, const StringView &val) -> bool;

/*!
 * Check if a string begins with another string
 */
[[nodiscard]] inline auto EndsWith(const StringView &str, const StringView &val) -> bool;

/*!
 * Check if the string "val" is found within "str".
 */
[[nodiscard]] inline auto Contains(const StringView &str, const StringView &val) -> bool;

/*!
 * Check if the character c is found within "str".
 */
[[nodiscard]] inline auto Contains(const StringView &str, const StringView::value_type c) -> bool;

/*!
 * Convert a character into a hex string.
 * For example: 'a' becomes "61".
 */
[[nodiscard]] auto CharToHex(const char c) -> String;

/*
 * Convert a hex string into a char
 * For example: "61" becomes 'a'.
 */
[[nodiscard]] auto HexToChar(const String &str) -> char;

/*!
 * Convert a string in HEX format ("0x1234") to an integer.
 */
template <typename T>
[[nodiscard]] inline auto HexStringToInt(const String &str)
{
    T value;
    std::istringstream iss(str.Str());
    iss >> std::hex >> value;
    return value;
}

template <>
[[nodiscard]] inline auto HexStringToInt<std::uint8_t>(const String &str)
{
    int value;
    std::istringstream iss(str.Str());
    iss >> std::hex >> value;
    return static_cast<std::uint8_t>(value);
}

/*!
 * Convert a value into HEX format (ie. 255 becomes "ff")
 */
template <typename T>
[[nodiscard]] inline auto IntToHexString(const T value) -> String
{
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << static_cast<std::int64_t>(value);
    return std::move(stream.str());
}

/*!
 * Convert a byte into HEX format (ie. 255 becomes "ff")
 */
[[nodiscard]] inline auto Uint8ToHexString(const std::uint8_t value) noexcept -> const char *;

/*!
 * Construct a StringView from given iterators
 */
template <typename IteratorT>
[[nodiscard]] inline constexpr auto MakeStringView(IteratorT begin, IteratorT end) noexcept
{
    using ResultType = std::basic_string_view<typename std::iterator_traits<IteratorT>::value_type>;

    if (begin == end)
        return ResultType{};

    return ResultType{&*begin, static_cast<typename ResultType::size_type>(
                                    std::max(std::distance(begin, end), typename ResultType::difference_type{}))};
}

} // namespace aeon::Common::string_utils

#include <aeon/common/impl/string_utils_impl.h>
