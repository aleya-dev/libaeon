// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/compilers.h>
#include <aeon/common/concepts.h>
#include <cstdint>

namespace aeon::Common
{

AEON_PACK_STRUCT_PUSH(1)
template <Concepts::Arithmetic T>
class ColorRgb
{
public:
    using Type = T;

    constexpr ColorRgb() noexcept;
    constexpr explicit ColorRgb(const Type r, const Type g, const Type b) noexcept;

    template <Concepts::Arithmetic U>
    constexpr explicit ColorRgb(const U r, const U g, const U b) noexcept;

    template <Concepts::Arithmetic U>
    constexpr explicit ColorRgb(const ColorRgb<U> color) noexcept;

    ~ColorRgb() = default;

    constexpr ColorRgb(const ColorRgb &) noexcept = default;
    constexpr auto operator=(const ColorRgb &) noexcept -> ColorRgb & = default;

    constexpr ColorRgb(ColorRgb &&) noexcept = default;
    constexpr auto operator=(ColorRgb &&) noexcept -> ColorRgb & = default;

    Type R;
    Type G;
    Type B;
} AEON_PACK_STRUCT_POP(1);

using ColorRgbU = ColorRgb<std::uint8_t>;
using ColorRgbF = ColorRgb<float>;
using ColorRgbD = ColorRgb<double>;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <Concepts::Arithmetic T>
[[nodiscard]] inline constexpr auto Ptr(ColorRgb<T> &color) noexcept -> T *;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <Concepts::Arithmetic T>
[[nodiscard]] inline constexpr auto Ptr(const ColorRgb<T> &color) noexcept -> const T *;

template <Concepts::Arithmetic T>
inline constexpr auto operator==(const ColorRgb<T> &lhs, const ColorRgb<T> &rhs) noexcept -> bool;

template <Concepts::Arithmetic T>
inline constexpr auto operator!=(const ColorRgb<T> &lhs, const ColorRgb<T> &rhs) noexcept -> bool;

AEON_PACK_STRUCT_PUSH(1)
template <Concepts::Arithmetic T>
class ColorRgba
{
public:
    using Type = T;

    constexpr ColorRgba() noexcept;

    constexpr explicit ColorRgba(const Type r, const Type g, const Type b) noexcept;
    constexpr explicit ColorRgba(const Type r, const Type g, const Type b, const Type a) noexcept;

    constexpr explicit ColorRgba(const ColorRgb<Type> color) noexcept;
    constexpr explicit ColorRgba(const ColorRgb<Type> color, const Type a) noexcept;

    template <Concepts::Arithmetic U>
    constexpr explicit ColorRgba(const U r, const U g, const U b) noexcept;

    template <Concepts::Arithmetic U>
    constexpr explicit ColorRgba(const U r, const U g, const U b, const U a) noexcept;

    template <Concepts::Arithmetic U>
    constexpr explicit ColorRgba(const ColorRgb<U> color) noexcept;

    template <Concepts::Arithmetic U>
    constexpr explicit ColorRgba(const ColorRgb<U> color, const U a) noexcept;

    template <Concepts::Arithmetic U>
    constexpr explicit ColorRgba(const ColorRgba<U> color) noexcept;

    ~ColorRgba() = default;

    constexpr ColorRgba(const ColorRgba &) noexcept = default;
    constexpr auto operator=(const ColorRgba &) noexcept -> ColorRgba & = default;

    constexpr ColorRgba(ColorRgba &&) noexcept = default;
    constexpr auto operator=(ColorRgba &&) noexcept -> ColorRgba & = default;

    Type R;
    Type G;
    Type B;
    Type A;
} AEON_PACK_STRUCT_POP(1);

using ColorRgbaU = ColorRgba<std::uint8_t>;
using ColorRgbaF = ColorRgba<float>;
using ColorRgbaD = ColorRgba<double>;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b a]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <Concepts::Arithmetic T>
[[nodiscard]] inline constexpr auto Ptr(ColorRgba<T> &color) noexcept -> T *;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b a]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <Concepts::Arithmetic T>
[[nodiscard]] inline constexpr auto Ptr(const ColorRgba<T> &color) noexcept -> const T *;

template <Concepts::Arithmetic T>
inline constexpr auto operator==(const ColorRgba<T> &lhs, const ColorRgba<T> &rhs) noexcept -> bool;

template <Concepts::Arithmetic T>
inline constexpr auto operator!=(const ColorRgba<T> &lhs, const ColorRgba<T> &rhs) noexcept -> bool;

} // namespace aeon::Common

#include <aeon/common/impl/color_impl.h>
