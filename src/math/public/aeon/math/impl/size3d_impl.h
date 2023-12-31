// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/math/vector3.h>
#include <aeon/math/size2d.h>
#include <algorithm>
#include <bit>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline constexpr size3d<T>::size3d() noexcept
    : width{}
    , height{}
    , depth{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr size3d<T>::size3d(const T width, const T height, const T depth) noexcept
    : width{width}
    , height{height}
    , depth{depth}
{
}

template <common::concepts::arithmetic_convertible T>
template <common::concepts::arithmetic_convertible U>
inline constexpr size3d<T>::size3d(const U width, const U height, const U depth) noexcept
    : width{static_cast<T>(width)}
    , height{static_cast<T>(height)}
    , depth{static_cast<T>(depth)}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr size3d<T>::size3d(const size2d<T> &size, const T depth) noexcept
    : width{math::width(size)}
    , height{math::height(size)}
    , depth{depth}
{
}

template <common::concepts::arithmetic_convertible T>
template <common::concepts::arithmetic_convertible U>
inline constexpr size3d<T>::size3d(const size2d<U> &size, const U depth) noexcept
    : width{static_cast<T>(math::width(size))}
    , height{static_cast<T>(math::height(size))}
    , depth{static_cast<T>(depth)}
{
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto width(const size3d<T> &size) noexcept -> T
{
    return size.width;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto height(const size3d<T> &size) noexcept -> T
{
    return size.height;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto depth(const size3d<T> &size) noexcept -> T
{
    return size.depth;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto volume(const size3d<T> &size) noexcept -> T
{
    return width(size) * height(size) * depth(size);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto empty(const size3d<T> &size) noexcept -> bool
{
    return width(size) == T(0) || height(size) == T(0) || depth(size) == T(0);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto null(const size3d<T> &size) noexcept -> bool
{
    return width(size) == T(0) && height(size) == T(0) && depth(size) == T(0);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto valid(const size3d<T> &size) noexcept -> bool
{
    return width(size) >= T(0) && height(size) >= T(0) && depth(size) >= T(0);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto contains(const vector3<T> &vec, const size3d<T> size) noexcept -> bool
{
    return (vec.x < width(size) && vec.y < height(size) && vec.z < depth(size));
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void inflate(size3d<T> &size, const T val) noexcept
{
    size = inflated(size, val);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto inflated(const size3d<T> &size, const T val) noexcept -> size3d<T>
{
    return size + val;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size3d<T> &size, const T val) noexcept
{
    size = scaled(size, val);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size3d<T> &size, const T x, const T y, const T z) noexcept
{
    size = scaled(size, x, y, z);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size3d<T> &size, const vector3<T> &vec) noexcept
{
    size = scaled(size, vec);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size3d<T> &size, const size3d<T> &val) noexcept
{
    size = scaled(size, val);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const T val) noexcept -> size3d<T>
{
    return size * val;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const T x, const T y, const T z) noexcept -> size3d<T>
{
    return scaled(size, {x, y, z});
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const vector3<T> &vec) noexcept -> size3d<T>
{
    return size * vec;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const size3d<T> &val) noexcept -> size3d<T>
{
    return size * val;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(size3d<T> &size, const U val) noexcept
{
    size = scaled(size, val);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(size3d<T> &size, const U x, const U y, const U z) noexcept
{
    size = scaled(size, x, y, z);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(size3d<T> &size, const vector3<U> &vec) noexcept
{
    size = scaled(size, vec);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(size3d<T> &size, const size3d<U> &val) noexcept
{
    size = scaled(size, val);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const U val) noexcept -> size3d<T>
{
    return size * val;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const U x, const U y, const U z) noexcept -> size3d<T>
{
    return scaled(size, {x, y, z});
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const vector3<U> &vec) noexcept -> size3d<T>
{
    return size * vec;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const size3d<U> &val) noexcept -> size3d<T>
{
    return size * val;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto min(const size3d<T> &a, const size3d<T> &b) noexcept -> size3d<T>
{
    return {std::min(width(a), width(b)), std::min(height(a), height(b)), std::min(depth(a), depth(b))};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto max(const size3d<T> &a, const size3d<T> &b) noexcept -> size3d<T>
{
    return {std::max(width(a), width(b)), std::max(height(a), height(b)), std::max(depth(a), depth(b))};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto clamp(const size3d<T> &val, const size3d<T> &min_size,
                                          const size3d<T> &max_size) noexcept -> size3d<T>
{
    return max(min_size, min(max_size, val));
}

template <std::unsigned_integral T>
inline constexpr void bit_ceil(size3d<T> &val) noexcept
{
    val = bit_ceiled(val);
}

template <std::unsigned_integral T>
[[nodiscard]] inline constexpr auto bit_ceiled(const size3d<T> &val) noexcept -> size3d<T>
{
    return {std::bit_ceil(width(val)), std::bit_ceil(height(val)), std::bit_ceil(depth(val))};
}

template <std::unsigned_integral T>
inline constexpr void bit_floor(size3d<T> &val) noexcept
{
    val = bit_floored(val);
}

template <std::unsigned_integral T>
[[nodiscard]] inline constexpr auto bit_floored(const size3d<T> &val) noexcept -> size3d<T>
{
    return {std::bit_floor(width(val)), std::bit_floor(height(val)), std::bit_floor(depth(val))};
}

template <common::concepts::arithmetic_convertible T, std::floating_point U>
[[nodiscard]] inline constexpr auto interpolate(const size3d<T> &val1, const size3d<T> &val2, const U ratio) noexcept
    -> size3d<T>
{
    const auto inverted = (U(1.0) - ratio);

    return size3d<T>{static_cast<U>(width(val1)) * inverted + static_cast<U>(width(val2)) * ratio,
                     static_cast<U>(height(val1)) * inverted + static_cast<U>(height(val2)) * ratio,
                     static_cast<U>(depth(val1)) * inverted + static_cast<U>(depth(val2)) * ratio};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto round(const size3d<T> &val) noexcept -> size3d<T>
{
    return {std::round(width(val)), std::round(height(val)), std::round(depth(val))};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto operator==(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> bool
{
    return width(lhs) == width(rhs) && height(lhs) == height(rhs) && depth(lhs) == depth(rhs);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto operator!=(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    return {width(lhs) + width(rhs), height(lhs) + height(rhs), depth(lhs) + depth(rhs)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    return {width(lhs) + rhs, height(lhs) + rhs, depth(lhs) + rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    return {width(lhs) - width(rhs), height(lhs) - height(rhs), depth(lhs) - depth(rhs)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    return {width(lhs) - rhs, height(lhs) - rhs, depth(lhs) - rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    return {width(lhs) * width(rhs), height(lhs) * height(rhs), depth(lhs) * depth(rhs)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const size3d<T> &lhs, const vector3<T> &rhs) noexcept -> size3d<T>
{
    return {width(lhs) * rhs.x, height(lhs) * rhs.y, depth(lhs) * rhs.z};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(size3d<T> &lhs, const vector3<T> &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    return {width(lhs) * rhs, height(lhs) * rhs, depth(lhs) * rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    return {width(lhs) / rhs, height(lhs) / rhs, depth(lhs) / rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    lhs = lhs / rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const size3d<T> &lhs, const size3d<U> &rhs) noexcept -> size3d<T>
{
    return {
        static_cast<T>(static_cast<U>(width(lhs)) * width(rhs)),
        static_cast<T>(static_cast<U>(height(lhs)) * height(rhs)),
        static_cast<T>(static_cast<U>(depth(lhs)) * depth(rhs)),
    };
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(size3d<T> &lhs, const size3d<U> &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const size3d<T> &lhs, const vector3<U> &rhs) noexcept -> size3d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) * rhs.x), static_cast<T>(static_cast<U>(height(lhs)) * rhs.y),
            static_cast<T>(static_cast<U>(depth(lhs)) * rhs.z)};
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(size3d<T> &lhs, const vector3<U> &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const size3d<T> &lhs, const U &rhs) noexcept -> size3d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) * rhs), static_cast<T>(static_cast<U>(height(lhs)) * rhs),
            static_cast<T>(static_cast<U>(depth(lhs)) * rhs)};
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(size3d<T> &lhs, const U &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/(const size3d<T> &lhs, const U &rhs) noexcept -> size3d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) / rhs), static_cast<T>(static_cast<U>(height(lhs)) / rhs),
            static_cast<T>(static_cast<U>(depth(lhs)) / rhs)};
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/=(size3d<T> &lhs, const U &rhs) noexcept -> size3d<T>
{
    lhs = lhs / rhs;
    return lhs;
}

} // namespace aeon::math
