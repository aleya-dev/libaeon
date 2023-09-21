// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string_view.h>

namespace aeon::Common
{

inline constexpr String::String() noexcept
    : m_str{}
{
}

inline constexpr String::String(const value_type c) noexcept
    : m_str{c}
{
}

inline constexpr String::String(const char8_t c) noexcept
    : m_str{static_cast<value_type>(c)}
{
}

inline constexpr String::String(const size_type count, const value_type c) noexcept
    : m_str(count, c)
{
}

inline constexpr String::String(const size_type count, const char8_t c) noexcept
    : m_str(count, static_cast<value_type>(c))
{
}

inline constexpr String::String(const char *const str)
    : m_str{str}
{
}

inline String::String(const char8_t *const str)
    : m_str{reinterpret_cast<const char *const>(str)}
{
}

inline constexpr String::String(std::string str) noexcept
    : m_str{std::move(str)}
{
}

inline constexpr String::String(const std::u8string &str)
    : m_str{std::begin(str), std::end(str)}
{
}

inline constexpr String::String(const StringView &str) noexcept
    : m_str{str.m_str}
{
}

template <std::contiguous_iterator iterator_t>
inline constexpr String::String(iterator_t begin, iterator_t end) noexcept
    : m_str{begin, end}
{
}

inline constexpr auto String::operator=(const value_type *const str) -> String &
{
    Assign(str);
    return *this;
}

inline constexpr auto String::operator=(std::string str) -> String &
{
    Assign(std::move(str));
    return *this;
}

inline auto String::operator=(const char8_t *const str) -> String &
{
    Assign(str);
    return *this;
}

inline constexpr auto String::operator=(const std::u8string &str) -> String &
{
    Assign(str);
    return *this;
}

inline constexpr auto String::operator=(const StringView &str) -> String &
{
    Assign(str);
    return *this;
}

inline constexpr void String::Assign(const value_type *const str)
{
    m_str = str;
}

inline constexpr void String::Assign(std::string &&str)
{
    m_str = std::move(str);
}

inline void String::Assign(const char8_t *const str)
{
    m_str = reinterpret_cast<const char *const>(str);
}

inline constexpr void String::Assign(const std::u8string &str)
{
    m_str = std::string{std::begin(str), std::end(str)};
}

inline constexpr void String::Assign(const String &str)
{
    m_str = str.m_str;
}

constexpr void String::Assign(const StringView &str)
{
    m_str = str.m_str;
}

inline constexpr auto String::Insert(const size_type index, const value_type *const str) -> String &
{
    m_str.insert(index, str);
    return *this;
}

inline auto String::Insert(const size_type index, const char8_t *const str) -> String &
{
    m_str.insert(index, reinterpret_cast<const char *const>(str));
    return *this;
}

inline constexpr auto String::Insert(const size_type index, const std::string_view &str) -> String &
{
    m_str.insert(index, str);
    return *this;
}

inline auto String::Insert(const size_type index, const std::u8string_view &str) -> String &
{
    m_str.insert(index, reinterpret_cast<const char *const>(std::data(str)), std::size(str));
    return *this;
}

inline auto String::Insert(const size_type index, const String &str) -> String &
{
    m_str.insert(index, str.m_str);
    return *this;
}

inline auto String::Insert(const size_type index, const StringView &str) -> String &
{
    m_str.insert(index, str.m_str);
    return *this;
}

template <typename position_iterator_t, typename input_iterator_t>
inline auto String::Insert(const position_iterator_t pos, const input_iterator_t first, const input_iterator_t last)
    -> String &
{
    m_str.insert(pos, first, last);
    return *this;
}

inline constexpr auto String::Erase(const size_type index, const size_type count) -> String &
{
    m_str.erase(index, count);
    return *this;
}

inline constexpr auto String::Erase(const_iterator position) -> iterator
{
    return m_str.erase(position);
}

inline constexpr auto String::Erase(const_iterator first, const_iterator last) -> iterator
{
    return m_str.erase(first, last);
}

[[nodiscard]] inline constexpr auto String::Str() noexcept -> std::string &
{
    return m_str;
}

[[nodiscard]] inline constexpr auto String::Str() const noexcept -> const std::string &
{
    return m_str;
}

[[nodiscard]] inline auto String::U8Str() const noexcept -> std::u8string
{
    return std::u8string{reinterpret_cast<const char8_t *const>(std::data(m_str)), std::size(m_str)};
}

[[nodiscard]] inline constexpr auto String::Size() const noexcept -> size_type
{
    return std::size(m_str);
}

[[nodiscard]] inline constexpr auto String::Capacity() const noexcept -> size_type
{
    return m_str.capacity();
}

[[nodiscard]] inline constexpr auto String::Data() noexcept -> pointer
{
    return std::data(m_str);
}

[[nodiscard]] inline constexpr auto String::Data() const noexcept -> const_pointer
{
    return std::data(m_str);
}

inline constexpr void String::ShrinkToFit()
{
    m_str.shrink_to_fit();
}

[[nodiscard]] inline constexpr auto String::CStr() const noexcept -> const_pointer
{
    return m_str.c_str();
}

[[nodiscard]] inline auto String::U8CStr() const noexcept -> const char8_t *
{
    return reinterpret_cast<const char8_t *const>(CStr());
}

inline constexpr void String::Reserve(const size_type size)
{
    m_str.reserve(size);
}

inline constexpr void String::Resize(const size_type count)
{
    m_str.resize(count);
}

[[nodiscard]] inline constexpr auto String::Compare(const String &str) const noexcept -> int
{
    return m_str.compare(str.m_str);
}

[[nodiscard]] inline constexpr auto String::Compare(const StringView &str) const noexcept -> int
{
    return m_str.compare(str.m_str);
}

[[nodiscard]] inline constexpr auto String::Compare(const std::string &str) const noexcept -> int
{
    return m_str.compare(str);
}

[[nodiscard]] inline auto String::Compare(const std::u8string &str) const noexcept -> int
{
    return m_str.compare(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)});
}

[[nodiscard]] inline constexpr auto String::Compare(const value_type *const str) const noexcept -> int
{
    return m_str.compare(str);
}

[[nodiscard]] inline auto String::Compare(const char8_t *const str) const noexcept -> int
{
    return m_str.compare(reinterpret_cast<const char *const>(str));
}

[[nodiscard]] inline constexpr auto String::Compare(const size_type pos, const size_type count,
                                                    const StringView str) const -> int
{
    return m_str.compare(pos, count, str.m_str);
}

inline constexpr auto String::operator==(const String &str) const -> bool
{
    return m_str == str.m_str;
}

inline constexpr auto String::operator==(const StringView &str) const -> bool
{
    return m_str == str.m_str;
}

inline constexpr auto String::operator==(const std::string &str) const -> bool
{
    return m_str == str;
}

inline auto String::operator==(const std::u8string &str) const -> bool
{
    return m_str == std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto String::operator==(const value_type *const str) const -> bool
{
    return m_str == str;
}

inline auto String::operator==(const char8_t *const str) const -> bool
{
    return m_str == reinterpret_cast<const char *const>(str);
}

#if __cplusplus < 202002L
inline constexpr auto String::operator!=(const String &str) const -> bool
{
    return !(*this == str);
}

inline constexpr auto String::operator!=(const StringView &str) const -> bool
{
    return !(*this == str);
}

inline constexpr auto string::operator!=(const std::string &str) const -> bool
{
    return !(*this == str);
}

inline auto String::operator!=(const std::u8string &str) const -> bool
{
    return !(*this == str);
}

inline constexpr auto String::operator!=(const value_type *const str) const -> bool
{
    return !(*this == str);
}

inline auto String::operator!=(const char8_t *const str) const -> bool
{
    return !(*this == str);
}
#endif

inline constexpr auto String::operator<(const String &str) const -> bool
{
    return m_str < str.m_str;
}

inline constexpr auto String::operator<(const StringView &str) const -> bool
{
    return m_str < str.m_str;
}

inline constexpr auto String::operator<(const std::string &str) const -> bool
{
    return m_str < str;
}

inline auto String::operator<(const std::u8string &str) const -> bool
{
    return m_str < std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto String::operator<(const value_type *const str) const -> bool
{
    return m_str < str;
}

inline auto String::operator<(const char8_t *const str) const -> bool
{
    return m_str < reinterpret_cast<const char *const>(str);
}

inline constexpr auto String::operator<=(const String &str) const -> bool
{
    return m_str <= str.m_str;
}

inline constexpr auto String::operator<=(const StringView &str) const -> bool
{
    return m_str <= str.m_str;
}

inline constexpr auto String::operator<=(const std::string &str) const -> bool
{
    return m_str <= str;
}

inline auto String::operator<=(const std::u8string &str) const -> bool
{
    return m_str <= std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto String::operator<=(const value_type *const str) const -> bool
{
    return m_str <= str;
}

inline auto String::operator<=(const char8_t *const str) const -> bool
{
    return m_str <= reinterpret_cast<const char *const>(str);
}

inline constexpr auto String::operator>(const String &str) const -> bool
{
    return m_str > str.m_str;
}

inline constexpr auto String::operator>(const StringView &str) const -> bool
{
    return m_str > str.m_str;
}

inline constexpr auto String::operator>(const std::string &str) const -> bool
{
    return m_str > str;
}

inline auto String::operator>(const std::u8string &str) const -> bool
{
    return m_str > std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto String::operator>(const value_type *const str) const -> bool
{
    return m_str > str;
}

inline auto String::operator>(const char8_t *const str) const -> bool
{
    return m_str > reinterpret_cast<const char *const>(str);
}

inline constexpr auto String::operator>=(const String &str) const -> bool
{
    return m_str >= str.m_str;
}

inline constexpr auto String::operator>=(const StringView &str) const -> bool
{
    return m_str >= str.m_str;
}

inline constexpr auto String::operator>=(const std::string &str) const -> bool
{
    return m_str >= str;
}

inline auto String::operator>=(const std::u8string &str) const -> bool
{
    return m_str >= std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto String::operator>=(const value_type *const str) const -> bool
{
    return m_str >= str;
}

inline auto String::operator>=(const char8_t *const str) const -> bool
{
    return m_str >= reinterpret_cast<const char *const>(str);
}

inline constexpr auto String::Append(const value_type *const str) -> String &
{
    m_str.append(str);
    return *this;
}

inline constexpr auto String::Append(const value_type *const str, const size_type size) -> String &
{
    m_str.append(str, size);
    return *this;
}

inline auto String::Append(const char8_t *const str, const size_type size) -> String &
{
    m_str.append(reinterpret_cast<const char *const>(str), size);
    return *this;
}

inline auto String::Append(const char8_t *const str) -> String &
{
    m_str.append(reinterpret_cast<const char *const>(str));
    return *this;
}

inline constexpr auto String::Append(const std::string &str) -> String &
{
    m_str.append(str);
    return *this;
}

inline auto String::Append(const std::u8string &str) -> String &
{
    m_str.append(std::begin(str), std::end(str));
    return *this;
}

inline constexpr auto String::Append(const String &str) -> String &
{
    m_str.append(str.m_str);
    return *this;
}

inline constexpr auto String::Append(const StringView &str) -> String &
{
    m_str.append(str.m_str);
    return *this;
}

template <std::contiguous_iterator iterator_t>
inline constexpr auto String::Append(iterator_t begin, iterator_t end) noexcept -> String &
{
    m_str.append(begin, end);
    return *this;
}

inline constexpr auto String::operator+=(const char *str) -> String &
{
    m_str.append(str);
    return *this;
}

inline auto String::operator+=(const char8_t *str) -> String &
{
    m_str += reinterpret_cast<const char *const>(str);
    return *this;
}

inline constexpr auto String::operator+=(const std::string &str) -> String &
{
    m_str.append(str);
    return *this;
}

inline constexpr auto String::operator+=(const std::string_view &str) -> String &
{
    m_str += str;
    return *this;
}

inline auto String::operator+=(const std::u8string_view &str) -> String &
{
    m_str += std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
    return *this;
}

inline constexpr auto String::operator+=(const String &str) -> String &
{
    m_str += str.m_str;
    return *this;
}

inline constexpr auto String::operator+=(const StringView &str) -> String &
{
    m_str += str.m_str;
    return *this;
}

inline constexpr auto String::operator+=(const value_type c) -> String &
{
    m_str += c;
    return *this;
}

inline constexpr auto String::operator+=(const char8_t c) -> String &
{
    m_str += static_cast<const char>(c);
    return *this;
}

[[nodiscard]] inline constexpr auto String::AsStdStringView() noexcept -> std::string_view
{
    return m_str;
}

[[nodiscard]] inline constexpr auto String::AsStdStringView() const noexcept -> std::string_view
{
    return m_str;
}

[[nodiscard]] inline auto String::AsStdU8StringView() noexcept -> std::u8string_view
{
    return std::u8string_view{reinterpret_cast<char8_t *>(std::data(m_str)), std::size(m_str)};
}

[[nodiscard]] inline auto String::AsStdU8StringView() const noexcept -> std::u8string_view
{
    return std::u8string_view{reinterpret_cast<const char8_t *const>(std::data(m_str)), std::size(m_str)};
}

inline constexpr void String::Clear()
{
    m_str.clear();
}

[[nodiscard]] inline constexpr auto String::Empty() const noexcept -> bool
{
    return m_str.empty();
}

[[nodiscard]] inline constexpr auto String::At(const size_type pos) -> reference
{
    return m_str.at(pos);
}

[[nodiscard]] inline constexpr auto String::At(const size_type pos) const -> const_reference
{
    return m_str.at(pos);
}

[[nodiscard]] inline constexpr auto String::operator[](const size_type pos) -> reference
{
    return m_str[pos];
}

[[nodiscard]] inline constexpr auto String::operator[](const size_type pos) const -> const_reference
{
    return m_str[pos];
}

[[nodiscard]] inline constexpr auto String::Front() noexcept -> reference
{
    return m_str.front();
}

[[nodiscard]] inline constexpr auto String::Front() const noexcept -> const_reference
{
    return m_str.front();
}

[[nodiscard]] inline constexpr auto String::Back() noexcept -> reference
{
    return m_str.back();
}

[[nodiscard]] inline constexpr auto String::Back() const noexcept -> const_reference
{
    return m_str.back();
}

[[nodiscard]] inline constexpr auto String::begin() noexcept -> iterator
{
    return m_str.begin();
}

[[nodiscard]] inline constexpr auto String::begin() const noexcept -> const_iterator
{
    return m_str.begin();
}

[[nodiscard]] inline constexpr auto String::cbegin() const noexcept -> const_iterator
{
    return m_str.cbegin();
}

[[nodiscard]] inline constexpr auto String::end() noexcept -> iterator
{
    return m_str.end();
}

[[nodiscard]] inline constexpr auto String::end() const noexcept -> const_iterator
{
    return m_str.end();
}

[[nodiscard]] inline constexpr auto String::cend() const noexcept -> const_iterator
{
    return m_str.cend();
}

[[nodiscard]] inline constexpr auto String::rbegin() noexcept -> reverse_iterator
{
    return m_str.rbegin();
}

[[nodiscard]] inline constexpr auto String::rbegin() const noexcept -> const_reverse_iterator
{
    return m_str.rbegin();
}

[[nodiscard]] inline constexpr auto String::crbegin() const noexcept -> const_reverse_iterator
{
    return m_str.crbegin();
}

[[nodiscard]] inline constexpr auto String::rend() noexcept -> reverse_iterator
{
    return m_str.rend();
}

[[nodiscard]] inline constexpr auto String::rend() const noexcept -> const_reverse_iterator
{
    return m_str.rend();
}

[[nodiscard]] inline constexpr auto String::crend() const noexcept -> const_reverse_iterator
{
    return m_str.crend();
}

[[nodiscard]] inline constexpr auto String::StartsWith(const std::string_view &str) const noexcept -> bool
{
    return m_str.starts_with(str);
}

[[nodiscard]] inline auto String::StartsWith(const std::u8string_view &str) const noexcept -> bool
{
    return m_str.starts_with(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)});
}

[[nodiscard]] inline constexpr auto String::StartsWith(const String &str) const noexcept -> bool
{
    return m_str.starts_with(str.m_str);
}

[[nodiscard]] inline constexpr auto String::StartsWith(const StringView &str) const noexcept -> bool
{
    return m_str.starts_with(str.m_str);
}

[[nodiscard]] inline constexpr auto String::StartsWith(const value_type c) const noexcept -> bool
{
    return m_str.starts_with(c);
}

[[nodiscard]] inline constexpr auto String::StartsWith(const char8_t c) const noexcept -> bool
{
    return m_str.starts_with(static_cast<const char>(c));
}

[[nodiscard]] inline constexpr auto String::EndsWith(const std::string_view &str) const noexcept -> bool
{
    return m_str.ends_with(str);
}

[[nodiscard]] inline auto String::EndsWith(const std::u8string_view &str) const noexcept -> bool
{
    return m_str.ends_with(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)});
}

[[nodiscard]] inline constexpr auto String::EndsWith(const String &str) const noexcept -> bool
{
    return m_str.ends_with(str.m_str);
}

[[nodiscard]] inline constexpr auto String::EndsWith(const StringView &str) const noexcept -> bool
{
    return m_str.ends_with(str.m_str);
}

[[nodiscard]] inline constexpr auto String::EndsWith(const value_type c) const noexcept -> bool
{
    return m_str.ends_with(c);
}

[[nodiscard]] inline constexpr auto String::EndsWith(const char8_t c) const noexcept -> bool
{
    return m_str.ends_with(static_cast<const char>(c));
}

[[nodiscard]] inline constexpr auto String::Substr(const size_type pos, const size_type count) const -> String
{
    return m_str.substr(pos, count);
}

[[nodiscard]] inline auto String::Find(const std::string_view &str, const size_type pos) const noexcept -> size_type
{
    return m_str.find(str, pos);
}

[[nodiscard]] inline auto String::Find(const std::u8string_view &str, const size_type pos) const noexcept -> size_type
{
    return m_str.find(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)}, pos);
}

[[nodiscard]] inline constexpr auto String::Find(const String &str, const size_type pos) const noexcept -> size_type
{
    return m_str.find(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::Find(const StringView &str, const size_type pos) const noexcept -> size_type
{
    return m_str.find(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::Find(const value_type *str, const size_type pos) const -> size_type
{
    return m_str.find(str, pos);
}

[[nodiscard]] inline auto String::Find(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.find(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto String::Find(const value_type c, const size_type pos) const -> size_type
{
    return m_str.find(c, pos);
}

[[nodiscard]] inline constexpr auto String::Find(const char8_t c, const size_type pos) const -> size_type
{
    return m_str.find(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto String::Rfind(const std::string_view &str, const size_type pos) const noexcept -> size_type
{
    return m_str.rfind(str, pos);
}

[[nodiscard]] inline auto String::Rfind(const std::u8string_view &str, const size_type pos) const noexcept -> size_type
{
    return m_str.rfind(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)}, pos);
}

[[nodiscard]] inline constexpr auto String::Rfind(const String &str, const size_type pos) const noexcept -> size_type
{
    return m_str.rfind(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::Rfind(const StringView &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.rfind(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::Rfind(const value_type *str, const size_type pos) const -> size_type
{
    return m_str.rfind(str, pos);
}

[[nodiscard]] inline auto String::Rfind(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.rfind(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto String::Rfind(const value_type c, const size_type pos) const -> size_type
{
    return m_str.rfind(c, pos);
}

[[nodiscard]] inline constexpr auto String::Rfind(const char8_t c, const size_type pos) const -> size_type
{
    return m_str.rfind(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto String::FindFirstOf(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_of(str, pos);
}

[[nodiscard]] inline auto String::FindFirstOf(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                              pos);
}

[[nodiscard]] inline constexpr auto String::FindFirstOf(const String &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::FindFirstOf(const StringView &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::FindFirstOf(const value_type *str, const size_type pos) const -> size_type
{
    return m_str.find_first_of(str, pos);
}

[[nodiscard]] inline auto String::FindFirstOf(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.find_first_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto String::FindFirstOf(const value_type c, const size_type pos) const -> size_type
{
    return m_str.find_first_of(c, pos);
}

[[nodiscard]] inline constexpr auto String::FindFirstOf(const char8_t c, const size_type pos) const -> size_type
{
    return m_str.find_first_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto String::FindFirstNotOf(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_not_of(str, pos);
}

[[nodiscard]] inline auto String::FindFirstNotOf(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_not_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                                  pos);
}

[[nodiscard]] inline constexpr auto String::FindFirstNotOf(const String &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_not_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::FindFirstNotOf(const StringView &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_not_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::FindFirstNotOf(const value_type *str, const size_type pos) const
    -> size_type
{
    return m_str.find_first_not_of(str, pos);
}

[[nodiscard]] inline auto String::FindFirstNotOf(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.find_first_not_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto String::FindFirstNotOf(const value_type c, const size_type pos) const
    -> size_type
{
    return m_str.find_first_not_of(c, pos);
}

[[nodiscard]] inline constexpr auto String::FindFirstNotOf(const char8_t c, const size_type pos) const -> size_type
{
    return m_str.find_first_not_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto String::FindLastOf(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_of(str, pos);
}

[[nodiscard]] inline auto String::FindLastOf(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                             pos);
}

[[nodiscard]] inline constexpr auto String::FindLastOf(const String &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::FindLastOf(const StringView &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::FindLastOf(const value_type *str, const size_type pos) const -> size_type
{
    return m_str.find_last_of(str, pos);
}

[[nodiscard]] inline auto String::FindLastOf(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.find_last_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto String::FindLastOf(const value_type c, const size_type pos) const -> size_type
{
    return m_str.find_last_of(c, pos);
}

[[nodiscard]] inline constexpr auto String::FindLastOf(const char8_t c, const size_type pos) const -> size_type
{
    return m_str.find_last_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto String::FindLastNotOf(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_not_of(str, pos);
}

[[nodiscard]] inline auto String::FindLastNotOf(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_not_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                                 pos);
}

[[nodiscard]] inline constexpr auto String::FindLastNotOf(const String &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_not_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::FindLastNotOf(const StringView &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_not_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto String::FindLastNotOf(const value_type *str, const size_type pos) const
    -> size_type
{
    return m_str.find_last_not_of(str, pos);
}

[[nodiscard]] inline auto String::FindLastNotOf(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.find_last_not_of(reinterpret_cast<const char *const>(str), pos);
}

inline void String::Replace(const size_type pos, const size_type count, const StringView &str)
{
    m_str.replace(pos, count, str.m_str);
}

[[nodiscard]] inline constexpr auto String::FindLastNotOf(const value_type c, const size_type pos) const -> size_type
{
    return m_str.find_last_not_of(c, pos);
}

[[nodiscard]] inline constexpr auto String::FindLastNotOf(const char8_t c, const size_type pos) const -> size_type
{
    return m_str.find_last_not_of(static_cast<const char>(c), pos);
}

inline constexpr auto operator+(const String &lhs, const String &rhs) -> String
{
    return lhs.Str() + rhs.Str();
}

inline constexpr auto operator+(const String &lhs, const std::string &rhs) -> String
{
    return lhs.Str() + rhs;
}

inline constexpr auto operator+(const std::string &lhs, const String &rhs) -> String
{
    return lhs + rhs.Str();
}

inline auto operator+(const String &lhs, const std::u8string &rhs) -> String
{
    return lhs + String{rhs};
}

inline auto operator+(const std::u8string &lhs, const String &rhs) -> String
{
    return String{lhs} + rhs;
}

inline constexpr auto operator+(const String &lhs, const char *const rhs) -> String
{
    return lhs.Str() + rhs;
}

inline constexpr auto operator+(const char *const lhs, const String &rhs) -> String
{
    return lhs + rhs.Str();
}

inline auto operator+(const String &lhs, const char8_t *const rhs) -> String
{
    return lhs.Str() + reinterpret_cast<const char *const>(rhs);
}

inline auto operator+(const char8_t *const lhs, const String &rhs) -> String
{
    return reinterpret_cast<const char *const>(lhs) + rhs.Str();
}

inline constexpr auto operator+(const StringView &lhs, const String &rhs) -> String
{
    return lhs.AsStdStringView() + rhs.Str();
}

inline constexpr auto operator+(const StringView &lhs, const StringView &rhs) -> String
{
    return lhs.AsStdStringView() + rhs.AsStdStringView();
}

inline constexpr auto operator+(const StringView &lhs, const std::string &rhs) -> String
{
    return lhs.AsStdStringView() + rhs;
}

inline constexpr auto operator+(const std::string &lhs, const StringView &rhs) -> String
{
    return lhs + rhs.AsStdStringView();
}

inline auto operator+(const StringView &lhs, const std::u8string &rhs) -> String
{
    return std::string{lhs.AsStdStringView()} + reinterpret_cast<const char *const>(std::data(rhs));
}

inline auto operator+(const std::u8string &lhs, const StringView &rhs) -> String
{
    return std::string_view{reinterpret_cast<const char *const>(std::data(lhs)), std::size(lhs)} +
           rhs.AsStdStringView();
}

inline constexpr auto operator+(const StringView &lhs, const char *const rhs) -> String
{
    return lhs.AsStdStringView() + rhs;
}

inline constexpr auto operator+(const char *const lhs, const StringView &rhs) -> String
{
    return lhs + rhs.AsStdStringView();
}

inline auto operator+(const StringView &lhs, const char8_t *const rhs) -> String
{
    return lhs.AsStdStringView() + reinterpret_cast<const char *const>(rhs);
}

inline auto operator+(const char8_t *const lhs, const StringView &rhs) -> String
{
    return reinterpret_cast<const char *const>(lhs) + rhs.AsStdStringView();
}

inline auto operator<<(std::ostream &os, const String &str) -> std::ostream &
{
    return os << str.Str();
}

} // namespace aeon::Common
