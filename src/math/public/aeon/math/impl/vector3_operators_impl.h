// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <tuple>

namespace aeon::math
{

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator+(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator+(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator+(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs + rhs.x, lhs + rhs.y, lhs + rhs.z};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs - rhs.x, lhs - rhs.y, lhs - rhs.z};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {-vec.x, -vec.y, -vec.z};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator*(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator*(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator*(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator/(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator/(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator*(const vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs.x), static_cast<T>(static_cast<U>(lhs.y) * rhs.y),
            static_cast<T>(static_cast<U>(lhs.z) * rhs.z)};
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator*(const vector3<T> &lhs, const U rhs) noexcept -> vector3<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs), static_cast<T>(static_cast<U>(lhs.y) * rhs),
            static_cast<T>(static_cast<U>(lhs.z) * rhs)};
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator/(const vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs.x), static_cast<T>(static_cast<U>(lhs.y) / rhs.y),
            static_cast<T>(static_cast<U>(lhs.z) / rhs.z)};
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator/(const vector3<T> &lhs, const U rhs) noexcept -> vector3<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs), static_cast<T>(static_cast<U>(lhs.y) / rhs),
            static_cast<T>(static_cast<U>(lhs.z) / rhs)};
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator+=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator+=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator-=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator*=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator*=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator/=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator/=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator*=(vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator*=(vector3<T> &lhs, const U rhs) noexcept -> vector3<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator/=(vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T, Common::Concepts::ArithmeticConvertible U>
inline constexpr auto operator/=(vector3<T> &lhs, const U rhs) noexcept -> vector3<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator==(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <Common::Concepts::ArithmeticConvertible T>
inline constexpr auto operator<=>(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> std::strong_ordering
{
    return std::tie(lhs.x, lhs.y, lhs.z) <=> std::tie(rhs.x, rhs.y, rhs.z);
}

} // namespace aeon::math
