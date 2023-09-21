// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>

namespace aeon::Common
{

inline constexpr StringView::StringView() noexcept
    : m_str{}
{
}

inline constexpr StringView::StringView(const char *const str)
    : m_str{str}
{
}

inline StringView::StringView(const char8_t *const str)
    : m_str{reinterpret_cast<const char *const>(str)}
{
}

inline constexpr StringView::StringView(const char *const str, const size_type size)
    : m_str{str, size}
{
}

inline StringView::StringView(const char8_t *const str, const size_type size)
    : m_str{reinterpret_cast<const char *const>(str), size}
{
}

inline constexpr StringView::StringView(const std::string &str) noexcept
    : m_str{str}
{
}

inline StringView::StringView(const std::u8string &str)
    : m_str{reinterpret_cast<const char *const>(std::data(str)), std::size(str)}
{
}

inline constexpr StringView::StringView(const std::string_view &str) noexcept
    : m_str{str}
{
}

inline constexpr StringView::StringView(const String &str) noexcept
    : m_str{str.m_str}
{
}

inline StringView::StringView(const std::u8string_view &str)
    : m_str{reinterpret_cast<const char *const>(std::data(str)), std::size(str)}
{
}

template <std::contiguous_iterator iterator_t>
inline constexpr StringView::StringView(iterator_t begin, iterator_t end) noexcept
{
    using result_type = std::basic_string_view<typename std::iterator_traits<iterator_t>::value_type>;

    if (begin == end)
        return;

    m_str = {&*begin, static_cast<typename result_type::size_type>(
                         std::max(std::distance(begin, end), typename result_type::difference_type{}))};
}

inline constexpr auto StringView::operator=(const value_type *const str) -> StringView &
{
    Assign(str);
    return *this;
}

inline constexpr auto StringView::operator=(const std::string &str) -> StringView &
{
    Assign(str);
    return *this;
}

inline auto StringView::operator=(const char8_t *const str) -> StringView &
{
    Assign(str);
    return *this;
}

inline auto StringView::operator=(const std::u8string &str) -> StringView &
{
    Assign(str);
    return *this;
}

inline constexpr void StringView::Assign(const value_type *const str)
{
    m_str = str;
}

inline constexpr void StringView::Assign(const std::string &str)
{
    m_str = str;
}

inline void StringView::Assign(const char8_t *const str)
{
    m_str = reinterpret_cast<const char *const>(str);
}

inline void StringView::Assign(const std::u8string &str)
{
    m_str = std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr void StringView::Assign(const String &str)
{
    m_str = str.m_str;
}

[[nodiscard]] inline constexpr auto StringView::size() const noexcept -> size_type
{
    return std::size(m_str);
}

[[nodiscard]] inline constexpr auto StringView::data() const noexcept -> const_pointer
{
    return std::data(m_str);
}

[[nodiscard]] inline constexpr auto StringView::Compare(const String &str) const noexcept -> int
{
    return m_str.compare(str.m_str);
}

[[nodiscard]] inline constexpr auto StringView::Compare(const std::string &str) const noexcept -> int
{
    return m_str.compare(str);
}

[[nodiscard]] inline auto StringView::Compare(const std::u8string &str) const noexcept -> int
{
    return m_str.compare(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)});
}

[[nodiscard]] inline constexpr auto StringView::Compare(const value_type *const str) const noexcept -> int
{
    return m_str.compare(str);
}

[[nodiscard]] inline auto StringView::Compare(const char8_t *const str) const noexcept -> int
{
    return m_str.compare(reinterpret_cast<const char *const>(str));
}

[[nodiscard]] inline constexpr auto StringView::Compare(const size_type pos, const size_type count,
                                                        const StringView str) const -> int
{
    return m_str.compare(pos, count, str.m_str);
}

inline constexpr auto StringView::operator==(const String &str) const -> bool
{
    return m_str == str.m_str;
}

inline constexpr auto StringView::operator==(const StringView &str) const -> bool
{
    return m_str == str.m_str;
}

inline constexpr auto StringView::operator==(const std::string &str) const -> bool
{
    return m_str == str;
}

inline auto StringView::operator==(const std::u8string &str) const -> bool
{
    return m_str == std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto StringView::operator==(const value_type *const str) const -> bool
{
    return m_str == str;
}

inline auto StringView::operator==(const char8_t *const str) const -> bool
{
    return m_str == reinterpret_cast<const char *const>(str);
}

#if __cplusplus < 202002L
inline constexpr auto StringView::operator!=(const String &str) const -> bool
{
    return !(*this == str);
}

inline constexpr auto StringView::operator!=(const StringView &str) const -> bool
{
    return !(*this == str);
}

inline constexpr auto StringView::operator!=(const std::string &str) const -> bool
{
    return !(*this == str);
}

inline auto StringView::operator!=(const std::u8string &str) const -> bool
{
    return !(*this == str);
}

inline constexpr auto StringView::operator!=(const value_type *const str) const -> bool
{
    return !(*this == str);
}

inline auto StringView::operator!=(const char8_t *const str) const -> bool
{
    return !(*this == str);
}
#endif

inline constexpr auto StringView::operator<(const String &str) const -> bool
{
    return m_str < str.m_str;
}

inline constexpr auto StringView::operator<(const StringView &str) const -> bool
{
    return m_str < str.m_str;
}

inline constexpr auto StringView::operator<(const std::string &str) const -> bool
{
    return m_str < str;
}

inline auto StringView::operator<(const std::u8string &str) const -> bool
{
    return m_str < std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto StringView::operator<(const value_type *const str) const -> bool
{
    return m_str < str;
}

inline auto StringView::operator<(const char8_t *const str) const -> bool
{
    return m_str < reinterpret_cast<const char *const>(str);
}

inline constexpr auto StringView::operator<=(const String &str) const -> bool
{
    return m_str <= str.m_str;
}

inline constexpr auto StringView::operator<=(const StringView &str) const -> bool
{
    return m_str <= str.m_str;
}

inline constexpr auto StringView::operator<=(const std::string &str) const -> bool
{
    return m_str <= str;
}

inline auto StringView::operator<=(const std::u8string &str) const -> bool
{
    return m_str <= std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto StringView::operator<=(const value_type *const str) const -> bool
{
    return m_str <= str;
}

inline auto StringView::operator<=(const char8_t *const str) const -> bool
{
    return m_str <= reinterpret_cast<const char *const>(str);
}

inline constexpr auto StringView::operator>(const String &str) const -> bool
{
    return m_str > str.m_str;
}

inline constexpr auto StringView::operator>(const StringView &str) const -> bool
{
    return m_str > str.m_str;
}

inline constexpr auto StringView::operator>(const std::string &str) const -> bool
{
    return m_str > str;
}

inline auto StringView::operator>(const std::u8string &str) const -> bool
{
    return m_str > std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto StringView::operator>(const value_type *const str) const -> bool
{
    return m_str > str;
}

inline auto StringView::operator>(const char8_t *const str) const -> bool
{
    return m_str > reinterpret_cast<const char *const>(str);
}

inline constexpr auto StringView::operator>=(const String &str) const -> bool
{
    return m_str >= str.m_str;
}

inline constexpr auto StringView::operator>=(const StringView &str) const -> bool
{
    return m_str >= str.m_str;
}

inline constexpr auto StringView::operator>=(const std::string &str) const -> bool
{
    return m_str >= str;
}

inline auto StringView::operator>=(const std::u8string &str) const -> bool
{
    return m_str >= std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto StringView::operator>=(const value_type *const str) const -> bool
{
    return m_str >= str;
}

inline auto StringView::operator>=(const char8_t *const str) const -> bool
{
    return m_str >= reinterpret_cast<const char *const>(str);
}

[[nodiscard]] inline constexpr auto StringView::AsStdStringView() noexcept -> std::string_view
{
    return m_str;
}

[[nodiscard]] inline constexpr auto StringView::AsStdStringView() const noexcept -> std::string_view
{
    return m_str;
}

[[nodiscard]] inline auto StringView::AsStdU8StringView() noexcept -> std::u8string_view
{
    return std::u8string_view{reinterpret_cast<const char8_t *>(std::data(m_str)), std::size(m_str)};
}

[[nodiscard]] inline auto StringView::AsStdU8StringView() const noexcept -> std::u8string_view
{
    return std::u8string_view{reinterpret_cast<const char8_t *const>(std::data(m_str)), std::size(m_str)};
}

[[nodiscard]] inline constexpr auto StringView::Empty() const noexcept -> bool
{
    return m_str.empty();
}

[[nodiscard]] inline constexpr auto StringView::At(const size_type pos) const -> const_reference
{
    return m_str.at(pos);
}

[[nodiscard]] inline constexpr auto StringView::operator[](const size_type pos) const -> const_reference
{
    return m_str[pos];
}

[[nodiscard]] inline constexpr auto StringView::front() const noexcept -> const_reference
{
    return m_str.front();
}

[[nodiscard]] inline constexpr auto StringView::back() const noexcept -> const_reference
{
    return m_str.back();
}

[[nodiscard]] inline constexpr auto StringView::begin() const noexcept -> const_iterator
{
    return m_str.begin();
}

[[nodiscard]] inline constexpr auto StringView::cbegin() const noexcept -> const_iterator
{
    return m_str.cbegin();
}

[[nodiscard]] inline constexpr auto StringView::end() const noexcept -> const_iterator
{
    return m_str.end();
}

[[nodiscard]] inline constexpr auto StringView::cend() const noexcept -> const_iterator
{
    return m_str.cend();
}

[[nodiscard]] inline constexpr auto StringView::rbegin() noexcept -> reverse_iterator
{
    return m_str.rbegin();
}

[[nodiscard]] inline constexpr auto StringView::rbegin() const noexcept -> const_reverse_iterator
{
    return m_str.rbegin();
}

[[nodiscard]] inline constexpr auto StringView::crbegin() const noexcept -> const_reverse_iterator
{
    return m_str.crbegin();
}

[[nodiscard]] inline constexpr auto StringView::rend() noexcept -> reverse_iterator
{
    return m_str.rend();
}

[[nodiscard]] inline constexpr auto StringView::rend() const noexcept -> const_reverse_iterator
{
    return m_str.rend();
}

[[nodiscard]] inline constexpr auto StringView::crend() const noexcept -> const_reverse_iterator
{
    return m_str.crend();
}

[[nodiscard]] inline constexpr auto StringView::StartsWith(const std::string_view &str) const noexcept -> bool
{
    return m_str.starts_with(str);
}

[[nodiscard]] inline auto StringView::StartsWith(const std::u8string_view &str) const noexcept -> bool
{
    return m_str.starts_with(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)});
}

[[nodiscard]] inline constexpr auto StringView::StartsWith(const String &str) const noexcept -> bool
{
    return m_str.starts_with(str.m_str);
}

[[nodiscard]] inline constexpr auto StringView::StartsWith(const value_type c) const noexcept -> bool
{
    return m_str.starts_with(c);
}

[[nodiscard]] inline constexpr auto StringView::StartsWith(const char8_t c) const noexcept -> bool
{
    return m_str.starts_with(static_cast<const char>(c));
}

[[nodiscard]] inline constexpr auto StringView::EndsWith(const std::string_view &str) const noexcept -> bool
{
    return m_str.ends_with(str);
}

[[nodiscard]] inline auto StringView::EndsWith(const std::u8string_view &str) const noexcept -> bool
{
    return m_str.ends_with(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)});
}

[[nodiscard]] inline constexpr auto StringView::EndsWith(const String &str) const noexcept -> bool
{
    return m_str.ends_with(str.m_str);
}

[[nodiscard]] inline constexpr auto StringView::EndsWith(const value_type c) const noexcept -> bool
{
    return m_str.ends_with(c);
}

[[nodiscard]] inline constexpr auto StringView::EndsWith(const char8_t c) const noexcept -> bool
{
    return m_str.ends_with(static_cast<const char>(c));
}

[[nodiscard]] inline constexpr auto StringView::Substr(const size_type pos, const size_type count) const -> StringView
{
    return m_str.substr(pos, count);
}

[[nodiscard]] inline auto StringView::Find(const std::string_view &str, const size_type pos) const noexcept -> size_type
{
    return m_str.find(str, pos);
}

[[nodiscard]] inline auto StringView::Find(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)}, pos);
}

[[nodiscard]] inline constexpr auto StringView::Find(const String &str, const size_type pos) const noexcept -> size_type
{
    return m_str.find(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto StringView::Find(const StringView &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto StringView::Find(const value_type *str, const size_type pos) const -> size_type
{
    return m_str.find(str, pos);
}

[[nodiscard]] inline auto StringView::Find(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.find(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto StringView::Find(const value_type c, const size_type pos) const -> size_type
{
    return m_str.find(c, pos);
}

[[nodiscard]] inline constexpr auto StringView::Find(const char8_t c, const size_type pos) const -> size_type
{
    return m_str.find(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto StringView::Rfind(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.rfind(str, pos);
}

[[nodiscard]] inline auto StringView::Rfind(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.rfind(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)}, pos);
}

[[nodiscard]] inline constexpr auto StringView::Rfind(const String &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.rfind(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto StringView::Rfind(const value_type *str, const size_type pos) const -> size_type
{
    return m_str.rfind(str, pos);
}

[[nodiscard]] inline auto StringView::Rfind(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.rfind(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto StringView::Rfind(const value_type c, const size_type pos) const -> size_type
{
    return m_str.rfind(c, pos);
}

[[nodiscard]] inline constexpr auto StringView::Rfind(const char8_t c, const size_type pos) const -> size_type
{
    return m_str.rfind(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto StringView::FindFirstOf(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_of(str, pos);
}

[[nodiscard]] inline auto StringView::FindFirstOf(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                              pos);
}

[[nodiscard]] inline constexpr auto StringView::FindFirstOf(const String &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto StringView::FindFirstOf(const value_type *str, const size_type pos) const
    -> size_type
{
    return m_str.find_first_of(str, pos);
}

[[nodiscard]] inline auto StringView::FindFirstOf(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.find_first_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto StringView::FindFirstOf(const value_type c, const size_type pos) const
    -> size_type
{
    return m_str.find_first_of(c, pos);
}

[[nodiscard]] inline constexpr auto StringView::FindFirstOf(const char8_t c, const size_type pos) const -> size_type
{
    return m_str.find_first_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto StringView::FindFirstNotOf(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_not_of(str, pos);
}

[[nodiscard]] inline auto StringView::FindFirstNotOf(const std::u8string_view &str,
                                                        const size_type pos) const noexcept -> size_type
{
    return m_str.find_first_not_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                                  pos);
}

[[nodiscard]] inline constexpr auto StringView::FindFirstNotOf(const String &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_first_not_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto StringView::FindFirstNotOf(const value_type *str, const size_type pos) const
    -> size_type
{
    return m_str.find_first_not_of(str, pos);
}

[[nodiscard]] inline auto StringView::FindFirstNotOf(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.find_first_not_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto StringView::FindFirstNotOf(const value_type c, const size_type pos) const
    -> size_type
{
    return m_str.find_first_not_of(c, pos);
}

[[nodiscard]] inline constexpr auto StringView::FindFirstNotOf(const char8_t c, const size_type pos) const
    -> size_type
{
    return m_str.find_first_not_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto StringView::FindLastOf(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_of(str, pos);
}

[[nodiscard]] inline auto StringView::FindLastOf(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                             pos);
}

[[nodiscard]] inline constexpr auto StringView::FindLastOf(const String &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto StringView::FindLastOf(const value_type *str, const size_type pos) const
    -> size_type
{
    return m_str.find_last_of(str, pos);
}

[[nodiscard]] inline auto StringView::FindLastOf(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.find_last_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto StringView::FindLastOf(const value_type c, const size_type pos) const -> size_type
{
    return m_str.find_last_of(c, pos);
}

[[nodiscard]] inline constexpr auto StringView::FindLastOf(const char8_t c, const size_type pos) const -> size_type
{
    return m_str.find_last_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto StringView::FindLastNotOf(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_not_of(str, pos);
}

[[nodiscard]] inline auto StringView::FindLastNotOf(const std::u8string_view &str,
                                                       const size_type pos) const noexcept -> size_type
{
    return m_str.find_last_not_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                                 pos);
}

[[nodiscard]] inline constexpr auto StringView::FindLastNotOf(const String &str, const size_type pos) const noexcept
    -> size_type
{
    return m_str.find_last_not_of(str.m_str, pos);
}

[[nodiscard]] inline constexpr auto StringView::FindLastNotOf(const value_type *str, const size_type pos) const
    -> size_type
{
    return m_str.find_last_not_of(str, pos);
}

[[nodiscard]] inline auto StringView::FindLastNotOf(const char8_t *str, const size_type pos) const -> size_type
{
    return m_str.find_last_not_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto StringView::FindLastNotOf(const value_type c, const size_type pos) const
    -> size_type
{
    return m_str.find_last_not_of(c, pos);
}

[[nodiscard]] inline constexpr auto StringView::FindLastNotOf(const char8_t c, const size_type pos) const
    -> size_type
{
    return m_str.find_last_not_of(static_cast<const char>(c), pos);
}

constexpr void StringView::RemovePrefix(const size_type n)
{
    m_str.remove_prefix(n);
}

constexpr void StringView::RemoveSuffix(const size_type n)
{
    m_str.remove_suffix(n);
}

inline auto operator<<(std::ostream &os, const StringView &str) -> std::ostream &
{
    return os << str.AsStdStringView();
}

} // namespace aeon::Common
