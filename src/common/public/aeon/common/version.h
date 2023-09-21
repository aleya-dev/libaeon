// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <ostream>

namespace aeon::Common
{

template <typename T = int>
class Version2
{
public:
    constexpr Version2() noexcept;

    constexpr explicit Version2(const T major, const T minor) noexcept;

    template <typename U>
    constexpr explicit Version2(const Version2<U> other) noexcept;

    template <typename U>
    constexpr explicit Version2(const U major, const U minor) noexcept;

    ~Version2() = default;

    constexpr Version2(const Version2<T> &) noexcept = default;
    constexpr auto operator=(const Version2<T> &) noexcept -> Version2<T> & = default;

    constexpr Version2(Version2<T> &&) noexcept = default;
    constexpr auto operator=(Version2<T> &&) noexcept -> Version2<T> & = default;

    [[nodiscard]] auto Str() const -> String;

    T Major;
    T Minor;
};

template <typename T = int>
class Version3 : public Version2<T>
{
public:
    constexpr Version3() noexcept;

    constexpr explicit Version3(const T major, const T minor) noexcept;

    constexpr explicit Version3(const T major, const T minor, const T patch) noexcept;

    constexpr explicit Version3(const Version2<T> &ver) noexcept;

    constexpr explicit Version3(const Version2<T> &ver, const T patch) noexcept;

    template <typename U>
    constexpr explicit Version3(const U major, const U minor) noexcept;

    template <typename U>
    constexpr explicit Version3(const U major, const U minor, const U patch) noexcept;

    template <typename U>
    constexpr explicit Version3(const Version2<U> &ver) noexcept;

    template <typename U>
    constexpr explicit Version3(const Version2<U> &ver, const U patch) noexcept;

    template <typename U>
    constexpr explicit Version3(const Version3<U> &ver) noexcept;

    ~Version3() = default;

    constexpr Version3(const Version3<T> &) noexcept = default;
    constexpr auto operator=(const Version3<T> &) noexcept -> Version3<T> & = default;

    constexpr Version3(Version3<T> &&) noexcept = default;
    constexpr auto operator=(Version3<T> &&) noexcept -> Version3<T> & = default;

    [[nodiscard]] auto Str() const -> String;

    T Patch;
};

template <typename T = int>
class Version4 : public Version3<T>
{
public:
    constexpr Version4() noexcept;

    constexpr explicit Version4(const T major, const T minor) noexcept;

    constexpr explicit Version4(const T major, const T minor, const T patch) noexcept;

    constexpr explicit Version4(const T major, const T minor, const T patch, const T build) noexcept;

    constexpr explicit Version4(const Version2<T> &ver) noexcept;

    constexpr explicit Version4(const Version2<T> &ver, const T patch) noexcept;

    constexpr explicit Version4(const Version2<T> &ver, const T patch, const T build) noexcept;

    constexpr explicit Version4(const Version3<T> &ver) noexcept;

    constexpr explicit Version4(const Version3<T> &ver, const T build) noexcept;

    template <typename U>
    constexpr explicit Version4(const U major, const U minor) noexcept;

    template <typename U>
    constexpr explicit Version4(const U major, const U minor, const U patch) noexcept;

    template <typename U>
    constexpr explicit Version4(const U major, const U minor, const U patch, const U build) noexcept;

    template <typename U>
    constexpr explicit Version4(const Version2<U> &ver) noexcept;

    template <typename U>
    constexpr explicit Version4(const Version2<U> &ver, const U patch) noexcept;

    template <typename U>
    constexpr explicit Version4(const Version2<U> &ver, const U patch, const U build) noexcept;

    template <typename U>
    constexpr explicit Version4(const Version3<U> &ver) noexcept;

    template <typename U>
    constexpr explicit Version4(const Version3<U> &ver, const U build) noexcept;

    template <typename U>
    constexpr explicit Version4(const Version4<U> &ver) noexcept;

    ~Version4() = default;

    constexpr Version4(const Version4<T> &) noexcept = default;
    constexpr auto operator=(const Version4<T> &) noexcept -> Version4<T> & = default;

    constexpr Version4(Version4<T> &&) noexcept = default;
    constexpr auto operator=(Version4<T> &&) noexcept -> Version4<T> & = default;

    [[nodiscard]] auto Str() const -> String;

    T Build;
};

template <typename T>
inline constexpr auto operator<(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<=(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>=(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator==(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const Version2<T> &v) -> std::ostream &;

template <typename T>
inline constexpr auto operator<(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<=(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>=(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator==(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const Version3<T> &v) -> std::ostream &;

template <typename T>
inline constexpr auto operator<(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<=(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>=(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator==(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const Version4<T> &v) -> std::ostream &;

using Version = Version4<int>;

} // namespace aeon::Common

#include <aeon/common/impl/version_impl.h>
