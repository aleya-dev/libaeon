// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <aeon/common/assert.h>
#include <vector>
#include <limits>
#include <algorithm>
#include <ostream>

namespace aeon::Common
{

template <typename T>
class StringTable
{
    static constexpr auto npos = std::numeric_limits<std::size_t>::max();

public:
    explicit StringTable() noexcept;
    explicit StringTable(String str) noexcept;
    ~StringTable();

    StringTable(const StringTable &) noexcept = default;
    auto operator=(const StringTable &) noexcept -> StringTable & = default;

    StringTable(StringTable &&) noexcept = default;
    auto operator=(StringTable &&) noexcept -> StringTable & = default;

    auto operator=(String str) noexcept -> StringTable &;

    [[nodiscard]] auto str() const noexcept -> const String &;

    [[nodiscard]] static auto size() noexcept;
    [[nodiscard]] static auto str(const std::size_t i) -> const String &;

    template <typename U>
    friend auto operator==(const StringTable<U> &lhs, const StringTable<U> &rhs) noexcept -> bool;

    template <typename U>
    friend auto operator!=(const StringTable<U> &lhs, const StringTable<U> &rhs) noexcept -> bool;

private:
    [[nodiscard]] static auto table() noexcept -> std::vector<String> &;

    void init(String str);

    std::size_t index_;
};

template <typename T>
inline StringTable<T>::StringTable() noexcept
    : index_{npos}
{
}

template <typename T>
inline StringTable<T>::StringTable(String str) noexcept
    : index_{}
{
    init(std::move(str));
}

template <typename T>
inline StringTable<T>::~StringTable() = default;

template <typename T>
inline auto StringTable<T>::operator=(String str) noexcept -> StringTable &
{
    init(std::move(str));
    return *this;
}

template <typename T>
[[nodiscard]] inline auto StringTable<T>::str() const noexcept -> const String &
{
    if (index_ == npos)
    {
        static const String str;
        return str;
    }

    AeonAssertIndexBounds(index_, std::size(table()));
    return table()[index_];
}

template <typename T>
[[nodiscard]] inline auto StringTable<T>::size() noexcept
{
    return std::size(table());
}

template <typename T>
[[nodiscard]] inline auto StringTable<T>::str(const std::size_t i) -> const String &
{
    AeonAssertIndexBounds(i, std::size(table()));
    return table().at(i);
}

template <typename T>
[[nodiscard]] inline auto StringTable<T>::table() noexcept -> std::vector<String> &
{
    static std::vector<String> table;
    return table;
}

template <typename T>
inline void StringTable<T>::init(String str)
{
    if (str.Empty())
    {
        index_ = npos;
        return;
    }

    const auto result =
        std::find_if(std::begin(table()), std::end(table()), [&str](const auto &s) { return s == str; });

    if (result != std::end(table()))
    {
        index_ = std::distance(std::begin(table()), result);
        return;
    }

    table().emplace_back(std::move(str));
    index_ = std::size(table()) - 1;
}

template <typename U>
inline auto operator==(const StringTable<U> &lhs, const StringTable<U> &rhs) noexcept -> bool
{
    return lhs.index_ == rhs.index_;
}

template <typename U>
inline auto operator!=(const StringTable<U> &lhs, const StringTable<U> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator==(const StringTable<T> &lhs, const String &rhs) noexcept -> bool
{
    return lhs.str() == rhs;
}

template <typename T>
inline auto operator!=(const StringTable<T> &lhs, const String &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator==(const String &lhs, const StringTable<T> &rhs) noexcept -> bool
{
    return lhs == rhs.str();
}

template <typename T>
inline auto operator!=(const String &lhs, const StringTable<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator<(const StringTable<T> &lhs, const StringTable<T> &rhs) noexcept -> bool
{
    return lhs.str() < rhs.str();
}

template <typename T>
inline auto operator<=(const StringTable<T> &lhs, const StringTable<T> &rhs) noexcept -> bool
{
    return lhs.str() <= rhs.str();
}

template <typename T>
inline auto operator>(const StringTable<T> &lhs, const StringTable<T> &rhs) noexcept -> bool
{
    return lhs.str() > rhs.str();
}

template <typename T>
inline auto operator>=(const StringTable<T> &lhs, const StringTable<T> &rhs) noexcept -> bool
{
    return lhs.str() >= rhs.str();
}

template <typename T>
inline auto operator<<(std::ostream &os, const StringTable<T> &str) -> std::ostream &
{
    return os << str.str();
}

} // namespace aeon::Common
