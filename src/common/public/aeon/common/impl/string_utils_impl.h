// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <cstdint>
#include <array>
#include <locale>

namespace aeon::Common::StringUtils
{

[[nodiscard]] inline auto IEquals(const StringView &str1, const StringView &str2) noexcept -> bool
{
    return std::equal(std::cbegin(str1), std::cend(str1), std::cbegin(str2), std::cend(str2),
                      [](const auto a, const auto b) { return std::tolower(a) == std::tolower(b); });
}

template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto Split(const String &str, const T delimiter, std::vector<String> &elements)
    -> std::vector<String> &
{
    std::basic_stringstream ss{str.Str()};
    String item;

    while (std::getline(ss, item.Str(), static_cast<char>(delimiter)))
    {
        elements.emplace_back(item);
    }

    return elements;
}

template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto Split(const String &str, const T delim) -> std::vector<String>
{
    std::vector<String> elements;
    return Split(str, delim, elements);
}

template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto Splitsv(const StringView &str, const T delim, std::vector<StringView> &elements)
    -> std::vector<StringView>
{
    auto start = StringView::size_type{};
    auto pos = str.FindFirstOf(delim, start);

    while (pos != StringView::npos)
    {
        elements.emplace_back(str.Substr(start, pos - start));
        start = pos + 1;
        pos = str.FindFirstOf(delim, start);
    }

    if (start < std::size(str))
        elements.emplace_back(str.Substr(start, std::size(str) - start));

    return elements;
}

template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto Splitsv(const StringView &str, const T delim) -> std::vector<StringView>
{
    std::vector<StringView> elements;
    return Splitsv(str, delim, elements);
}

inline void Ltrim(String &str)
{
    str.Erase(std::begin(str), std::find_if(std::cbegin(str), std::cend(str),
                                            [](const auto c) { return !std::isspace(static_cast<int>(c)); }));
}

inline void Ltrimsv(StringView &str)
{
    str.RemovePrefix(Container::CountUntil(std::cbegin(str), std::cend(str),
                                             [](const auto c) { return !std::isspace(static_cast<int>(c)); }));
}

inline void Rtrim(String &str)
{
    str.Erase(
        std::find_if(std::rbegin(str), std::rend(str), [](const auto c) { return !std::isspace(static_cast<int>(c)); })
            .base(),
        std::end(str));
}

inline void Rtrimsv(StringView &str)
{
    str.RemoveSuffix(Container::CountUntil(std::crbegin(str), std::crend(str),
                                             [](const auto c) { return !std::isspace(static_cast<int>(c)); }));
}

inline void Trim(String &str)
{
    Ltrim(str);
    Rtrim(str);
}

inline void Trimsv(StringView &str)
{
    Ltrimsv(str);
    Rtrimsv(str);
}

[[nodiscard]] inline auto Ltrimmed(const StringView &str) -> String
{
    auto trimstr = String{str};
    Ltrim(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto Ltrimmedsv(const StringView &str) -> StringView
{
    auto trimstr = StringView{str};
    Ltrimsv(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto Rtrimmed(const StringView &str) -> String
{
    auto trimstr = String{str};
    Rtrim(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto Rtrimmedsv(const StringView &str) -> StringView
{
    auto trimstr = StringView{str};
    Rtrimsv(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto Trimmed(const StringView &str) -> String
{
    auto trimstr = String{str};
    Trim(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto Trimmedsv(const StringView &str) -> StringView
{
    auto trimstr = StringView{str};
    Trimsv(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto Left(const StringView &str, const StringView::size_type len) -> String
{
    return String{Leftsv(str, len)};
}

[[nodiscard]] inline auto Leftsv(const StringView &str, const StringView::size_type len) -> StringView
{
    return str.Substr(0, len);
}

[[nodiscard]] inline auto Right(const StringView &str, const StringView::size_type len) -> String
{
    return String{Rightsv(str, len)};
}

[[nodiscard]] inline auto Rightsv(const StringView &str, const StringView::size_type len) -> StringView
{
    return str.Substr(std::size(str) - len);
}

[[nodiscard]] inline auto StrippedLeft(const StringView &str, const StringView::size_type len) -> String
{
    return String{StrippedLeftsv(str, len)};
}

[[nodiscard]] inline auto StrippedLeftsv(const StringView &str, const StringView::size_type len) -> StringView
{
    return str.Substr(len);
}

[[nodiscard]] inline auto StrippedRight(const StringView &str, const StringView::size_type len) -> String
{
    return String{StrippedRightsv(str, len)};
}

[[nodiscard]] inline auto StrippedRightsv(const StringView &str, const StringView::size_type len) -> StringView
{
    return str.Substr(0, std::size(str) - len);
}

[[nodiscard]] inline auto StrippedBoth(const StringView &str, const StringView::size_type len) -> String
{
    return String{StrippedBothsv(str, len)};
}

[[nodiscard]] inline auto StrippedBothsv(const StringView &str, const StringView::size_type len) -> StringView
{
    return str.Substr(len, std::size(str) - len - len);
}

template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedLeft(const StringView &str, const T c) -> String
{
    auto stripstr = String{str};
    CharStripLeft(stripstr, c);
    return stripstr;
}

template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedLeftsv(const StringView &str, const T c) -> StringView
{
    auto stripstr = StringView{str};
    CharStripLeftsv(stripstr, c);
    return stripstr;
}

template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedRight(const StringView &str, const T c) -> String
{
    auto stripstr = String{str};
    CharStripRight(stripstr, c);
    return stripstr;
}

template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedRightsv(const StringView &str, const T c) -> StringView
{
    auto stripstr = StringView{str};
    CharStripRightsv(stripstr, c);
    return stripstr;
}

template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedBoth(const StringView &str, const T c) -> String
{
    auto stripstr = String{str};
    CharStripBoth(stripstr, c);
    return stripstr;
}

template <Concepts::Utf8CharacterTypes T>
[[nodiscard]] inline auto CharStrippedBothsv(const StringView &str, const T c) -> StringView
{
    auto stripstr = StringView{str};
    CharStripBothsv(stripstr, c);
    return stripstr;
}

inline void StripLeft(String &str, const String::size_type len)
{
    str = StrippedLeft(str, len);
}

inline void StripLeftsv(StringView &str, const StringView::size_type len)
{
    str = StrippedLeftsv(str, len);
}

inline void StripRight(String &str, const String::size_type len)
{
    str = StrippedRight(str, len);
}

inline void StripRightsv(StringView &str, const StringView::size_type len)
{
    str = StrippedRightsv(str, len);
}

inline void StripBoth(String &str, const String::size_type len)
{
    str = StrippedBoth(str, len);
}

inline void StripBothsv(StringView &str, const StringView::size_type len)
{
    str = StrippedBothsv(str, len);
}

inline void CharStripLeft(String &str, const String::value_type c)
{
    str.Erase(std::begin(str), std::find_if(std::cbegin(str), std::cend(str), [c](const auto ch) { return c != ch; }));
}

inline void CharStripLeftsv(StringView &str, const StringView::value_type c)
{
    str.RemovePrefix(Container::CountUntil(std::cbegin(str), std::cend(str), [c](const auto ch) { return c != ch; }));
}

inline void CharStripRight(String &str, const String::value_type c)
{
    str.Erase(std::find_if(std::crbegin(str), std::crend(str), [c](const auto ch) { return c != ch; }).base(),
              std::end(str));
}

inline void CharStripRightsv(StringView &str, const StringView::value_type c)
{
    str.RemoveSuffix(
        Container::CountUntil(std::crbegin(str), std::crend(str), [c](const auto ch) { return c != ch; }));
}

inline void CharStripBoth(String &str, const String::value_type c)
{
    CharStripLeft(str, c);
    CharStripRight(str, c);
}

inline void CharStripBothsv(StringView &str, const StringView::value_type c)
{
    CharStripLeftsv(str, c);
    CharStripRightsv(str, c);
}

inline void Replace(String &str, const StringView &from, const StringView &to)
{
    if (from.Empty())
        return;

    auto startPos = String::size_type{};
    while ((startPos = str.Find(from, startPos)) != String::npos)
    {
        str.Replace(startPos, std::size(from), to);
        startPos += std::size(to);
    }
}

[[nodiscard]] inline auto ReplaceCopy(const StringView &str, const StringView &from, const StringView &to) -> String
{
    auto copy = String{str};
    Replace(copy, from, to);
    return copy;
}

inline void ToLower(String &str)
{
    const auto toLowerInternal = [](const auto c)
    { return std::use_facet<std::ctype<String::value_type>>(std::locale()).tolower(c); };
    std::transform(std::cbegin(str), std::cend(str), std::begin(str), toLowerInternal);
}

[[nodiscard]] inline auto ToLowerCopy(const StringView &str) -> String
{
    auto result = String{str};
    ToLower(result);
    return result;
}

inline void ToUpper(String &str)
{
    const auto toUpperInternal = [](const auto c)
    { return std::use_facet<std::ctype<String::value_type>>(std::locale()).toupper(c); };
    std::transform(std::cbegin(str), std::cend(str), std::begin(str), toUpperInternal);
}

[[nodiscard]] inline auto ToUpperCopy(const StringView &str) -> String
{
    auto result = String{str};
    ToUpper(result);
    return result;
}

[[nodiscard]] inline auto BeginsWith(const StringView &str, const StringView &val) -> bool
{
    if (std::size(str) < std::size(val))
        return false;

    return Leftsv(str, std::size(val)) == val;
}

[[nodiscard]] inline auto EndsWith(const StringView &str, const StringView &val) -> bool
{
    if (std::size(str) < std::size(val))
        return false;

    return Rightsv(str, std::size(val)) == val;
}

[[nodiscard]] inline auto Contains(const StringView &str, const StringView &val) -> bool
{
    return str.Find(val) != StringView::npos;
}

[[nodiscard]] inline auto Contains(const StringView &str, const StringView::value_type c) -> bool
{
    return str.Find(c) != StringView::npos;
}

[[nodiscard]] inline auto Uint8ToHexString(const std::uint8_t value) noexcept -> const char *
{
    static constexpr std::array<const char *, 256> HexLookup{
        "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b", "0c", "0d", "0e", "0f", "10", "11",
        "12", "13", "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f", "20", "21", "22", "23",
        "24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f", "30", "31", "32", "33", "34", "35",
        "36", "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f", "40", "41", "42", "43", "44", "45", "46", "47",
        "48", "49", "4a", "4b", "4c", "4d", "4e", "4f", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
        "5a", "5b", "5c", "5d", "5e", "5f", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b",
        "6c", "6d", "6e", "6f", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a", "7b", "7c", "7d",
        "7e", "7f", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
        "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b", "9c", "9d", "9e", "9f", "a0", "a1",
        "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af", "b0", "b1", "b2", "b3",
        "b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf", "c0", "c1", "c2", "c3", "c4", "c5",
        "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf", "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",
        "d8", "d9", "da", "db", "dc", "dd", "de", "df", "e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9",
        "ea", "eb", "ec", "ed", "ee", "ef", "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb",
        "fc", "fd", "fe", "ff"};
    return HexLookup[value];
}

} // namespace aeon::Common::string_utils
