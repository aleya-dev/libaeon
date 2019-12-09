// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/common/string.h>
#include <aeon/common/literals.h>
#include <aeon/common/container.h>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <sstream>
#include <iomanip>

namespace aeon::common::string
{

auto split(const std::string &str, const char delim, std::vector<std::string> &elements) -> std::vector<std::string> &
{
    std::stringstream ss{str};
    std::string item;

    while (std::getline(ss, item, delim))
    {
        elements.emplace_back(item);
    }

    return elements;
}

auto split(const std::string &str, const char delim) -> std::vector<std::string>
{
    std::vector<std::string> elements;
    return split(str, delim, elements);
}

auto splitsv(const std::string_view &str, const char delim, std::vector<std::string_view> &elements)
    -> std::vector<std::string_view>
{
    auto start = 0_size_t;
    auto pos = str.find_first_of(delim, start);

    while (pos != std::string_view::npos)
    {
        elements.emplace_back(str.substr(start, pos - start));
        start = pos + 1;
        pos = str.find_first_of(delim, start);
    }

    if (start < str.length())
        elements.emplace_back(str.substr(start, str.length() - start));

    return elements;
}

auto splitsv(const std::string_view &str, const char delim) -> std::vector<std::string_view>
{
    std::vector<std::string_view> elements;
    return splitsv(str, delim, elements);
}

void ltrim(std::string &str)
{
    str.erase(std::begin(str),
              std::find_if(std::begin(str), std::end(str), [](const int c) { return !std::isspace(c); }));
}

void ltrimsv(std::string_view &str)
{
    str.remove_prefix(
        container::count_until(std::begin(str), std::end(str), [](const int c) { return !std::isspace(c); }));
}

void rtrim(std::string &str)
{
    str.erase(std::find_if(std::rbegin(str), std::rend(str), [](const int c) { return !std::isspace(c); }).base(),
              std::end(str));
}

void rtrimsv(std::string_view &str)
{
    str.remove_suffix(
        container::count_until(std::rbegin(str), std::rend(str), [](const int c) { return !std::isspace(c); }));
}

void trim(std::string &str)
{
    ltrim(str);
    rtrim(str);
}

void trimsv(std::string_view &str)
{
    ltrimsv(str);
    rtrimsv(str);
}

auto ltrimmed(const std::string &str) -> std::string
{
    auto trimstr = str;
    ltrim(trimstr);
    return trimstr;
}

auto ltrimmedsv(const std::string_view &str) -> std::string_view
{
    auto trimstr = str;
    ltrimsv(trimstr);
    return trimstr;
}

auto rtrimmed(const std::string &str) -> std::string
{
    auto trimstr = str;
    rtrim(trimstr);
    return trimstr;
}

auto rtrimmedsv(const std::string_view &str) -> std::string_view
{
    auto trimstr = str;
    rtrimsv(trimstr);
    return trimstr;
}

auto trimmed(const std::string &str) -> std::string
{
    auto trimstr = str;
    trim(trimstr);
    return trimstr;
}

auto trimmedsv(const std::string_view &str) -> std::string_view
{
    auto trimstr = str;
    trimsv(trimstr);
    return trimstr;
}

auto left(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(0, len);
}

auto leftsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(0, len);
}

auto right(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(str.size() - len);
}

auto rightsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(str.size() - len);
}

auto stripped_left(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(len);
}

auto stripped_leftsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(len);
}

auto stripped_right(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(0, str.size() - len);
}

auto stripped_rightsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(0, str.size() - len);
}

auto stripped_both(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(len, str.size() - len - len);
}

auto stripped_bothsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(len, str.size() - len - len);
}

auto char_stripped_left(const std::string &str, const char c) -> std::string
{
    auto stripstr = str;
    char_strip_left(stripstr, c);
    return stripstr;
}

auto char_stripped_leftsv(const std::string_view &str, const char c) -> std::string_view
{
    auto stripstr = str;
    char_strip_leftsv(stripstr, c);
    return stripstr;
}

auto char_stripped_right(const std::string &str, const char c) -> std::string
{
    auto stripstr = str;
    char_strip_right(stripstr, c);
    return stripstr;
}

auto char_stripped_rightsv(const std::string_view &str, const char c) -> std::string_view
{
    auto stripstr = str;
    char_strip_rightsv(stripstr, c);
    return stripstr;
}

auto char_stripped_both(const std::string &str, const char c) -> std::string
{
    auto stripstr = str;
    char_strip_both(stripstr, c);
    return stripstr;
}

auto char_stripped_bothsv(const std::string_view &str, const char c) -> std::string_view
{
    auto stripstr = str;
    char_strip_bothsv(stripstr, c);
    return stripstr;
}

void strip_left(std::string &str, const std::size_t len)
{
    str = stripped_left(str, len);
}

void strip_leftsv(std::string_view &str, const std::size_t len)
{
    str = stripped_leftsv(str, len);
}

void strip_right(std::string &str, const std::size_t len)
{
    str = stripped_right(str, len);
}

void strip_rightsv(std::string_view &str, const std::size_t len)
{
    str = stripped_rightsv(str, len);
}

void strip_both(std::string &str, const std::size_t len)
{
    str = stripped_both(str, len);
}

void strip_bothsv(std::string_view &str, const std::size_t len)
{
    str = stripped_bothsv(str, len);
}

void char_strip_left(std::string &str, const char c)
{
    str.erase(std::begin(str), std::find_if(std::begin(str), std::end(str), [c](const int ch) { return c != ch; }));
}

void char_strip_leftsv(std::string_view &str, const char c)
{
    str.remove_prefix(container::count_until(std::begin(str), std::end(str), [c](const int ch) { return c != ch; }));
}

void char_strip_right(std::string &str, const char c)
{
    str.erase(std::find_if(std::rbegin(str), std::rend(str), [c](const int ch) { return c != ch; }).base(),
              std::end(str));
}

void char_strip_rightsv(std::string_view &str, const char c)
{
    str.remove_suffix(container::count_until(std::rbegin(str), std::rend(str), [c](const int ch) { return c != ch; }));
}

void char_strip_both(std::string &str, const char c)
{
    char_strip_left(str, c);
    char_strip_right(str, c);
}

void char_strip_bothsv(std::string_view &str, const char c)
{
    char_strip_leftsv(str, c);
    char_strip_rightsv(str, c);
}

void replace(std::string &str, const std::string &from, const std::string &to)
{
    if (from.empty())
        return;

    auto start_pos = 0_size_t;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

auto replace_copy(const std::string &str, const std::string &from, const std::string &to) -> std::string
{
    std::string copy = str;
    replace(copy, from, to);
    return copy;
}

void to_lower(std::string &str)
{
    const auto to_lower_internal = [](const char c) {
        return std::use_facet<std::ctype<char>>(std::locale()).tolower(c);
    };

    std::transform(std::begin(str), std::end(str), std::begin(str), to_lower_internal);
}

auto to_lower_copy(const std::string &str) -> std::string
{
    std::string result = str;
    to_lower(result);
    return result;
}

void to_upper(std::string &str)
{
    const auto to_upper_internal = [](const char c) {
        return std::use_facet<std::ctype<char>>(std::locale()).toupper(c);
    };

    std::transform(std::begin(str), std::end(str), std::begin(str), to_upper_internal);
}

auto to_upper_copy(const std::string &str) -> std::string
{
    std::string result = str;
    to_upper(result);
    return result;
}

auto begins_with(const std::string &str, const std::string &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return left(str, val.size()) == val;
}

auto begins_withsv(const std::string_view &str, const std::string_view &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return leftsv(str, val.size()) == val;
}

auto ends_with(const std::string &str, const std::string &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return right(str, val.size()) == val;
}

auto ends_withsv(const std::string_view &str, const std::string_view &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return rightsv(str, val.size()) == val;
}

auto contains(const std::string_view &str, const std::string_view &val) -> bool
{
    return str.find(val) != std::string::npos;
}

auto contains(const std::string_view &str, const char c) -> bool
{
    return str.find(c) != std::string::npos;
}

auto char_to_hex(const char c) -> std::string
{
    std::ostringstream ss;
    ss << '%' << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<short>(c & 0xff);
    return ss.str();
}

auto hex_to_char(const std::string &str) -> char
{
    if (str.empty())
        return 0;

    std::istringstream in(str);

    short c = 0;
    in >> std::hex >> c;

    if (in.fail())
        throw std::runtime_error("stream decode failure");

    return static_cast<char>(c & 0xff);
}

} // namespace aeon::common::string
