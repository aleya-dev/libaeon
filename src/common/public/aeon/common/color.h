// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/compilers.h>
#include <aeon/common/concepts.h>
#include <cstdint>

namespace aeon::common
{

AEON_PACK_STRUCT_PUSH(1)
template <concepts::arithmetic T>
class color_rgb
{
public:
    using type = T;

    constexpr color_rgb() noexcept;
    constexpr explicit color_rgb(const type r, const type g, const type b) noexcept;

    template <concepts::arithmetic U>
    constexpr explicit color_rgb(const U r, const U g, const U b) noexcept;

    template <concepts::arithmetic U>
    constexpr explicit color_rgb(const color_rgb<U> color) noexcept;

    ~color_rgb() = default;

    constexpr color_rgb(const color_rgb &) noexcept = default;
    constexpr auto operator=(const color_rgb &) noexcept -> color_rgb & = default;

    constexpr color_rgb(color_rgb &&) noexcept = default;
    constexpr auto operator=(color_rgb &&) noexcept -> color_rgb & = default;

    type r;
    type g;
    type b;
} AEON_PACK_STRUCT_POP(1);

using color_rgb_u = color_rgb<std::uint8_t>;
using color_rgb_f = color_rgb<float>;
using color_rgb_d = color_rgb<double>;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(color_rgb<T> &color) noexcept -> T *;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(const color_rgb<T> &color) noexcept -> const T *;

template <concepts::arithmetic T>
inline constexpr auto operator==(const color_rgb<T> &lhs, const color_rgb<T> &rhs) noexcept -> bool;

template <concepts::arithmetic T>
inline constexpr auto operator!=(const color_rgb<T> &lhs, const color_rgb<T> &rhs) noexcept -> bool;

AEON_PACK_STRUCT_PUSH(1)
template <concepts::arithmetic T>
class color_rgba
{
public:
    using type = T;

    constexpr color_rgba() noexcept;

    constexpr explicit color_rgba(const type r, const type g, const type b) noexcept;
    constexpr explicit color_rgba(const type r, const type g, const type b, const type a) noexcept;

    constexpr explicit color_rgba(const color_rgb<type> color) noexcept;
    constexpr explicit color_rgba(const color_rgb<type> color, const type a) noexcept;

    template <concepts::arithmetic U>
    constexpr explicit color_rgba(const U r, const U g, const U b) noexcept;

    template <concepts::arithmetic U>
    constexpr explicit color_rgba(const U r, const U g, const U b, const U a) noexcept;

    template <concepts::arithmetic U>
    constexpr explicit color_rgba(const color_rgb<U> color) noexcept;

    template <concepts::arithmetic U>
    constexpr explicit color_rgba(const color_rgb<U> color, const U a) noexcept;

    template <concepts::arithmetic U>
    constexpr explicit color_rgba(const color_rgba<U> color) noexcept;

    ~color_rgba() = default;

    constexpr color_rgba(const color_rgba &) noexcept = default;
    constexpr auto operator=(const color_rgba &) noexcept -> color_rgba & = default;

    constexpr color_rgba(color_rgba &&) noexcept = default;
    constexpr auto operator=(color_rgba &&) noexcept -> color_rgba & = default;

    type r;
    type g;
    type b;
    type a;
} AEON_PACK_STRUCT_POP(1);

using color_rgba_u = color_rgba<std::uint8_t>;
using color_rgba_f = color_rgba<float>;
using color_rgba_d = color_rgba<double>;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b a]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(color_rgba<T> &color) noexcept -> T *;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b a]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(const color_rgba<T> &color) noexcept -> const T *;

template <concepts::arithmetic T>
inline constexpr auto operator==(const color_rgba<T> &lhs, const color_rgba<T> &rhs) noexcept -> bool;

template <concepts::arithmetic T>
inline constexpr auto operator!=(const color_rgba<T> &lhs, const color_rgba<T> &rhs) noexcept -> bool;

} // namespace aeon::common

#include <aeon/common/impl/color_impl.h>
