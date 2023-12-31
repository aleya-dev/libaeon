// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/common/assert.h>
#include <cmath>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline constexpr vector3<T>::vector3() noexcept
    : x{}
    , y{}
    , z{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr vector3<T>::vector3(const T xyz) noexcept
    : x{xyz}
    , y{xyz}
    , z{xyz}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr vector3<T>::vector3(const T x, const T y) noexcept
    : x{x}
    , y{y}
    , z{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr vector3<T>::vector3(const T x, const T y, const T z) noexcept
    : x{x}
    , y{y}
    , z{z}
{
}

template <common::concepts::arithmetic_convertible T>
template <common::concepts::arithmetic_convertible U>
inline constexpr vector3<T>::vector3(const U x, const U y) noexcept
    : x{static_cast<T>(x)}
    , y{static_cast<T>(y)}
    , z{}
{
}

template <common::concepts::arithmetic_convertible T>
template <common::concepts::arithmetic_convertible U>
inline constexpr vector3<T>::vector3(const U x, const U y, const U z) noexcept
    : x{static_cast<T>(x)}
    , y{static_cast<T>(y)}
    , z{static_cast<T>(z)}
{
}

template <common::concepts::arithmetic_convertible T>
template <common::concepts::arithmetic_convertible U>
inline constexpr vector3<T>::vector3(const vector3<U> &vec) noexcept
    : x{static_cast<T>(vec.x)}
    , y{static_cast<T>(vec.y)}
    , z{static_cast<T>(vec.z)}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr vector3<T>::vector3(const vector2<T> vec) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr vector3<T>::vector3(const vector2<T> vec, const T z) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{z}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr vector3<T>::vector3(const T xyz[3]) noexcept
    : x{xyz[0]}
    , y{xyz[1]}
    , z{xyz[2]}
{
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto vector3<T>::operator=(const vector2<T> &vec) noexcept -> vector3<T> &
{
    x = vec.x;
    y = vec.y;
    z = T{};
    return *this;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto vector3<T>::operator[](const std::size_t i) noexcept -> T &
{
    std::array<T *, 3> value{&x, &y, &z};
    aeon_assert_size_bounds(value, i);
    return *value[i];
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto vector3<T>::operator[](const std::size_t i) const noexcept -> const T &
{
    std::array<const T *, 3> value{&x, &y, &z};
    aeon_assert_size_bounds(value, i);
    return *value[i];
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto vector3<T>::zero() noexcept -> vector3<T>
{
    return vector3<T>{};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void vector3<T>::set(const T new_x, const T new_y, const T new_z) noexcept
{
    x = new_x;
    y = new_y;
    z = new_z;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void translate(vector3<T> &lhs, const T x, const T y, const T z) noexcept
{
    lhs += vector3{x, y, z};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void translate(vector3<T> &lhs, const vector3<T> &rhs) noexcept
{
    lhs += rhs;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto translated(const vector3<T> &lhs, const T x, const T y, const T z) noexcept
    -> vector3<T>
{
    return lhs + vector3{x, y, z};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto translated(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return lhs + rhs;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto sum(const vector3<T> &vec) noexcept -> T
{
    return vec.x + vec.y + vec.z;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto dot(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto cross(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {(lhs.y * rhs.z) - (lhs.z * rhs.y), (lhs.z * rhs.x) - (lhs.x * rhs.z), (lhs.x * rhs.y) - (lhs.y * rhs.x)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto length(const vector3<T> &vec) noexcept -> T
{
    if constexpr (!std::is_integral_v<T>)
        return std::sqrt(dot(vec, vec));
    else
        return static_cast<T>(std::sqrt(static_cast<double>(dot(vec, vec))));
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto squared_length(const vector3<T> &vec) noexcept -> T
{
    return dot(vec, vec);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void normalize(vector3<T> &vec) noexcept
{
    vec = normalized(vec);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto normalized(const vector3<T> &vec) noexcept -> vector3<T>
{
    const auto l = length(vec);

    if (l > constants<T>::tolerance)
        return vec / l;

    return vector3<T>::zero();
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto min(const vector3<T> &vec) noexcept -> T
{
    return std::min({vec.x, vec.y, vec.z});
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto max(const vector3<T> &vec) noexcept -> T
{
    return std::max({vec.x, vec.y, vec.z});
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto sin(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::sin(vec.x), std::sin(vec.y), std::sin(vec.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto cos(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::cos(vec.x), std::cos(vec.y), std::cos(vec.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto tan(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::tan(vec.x), std::tan(vec.y), std::tan(vec.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto asin(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::asin(vec.x), std::asin(vec.y), std::asin(vec.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto acos(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::acos(vec.x), std::acos(vec.y), std::acos(vec.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto atan(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::atan(vec.x), std::atan(vec.y), std::atan(vec.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto abs(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::abs(vec.x), std::abs(vec.y), std::abs(vec.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T
{
    return length(lhs - rhs);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto squared_distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T
{
    return squared_length(lhs - rhs);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto absolute_distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept
    -> vector3<T>
{
    return {std::abs(lhs.x - rhs.x), std::abs(lhs.y - rhs.y), std::abs(lhs.z - rhs.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto manhattan_distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T
{
    return sum(absolute_distance(lhs, rhs));
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto chebyshev_distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T
{
    return max(absolute_distance(lhs, rhs));
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto midpoint(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return (lhs + rhs) * T(0.5);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto floor(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    auto x = lhs.x;
    auto y = lhs.y;
    auto z = lhs.z;

    if (rhs.x < x)
        x = rhs.x;
    if (rhs.y < y)
        y = rhs.y;
    if (rhs.z < z)
        z = rhs.z;

    return {x, y, z};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto floor(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::floor(vec.x), std::floor(vec.y), std::floor(vec.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ceil(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    auto x = lhs.x;
    auto y = lhs.y;
    auto z = lhs.z;

    if (rhs.x > x)
        x = rhs.x;
    if (rhs.y > y)
        y = rhs.y;
    if (rhs.z > z)
        z = rhs.z;

    return {x, y, z};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ceil(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::ceil(vec.x), std::ceil(vec.y), std::ceil(vec.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto round(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::round(vec.x), std::round(vec.y), std::round(vec.z)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rotate_xy_by(const vector3<T> &vec, const unitf<radian> angle,
                                                 const vector3<T> &center) noexcept -> vector3<T>
{
    const auto result = rotate_by({vec.x, vec.y}, angle, {center.x, center.y});
    return {result.x, result.y, vec.z};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rotate_xz_by(const vector3<T> &vec, const unitf<radian> angle,
                                                 const vector3<T> &center) noexcept -> vector3<T>
{
    const auto result = rotate_by({vec.x, vec.z}, angle, {center.x, center.z});
    return {result.x, vec.y, result.y};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rotate_yz_by(const vector3<T> &vec, const unitf<radian> angle,
                                                 const vector3<T> &center) noexcept -> vector3<T>
{
    const auto result = rotate_by({vec.y, vec.z}, angle, {center.y, center.z});
    return {vec.x, result.x, result.y};
}

template <common::concepts::arithmetic_convertible T, std::floating_point U>
[[nodiscard]] inline constexpr auto interpolate(const vector3<T> &val1, const vector3<T> &val2, const U ratio) noexcept
    -> vector3<T>
{
    const auto inverted = (U(1.0) - ratio);

    return vector3<T>{static_cast<U>(val1.x) * inverted + static_cast<U>(val2.x) * ratio,
                      static_cast<U>(val1.y) * inverted + static_cast<U>(val2.y) * ratio,
                      static_cast<U>(val1.z) * inverted + static_cast<U>(val2.z) * ratio};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ptr(vector3<T> &vec) noexcept -> T *
{
    return &vec.x;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ptr(const vector3<T> &vec) noexcept -> const T *
{
    return &vec.x;
}

} // namespace aeon::math
