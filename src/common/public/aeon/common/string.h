// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <concepts>
#include <string>
#include <ostream>

namespace aeon::Common
{

class StringView;

class String
{
    friend class StringView;

public:
    static_assert(alignof(char) == alignof(char8_t),
                  "Alignment of char and char8_t don't match. String won't work properly.");
    static_assert(sizeof(char) == sizeof(char8_t), "Size of char and char8_t don't match. String won't work properly.");

    static constexpr auto npos = std::string::npos;

    using value_type = std::string::value_type;
    using allocator_type = std::string::allocator_type;

    using size_type = std::string::size_type;
    using difference_type = std::string::difference_type;
    using pointer = std::string::pointer;
    using const_pointer = std::string::const_pointer;
    using reference = std::string::reference;
    using const_reference = std::string::const_reference;

    using iterator = std::string::iterator;
    using const_iterator = std::string::const_iterator;

    using reverse_iterator = std::string::reverse_iterator;
    using const_reverse_iterator = std::string::const_reverse_iterator;

    constexpr String() noexcept;

    constexpr String(const value_type c) noexcept;

    constexpr String(const char8_t c) noexcept;

    constexpr String(const size_type count, const value_type c) noexcept;

    constexpr String(const size_type count, const char8_t c) noexcept;

    constexpr String(const char *const str);

    String(const char8_t *const str);

    constexpr String(std::string str) noexcept;

    constexpr String(const std::u8string &str);

    constexpr explicit String(const StringView &str) noexcept;

    template <std::contiguous_iterator IteratorT>
    constexpr String(IteratorT begin, IteratorT end) noexcept;

    constexpr String(const String &other) = default;
    constexpr auto operator=(const String &other) -> String & = default;

    constexpr String(String &&other) noexcept = default;
    constexpr auto operator=(String &&other) noexcept -> String & = default;

    constexpr ~String() = default;

    constexpr auto operator=(const value_type *const str) -> String &;

    constexpr auto operator=(std::string str) -> String &;

    auto operator=(const char8_t *const str) -> String &;

    constexpr auto operator=(const std::u8string &str) -> String &;

    constexpr auto operator=(const StringView &str) -> String &;

    constexpr void Assign(const value_type *const str);

    constexpr void Assign(std::string &&str);

    void Assign(const char8_t *const str);

    constexpr void Assign(const std::u8string &str);

    constexpr void Assign(const String &str);

    constexpr void Assign(const StringView &str);

    constexpr auto Insert(const size_type index, const value_type *const str) -> String &;

    auto Insert(const size_type index, const char8_t *const str) -> String &;

    constexpr auto Insert(const size_type index, const std::string_view &str) -> String &;

    auto Insert(const size_type index, const std::u8string_view &str) -> String &;

    auto Insert(const size_type index, const String &str) -> String &;

    auto Insert(const size_type index, const StringView &str) -> String &;

    template <typename PositionIteratorT, typename InputIteratorT>
    auto Insert(const PositionIteratorT pos, const InputIteratorT first, const InputIteratorT last) -> String &;

    constexpr auto Erase(const size_type index = 0, const size_type count = npos) -> String &;

    constexpr auto Erase(const_iterator position) -> iterator;

    constexpr auto Erase(const_iterator first, const_iterator last) -> iterator;

    [[nodiscard]] constexpr auto Str() noexcept -> std::string &;

    [[nodiscard]] constexpr auto Str() const noexcept -> const std::string &;

    [[nodiscard]] auto U8Str() const noexcept -> std::u8string;

    [[nodiscard]] constexpr auto Size() const noexcept -> size_type;

    [[nodiscard]] constexpr auto Capacity() const noexcept -> size_type;

    [[nodiscard]] constexpr auto Data() noexcept -> pointer;

    [[nodiscard]] constexpr auto Data() const noexcept -> const_pointer;

    constexpr void ShrinkToFit();

    [[nodiscard]] constexpr auto CStr() const noexcept -> const_pointer;

    [[nodiscard]] auto U8CStr() const noexcept -> const char8_t *;

    constexpr void Reserve(const size_type size);

    constexpr void Resize(const size_type count);

    [[nodiscard]] constexpr auto Compare(const String &str) const noexcept -> int;

    [[nodiscard]] constexpr auto Compare(const StringView &str) const noexcept -> int;

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

    constexpr auto Append(const value_type *const str) -> String &;

    auto Append(const char8_t *const str) -> String &;

    constexpr auto Append(const value_type *const str, const size_type size) -> String &;

    auto Append(const char8_t *const str, const size_type size) -> String &;

    constexpr auto Append(const std::string &str) -> String &;

    auto Append(const std::u8string &str) -> String &;

    constexpr auto Append(const String &str) -> String &;

    constexpr auto Append(const StringView &str) -> String &;

    template <std::contiguous_iterator IteratorT>
    constexpr auto Append(IteratorT begin, IteratorT end) noexcept -> String &;

    constexpr auto operator+=(const char *str) -> String &;

    auto operator+=(const char8_t *str) -> String &;

    constexpr auto operator+=(const std::string &str) -> String &;

    constexpr auto operator+=(const std::string_view &str) -> String &;

    auto operator+=(const std::u8string_view &str) -> String &;

    constexpr auto operator+=(const String &str) -> String &;

    constexpr auto operator+=(const StringView &str) -> String &;

    constexpr auto operator+=(const value_type c) -> String &;

    constexpr auto operator+=(const char8_t c) -> String &;

    [[nodiscard]] constexpr auto AsStdStringView() noexcept -> std::string_view;

    [[nodiscard]] constexpr auto AsStdStringView() const noexcept -> std::string_view;

    [[nodiscard]] auto AsStdU8StringView() noexcept -> std::u8string_view;

    [[nodiscard]] auto AsStdU8StringView() const noexcept -> std::u8string_view;

    constexpr void Clear();

    [[nodiscard]] constexpr auto Empty() const noexcept -> bool;

    [[nodiscard]] constexpr auto At(const size_type pos) -> reference;

    [[nodiscard]] constexpr auto At(const size_type pos) const -> const_reference;

    [[nodiscard]] constexpr auto operator[](const size_type pos) -> reference;

    [[nodiscard]] constexpr auto operator[](const size_type pos) const -> const_reference;

    [[nodiscard]] constexpr auto Front() noexcept -> reference;

    [[nodiscard]] constexpr auto Front() const noexcept -> const_reference;

    [[nodiscard]] constexpr auto Back() noexcept -> reference;

    [[nodiscard]] constexpr auto Back() const noexcept -> const_reference;

    [[nodiscard]] constexpr auto begin() noexcept -> iterator;

    [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto end() noexcept -> iterator;

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

    [[nodiscard]] constexpr auto StartsWith(const StringView &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto StartsWith(const value_type c) const noexcept -> bool;

    [[nodiscard]] constexpr auto StartsWith(const char8_t c) const noexcept -> bool;

    [[nodiscard]] constexpr auto EndsWith(const std::string_view &str) const noexcept -> bool;

    [[nodiscard]] auto EndsWith(const std::u8string_view &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto EndsWith(const String &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto EndsWith(const StringView &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto EndsWith(const value_type c) const noexcept -> bool;

    [[nodiscard]] constexpr auto EndsWith(const char8_t c) const noexcept -> bool;

    [[nodiscard]] constexpr auto Substr(const size_type pos = 0, const size_type count = npos) const -> String;

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

    [[nodiscard]] constexpr auto Rfind(const StringView &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto Rfind(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto Rfind(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto Rfind(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto Rfind(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindFirstOf(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto FindFirstOf(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto FindFirstOf(const String &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto FindFirstOf(const StringView &str, const size_type pos = 0) const noexcept
        -> size_type;

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

    [[nodiscard]] constexpr auto FindFirstNotOf(const StringView &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto FindFirstNotOf(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindFirstNotOf(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindFirstNotOf(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindFirstNotOf(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindLastOf(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto FindLastOf(const std::u8string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto FindLastOf(const String &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto FindLastOf(const StringView &str, const size_type pos = 0) const noexcept
        -> size_type;

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

    [[nodiscard]] constexpr auto FindLastNotOf(const StringView &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto FindLastNotOf(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto FindLastNotOf(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindLastNotOf(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto FindLastNotOf(const char8_t c, const size_type pos = 0) const -> size_type;

    void Replace(const size_type pos, const size_type count, const StringView &str);

private:
    std::string m_str;
};

inline constexpr auto operator+(const String &lhs, const String &rhs) -> String;

inline constexpr auto operator+(const String &lhs, const std::string &rhs) -> String;

inline constexpr auto operator+(const std::string &lhs, const String &rhs) -> String;

inline auto operator+(const String &lhs, const std::u8string &rhs) -> String;

inline auto operator+(const std::u8string &lhs, const String &rhs) -> String;

inline constexpr auto operator+(const String &lhs, const char *const rhs) -> String;

inline constexpr auto operator+(const char *const lhs, const String &rhs) -> String;

inline auto operator+(const String &lhs, const char8_t *const rhs) -> String;

inline auto operator+(const char8_t *const lhs, const String &rhs) -> String;

inline constexpr auto operator+(const StringView &lhs, const String &rhs) -> String;

inline constexpr auto operator+(const StringView &lhs, const StringView &rhs) -> String;

inline constexpr auto operator+(const StringView &lhs, const std::string &rhs) -> String;

inline constexpr auto operator+(const std::string &lhs, const StringView &rhs) -> String;

inline auto operator+(const StringView &lhs, const std::u8string &rhs) -> String;

inline auto operator+(const std::u8string &lhs, const StringView &rhs) -> String;

inline constexpr auto operator+(const StringView &lhs, const char *const rhs) -> String;

inline constexpr auto operator+(const char *const lhs, const StringView &rhs) -> String;

inline auto operator+(const StringView &lhs, const char8_t *const rhs) -> String;

inline auto operator+(const char8_t *const lhs, const StringView &rhs) -> String;

inline auto operator<<(std::ostream &os, const String &str) -> std::ostream &;

} // namespace aeon::Common

#include <aeon/common/impl/string_impl.h>
