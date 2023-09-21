// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <string_view>
#include <ostream>
#include <concepts>

namespace aeon::Common
{

class String;

class StringView
{
    friend class String;

public:
    static_assert(alignof(char) == alignof(char8_t),
                  "Alignment of char and char8_t don't match. StringView won't work properly.");
    static_assert(sizeof(char) == sizeof(char8_t),
                  "Size of char and char8_t don't match. StringView won't work properly.");

    static constexpr auto npos = std::string_view::npos;

    using value_type = std::string_view::value_type;

    using size_type = std::string_view::size_type;
    using difference_type = std::string_view::difference_type;
    using pointer = std::string_view::pointer;
    using const_pointer = std::string_view::const_pointer;
    using reference = std::string_view::reference;
    using const_reference = std::string_view::const_reference;

    using iterator = std::string_view::iterator;
    using const_iterator = std::string_view::const_iterator;

    using reverse_iterator = std::string_view::reverse_iterator;
    using const_reverse_iterator = std::string_view::const_reverse_iterator;

    constexpr StringView() noexcept;

    constexpr StringView(const char *const str);

    StringView(const char8_t *const str);

    constexpr StringView(const char *const str, const size_type size);

    StringView(const char8_t *const str, const size_type size);

    constexpr StringView(const std::string &str) noexcept;

    StringView(const std::u8string &str);

    constexpr StringView(const std::string_view &str) noexcept;

    StringView(const std::u8string_view &str);

    constexpr StringView(const String &str) noexcept;

    template <std::contiguous_iterator IteratorT>
    constexpr StringView(IteratorT begin, IteratorT end) noexcept;

    constexpr StringView(const StringView &other) = default;
    constexpr auto operator=(const StringView &other) -> StringView & = default;

    constexpr StringView(StringView &&other) noexcept = default;
    constexpr auto operator=(StringView &&other) noexcept -> StringView & = default;

    constexpr ~StringView() = default;

    constexpr auto operator=(const value_type *const str) -> StringView &;
    constexpr auto operator=(const std::string &str) -> StringView &;

    auto operator=(const char8_t *const str) -> StringView &;

    auto operator=(const std::u8string &str) -> StringView &;

    constexpr void Assign(const value_type *const str);

    constexpr void Assign(const std::string &str);

    void Assign(const char8_t *const str);

    void Assign(const std::u8string &str);

    constexpr void Assign(const String &str);

    [[nodiscard]] constexpr auto size() const noexcept -> size_type;

    [[nodiscard]] constexpr auto data() const noexcept -> const_pointer;

    [[nodiscard]] constexpr auto Compare(const String &str) const noexcept -> int;

    [[nodiscard]] constexpr auto Compare(const std::string &str) const noexcept -> int;

    [[nodiscard]] auto Compare(const std::u8string &str) const noexcept -> int;

    [[nodiscard]] constexpr auto Compare(const value_type *const str) const noexcept -> int;

    [[nodiscard]] auto Compare(const char8_t *const str) const noexcept -> int;

    [[nodiscard]] constexpr auto Compare(const size_type pos, const size_type count, const StringView str) const -> int;

    constexpr auto operator==(const String &str) const -> bool;

    constexpr auto operator==(const StringView &str) const -> bool;

    constexpr auto operator==(const std::string &str) const -> bool;

    auto operator==(const std::u8string &str) const -> bool;

    constexpr auto operator==(const value_type *const str) const -> bool;

    auto operator==(const char8_t *const str) const -> bool;

#if __cplusplus < 202002L
    constexpr auto operator!=(const String &str) const -> bool;

    constexpr auto operator!=(const StringView &str) const -> bool;

    constexpr auto operator!=(const std::string &str) const -> bool;

    auto operator!=(const std::u8string &str) const -> bool;

    constexpr auto operator!=(const value_type *const str) const -> bool;

    auto operator!=(const char8_t *const str) const -> bool;
#endif

    constexpr auto operator<(const String &str) const -> bool;

    constexpr auto operator<(const StringView &str) const -> bool;

    constexpr auto operator<(const std::string &str) const -> bool;

    auto operator<(const std::u8string &str) const -> bool;

    constexpr auto operator<(const value_type *const str) const -> bool;

    auto operator<(const char8_t *const str) const -> bool;

    constexpr auto operator<=(const String &str) const -> bool;

    constexpr auto operator<=(const StringView &str) const -> bool;

    constexpr auto operator<=(const std::string &str) const -> bool;

    auto operator<=(const std::u8string &str) const -> bool;

    constexpr auto operator<=(const value_type *const str) const -> bool;

    auto operator<=(const char8_t *const str) const -> bool;

    constexpr auto operator>(const String &str) const -> bool;

    constexpr auto operator>(const StringView &str) const -> bool;

    constexpr auto operator>(const std::string &str) const -> bool;

    auto operator>(const std::u8string &str) const -> bool;

    constexpr auto operator>(const value_type *const str) const -> bool;

    auto operator>(const char8_t *const str) const -> bool;

    constexpr auto operator>=(const String &str) const -> bool;

    constexpr auto operator>=(const StringView &str) const -> bool;

    constexpr auto operator>=(const std::string &str) const -> bool;

    auto operator>=(const std::u8string &str) const -> bool;

    constexpr auto operator>=(const value_type *const str) const -> bool;

    auto operator>=(const char8_t *const str) const -> bool;

    [[nodiscard]] constexpr auto AsStdStringView() noexcept -> std::string_view;

    [[nodiscard]] constexpr auto AsStdStringView() const noexcept -> std::string_view;

    [[nodiscard]] auto AsStdU8StringView() noexcept -> std::u8string_view;

    [[nodiscard]] auto AsStdU8StringView() const noexcept -> std::u8string_view;

    [[nodiscard]] constexpr auto Empty() const noexcept -> bool;

    [[nodiscard]] constexpr auto At(const size_type pos) const -> const_reference;

    [[nodiscard]] constexpr auto operator[](const size_type pos) const -> const_reference;

    [[nodiscard]] constexpr auto front() const noexcept -> const_reference;

    [[nodiscard]] constexpr auto back() const noexcept -> const_reference;

    [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto end() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto cend() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto rbegin() noexcept -> reverse_iterator;

    [[nodiscard]] constexpr auto rbegin() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto crbegin() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto rend() noexcept -> reverse_iterator;

    [[nodiscard]] constexpr auto rend() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto crend() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto StartsWith(const std::string_view &str) const noexcept -> bool;

    [[nodiscard]] auto StartsWith(const std::u8string_view &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto StartsWith(const String &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto StartsWith(const value_type c) const noexcept -> bool;

    [[nodiscard]] constexpr auto StartsWith(const char8_t c) const noexcept -> bool;

    [[nodiscard]] constexpr auto EndsWith(const std::string_view &str) const noexcept -> bool;

    [[nodiscard]] auto EndsWith(const std::u8string_view &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto EndsWith(const String &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto EndsWith(const value_type c) const noexcept -> bool;

    [[nodiscard]] constexpr auto EndsWith(const char8_t c) const noexcept -> bool;

    [[nodiscard]] constexpr auto Substr(const size_type pos = 0, const size_type count = npos) const -> StringView;

    [[nodiscard]] auto Find(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto Find(const std::u8string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto Find(const String &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto Find(const StringView &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto Find(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto Find(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto Find(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto Find(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto Rfind(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto Rfind(const std::u8string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto Rfind(const String &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto Rfind(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto Rfind(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto Rfind(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto Rfind(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindFirstOf(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto FindFirstOf(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto FindFirstOf(const String &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto FindFirstOf(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindFirstOf(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindFirstOf(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindFirstOf(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindFirstNotOf(const std::string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] auto FindFirstNotOf(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto FindFirstNotOf(const String &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto FindFirstNotOf(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindFirstNotOf(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindFirstNotOf(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindFirstNotOf(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindLastOf(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto FindLastOf(const std::u8string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto FindLastOf(const String &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto FindLastOf(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindLastOf(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindLastOf(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindLastOf(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindLastNotOf(const std::string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] auto FindLastNotOf(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto FindLastNotOf(const String &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto FindLastNotOf(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindLastNotOf(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindLastNotOf(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindLastNotOf(const char8_t c, const size_type pos = 0) const -> size_type;

    constexpr void RemovePrefix(const size_type n);

    constexpr void RemoveSuffix(const size_type n);

private:
    std::string_view m_str;
};

inline auto operator<<(std::ostream &os, const StringView &str) -> std::ostream &;

} // namespace aeon::Common

#include <aeon/common/impl/string_view_impl.h>
