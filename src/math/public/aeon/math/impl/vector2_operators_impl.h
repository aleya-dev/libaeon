// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <tuple>

namespace aeon::math
{

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator+(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator+(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x + rhs, lhs.y + rhs};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator+(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs + rhs.x, lhs + rhs.y};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x - rhs, lhs.y - rhs};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs - rhs.x, lhs - rhs.y};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {-vec.x, -vec.y};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator*(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x * rhs.x, lhs.y * rhs.y};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator*(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x * rhs, lhs.y * rhs};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator*(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs * rhs.x, lhs * rhs.y};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator/(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x / rhs.x, lhs.y / rhs.y};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator/(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x / rhs, lhs.y / rhs};
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator*(const vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs.x), static_cast<T>(static_cast<U>(lhs.y) * rhs.y)};
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator*(const vector2<T> &lhs, const U rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs), static_cast<T>(static_cast<U>(lhs.y) * rhs)};
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator*(const T lhs, const vector2<U> &rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(lhs * static_cast<T>(rhs.x)), static_cast<T>(lhs * static_cast<T>(rhs.y))};
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator/(const vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs.x), static_cast<T>(static_cast<U>(lhs.y) / rhs.y)};
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator/(const vector2<T> &lhs, const U rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs), static_cast<T>(static_cast<U>(lhs.y) / rhs)};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator+=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator+=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator*=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator*=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator/=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator/=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator*=(vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator*=(vector2<T> &lhs, const U rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator/=(vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator/=(vector2<T> &lhs, const U rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator==(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator<=>(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> std::strong_ordering
{
    return std::tie(lhs.x, lhs.y) <=> std::tie(rhs.x, rhs.y);
}

} // namespace aeon::math
