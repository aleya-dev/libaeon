// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>
#include <algorithm>
#include <bit>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline constexpr size2d<T>::size2d() noexcept
    : width{}
    , height{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr size2d<T>::size2d(const T width, const T height) noexcept
    : width{width}
    , height{height}
{
}

template <common::concepts::arithmetic_convertible T>
template <common::concepts::arithmetic_convertible U>
inline constexpr size2d<T>::size2d(const size2d<U> size) noexcept
    : width{static_cast<T>(size.width)}
    , height{static_cast<T>(size.height)}
{
}

template <common::concepts::arithmetic_convertible T>
template <common::concepts::arithmetic_convertible U>
inline constexpr size2d<T>::size2d(const U width, const U height) noexcept
    : width{static_cast<T>(width)}
    , height{static_cast<T>(height)}
{
}

template <common::concepts::arithmetic_convertible T>
template <external_size2d U>
inline constexpr size2d<T>::size2d(const U &t) noexcept
    : width{static_cast<T>(t.width)}
    , height{static_cast<T>(t.height)}
{
}

template <common::concepts::arithmetic_convertible T>
template <external_size2d U>
auto constexpr size2d<T>::convert_to() const noexcept -> U
{
    return U{static_cast<decltype(U::width)>(width), static_cast<decltype(U::height)>(height)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto width(const size2d<T> &size) noexcept -> T
{
    return size.width;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto height(const size2d<T> &size) noexcept -> T
{
    return size.height;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto area(const size2d<T> &size) noexcept -> T
{
    return width(size) * height(size);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto empty(const size2d<T> &size) noexcept -> bool
{
    return width(size) == T(0) || height(size) == T(0);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto null(const size2d<T> &size) noexcept -> bool
{
    return width(size) == T(0) && height(size) == T(0);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto valid(const size2d<T> &size) noexcept -> bool
{
    return width(size) >= T(0) && height(size) >= T(0);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rect(const size2d<T> &size) noexcept -> rectangle<T>
{
    return {0, 0, width(size), height(size)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto contains(const vector2<T> &vec, const size2d<T> size) noexcept -> bool
{
    return (vec.x >= T() && vec.x < width(size) && vec.y >= T() && vec.y < height(size));
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void inflate(size2d<T> &size, const T val) noexcept
{
    size = inflated(size, val);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto inflated(const size2d<T> &size, const T val) noexcept -> size2d<T>
{
    return size + val;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size2d<T> &size, const T val) noexcept
{
    size = scaled(size, val);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size2d<T> &size, const T x, const T y) noexcept
{
    size = scaled(size, x, y);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size2d<T> &size, const vector2<T> &vec) noexcept
{
    size = scaled(size, vec);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size2d<T> &size, const size2d<T> &val) noexcept
{
    size = scaled(size, val);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size2d<T> &size, const T val) noexcept -> size2d<T>
{
    return size * val;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto scaled(const size2d<T> &size, const T x, const T y) noexcept -> size2d<T>
{
    return scaled(size, {x, y});
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size2d<T> &size, const vector2<T> &vec) noexcept -> size2d<T>
{
    return size * vec;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size2d<T> &size, const size2d<T> &val) noexcept -> size2d<T>
{
    return size * val;
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr void scale(size2d<T> &size, const U val) noexcept
{
    size = scaled(size, val);
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr void scale(size2d<T> &size, const U x, const U y) noexcept
{
    size = scaled(size, x, y);
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr void scale(size2d<T> &size, const vector2<U> &vec) noexcept
{
    size = scaled(size, vec);
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr void scale(size2d<T> &size, const size2d<U> &val) noexcept
{
    size = scaled(size, val);
}

template <common::concepts::arithmetic_convertible T, typename U>
[[nodiscard]] inline constexpr auto scaled(const size2d<T> &size, const U val) noexcept -> size2d<T>
{
    return size * val;
}

template <common::concepts::arithmetic_convertible T, typename U>
[[nodiscard]] inline constexpr auto scaled(const size2d<T> &size, const U x, const U y) noexcept -> size2d<T>
{
    return scaled(size, {x, y});
}

template <common::concepts::arithmetic_convertible T, typename U>
[[nodiscard]] inline constexpr auto scaled(const size2d<T> &size, const vector2<U> &vec) noexcept -> size2d<T>
{
    return size * vec;
}

template <common::concepts::arithmetic_convertible T, typename U>
[[nodiscard]] inline constexpr auto scaled(const size2d<T> &size, const size2d<U> &val) noexcept -> size2d<T>
{
    return size * val;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto min(const size2d<T> &a, const size2d<T> &b) noexcept -> size2d<T>
{
    return {std::min(width(a), width(b)), std::min(height(a), height(b))};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto max(const size2d<T> &a, const size2d<T> &b) noexcept -> size2d<T>
{
    return {std::max(width(a), width(b)), std::max(height(a), height(b))};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto clamp(const size2d<T> &val, const size2d<T> &min_size,
                                          const size2d<T> &max_size) noexcept -> size2d<T>
{
    return max(min_size, min(max_size, val));
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ratio(const size2d<T> &val) noexcept -> float
{
    return static_cast<float>(width(val)) / static_cast<float>(height(val));
}

template <std::unsigned_integral T>
inline constexpr void bit_ceil(size2d<T> &val) noexcept
{
    val = bit_ceiled(val);
}

template <std::unsigned_integral T>
[[nodiscard]] inline constexpr auto bit_ceiled(const size2d<T> &val) noexcept -> size2d<T>
{
    return {std::bit_ceil(width(val)), std::bit_ceil(height(val))};
}

template <std::unsigned_integral T>
inline constexpr void bit_floor(size2d<T> &val) noexcept
{
    val = bit_floored(val);
}

template <std::unsigned_integral T>
[[nodiscard]] inline constexpr auto bit_floored(const size2d<T> &val) noexcept -> size2d<T>
{
    return {std::bit_floor(width(val)), std::bit_floor(height(val))};
}

template <common::concepts::arithmetic_convertible T, std::floating_point U>
[[nodiscard]] inline constexpr auto interpolate(const size2d<T> &val1, const size2d<T> &val2, const U ratio) noexcept
    -> size2d<T>
{
    const auto inverted = (U(1.0) - ratio);

    return size2d<T>{static_cast<U>(width(val1)) * inverted + static_cast<U>(width(val2)) * ratio,
                     static_cast<U>(height(val1)) * inverted + static_cast<U>(height(val2)) * ratio};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto round(const size2d<T> &val) noexcept -> size2d<T>
{
    return {std::round(width(val)), std::round(height(val))};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto operator==(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool
{
    return width(lhs) == width(rhs) && height(lhs) == height(rhs);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto operator!=(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {width(lhs) + width(rhs), height(lhs) + height(rhs)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {width(lhs) + rhs, height(lhs) + rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {width(lhs) - width(rhs), height(lhs) - height(rhs)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {width(lhs) - rhs, height(lhs) - rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {width(lhs) * width(rhs), height(lhs) * height(rhs)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const size2d<T> &lhs, const vector2<T> &rhs) noexcept -> size2d<T>
{
    return {width(lhs) * rhs.x, height(lhs) * rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(size2d<T> &lhs, const vector2<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {width(lhs) * rhs, height(lhs) * rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {width(lhs) / rhs, height(lhs) / rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs / rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr auto operator*(const size2d<T> &lhs, const size2d<U> &rhs) noexcept -> size2d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) * width(rhs)),
            static_cast<T>(static_cast<U>(height(lhs)) * height(rhs))};
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr auto operator*=(size2d<T> &lhs, const size2d<U> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr auto operator*(const size2d<T> &lhs, const vector2<U> &rhs) noexcept -> size2d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) * rhs.x), static_cast<T>(static_cast<U>(height(lhs)) * rhs.y)};
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr auto operator*=(size2d<T> &lhs, const vector2<U> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr auto operator*(const size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) * rhs), static_cast<T>(static_cast<U>(height(lhs)) * rhs)};
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr auto operator*=(size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr auto operator/(const size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) / rhs), static_cast<T>(static_cast<U>(height(lhs)) / rhs)};
}

template <common::concepts::arithmetic_convertible T, typename U>
inline constexpr auto operator/=(size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>
{
    lhs = lhs / rhs;
    return lhs;
}

} // namespace aeon::math
