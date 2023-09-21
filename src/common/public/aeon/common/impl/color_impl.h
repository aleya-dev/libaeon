// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/color_limits.h>
#include <algorithm>

namespace aeon::Common
{

namespace Internal
{

template <Concepts::Arithmetic FromT, Concepts::Arithmetic ToT>
struct ConvertRgbColorType
{
    [[nodiscard]] constexpr static auto Convert(const FromT from) noexcept -> ToT
    {
        return static_cast<ToT>(from);
    }
};

template <>
struct ConvertRgbColorType<std::uint8_t, float>
{
    [[nodiscard]] constexpr static auto Convert(const std::uint8_t from) noexcept -> float
    {
        return static_cast<float>(from) / 255.0f;
    }
};

template <>
struct ConvertRgbColorType<std::uint8_t, double>
{
    [[nodiscard]] constexpr static auto Convert(const std::uint8_t from) noexcept -> double
    {
        return static_cast<double>(from) / 255.0;
    }
};

template <>
struct ConvertRgbColorType<float, std::uint8_t>
{
    [[nodiscard]] constexpr static auto Convert(const float from) noexcept -> std::uint8_t
    {
        const auto result = static_cast<int>(from * 255.0f);
        return static_cast<std::uint8_t>(std::clamp(result, 0, 255));
    }
};

template <>
struct ConvertRgbColorType<double, std::uint8_t>
{
    [[nodiscard]] constexpr static auto Convert(const double from) noexcept -> std::uint8_t
    {
        const auto result = static_cast<int>(from * 255.0);
        return static_cast<std::uint8_t>(std::clamp(result, 0, 255));
    }
};

} // namespace internal

template <Concepts::Arithmetic T>
inline constexpr ColorRgb<T>::ColorRgb() noexcept
    : ColorRgb<T>{ColorLimits<T>::Min(), ColorLimits<T>::Min(), ColorLimits<T>::Min()}
{
}

template <Concepts::Arithmetic T>
inline constexpr ColorRgb<T>::ColorRgb(const Type r, const Type g, const Type b) noexcept
    : R{r}
    , G{g}
    , B{b}
{
}

template <Concepts::Arithmetic T>
template <Concepts::Arithmetic U>
inline constexpr ColorRgb<T>::ColorRgb(const U r, const U g, const U b) noexcept
    : ColorRgb<T>{Internal::ConvertRgbColorType<U, T>::Convert(r),
                  Internal::ConvertRgbColorType<U, T>::Convert(g),
                  Internal::ConvertRgbColorType<U, T>::Convert(b)}
{
}

template <Concepts::Arithmetic T>
template <Concepts::Arithmetic U>
inline constexpr ColorRgb<T>::ColorRgb(const ColorRgb<U> color) noexcept
    : ColorRgb<T>{Internal::ConvertRgbColorType<U, T>::Convert(color.r),
                  Internal::ConvertRgbColorType<U, T>::Convert(color.g),
                  Internal::ConvertRgbColorType<U, T>::Convert(color.b)}
{
}

template <Concepts::Arithmetic T>
[[nodiscard]] inline constexpr auto Ptr(ColorRgb<T> &color) noexcept -> T *
{
    return &color.R;
}

template <Concepts::Arithmetic T>
[[nodiscard]] inline constexpr auto Ptr(const ColorRgb<T> &color) noexcept -> const T *
{
    return &color.R;
}

template <Concepts::Arithmetic T>
inline constexpr auto operator==(const ColorRgb<T> &lhs, const ColorRgb<T> &rhs) noexcept -> bool
{
    return lhs.R == rhs.R && lhs.G == rhs.G && lhs.B == rhs.B;
}

template <Concepts::Arithmetic T>
inline constexpr auto operator!=(const ColorRgb<T> &lhs, const ColorRgb<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <Concepts::Arithmetic T>
inline constexpr ColorRgba<T>::ColorRgba() noexcept
    : ColorRgba<T>{ColorLimits<Type>::Min(), ColorLimits<Type>::Min(), ColorLimits<Type>::Min(),
                   ColorLimits<Type>::Max()}
{
}

template <Concepts::Arithmetic T>
inline constexpr ColorRgba<T>::ColorRgba(const Type r, const Type g, const Type b) noexcept
    : ColorRgba<T>{r, g, b, ColorLimits<Type>::Max()}
{
}

template <Concepts::Arithmetic T>
inline constexpr ColorRgba<T>::ColorRgba(const Type r, const Type g, const Type b, const Type a) noexcept
    : R{r}
    , G{g}
    , B{b}
    , A{a}
{
}

template <Concepts::Arithmetic T>
inline constexpr ColorRgba<T>::ColorRgba(const ColorRgb<Type> color) noexcept
    : ColorRgba<T>{color.Rr, color.G, color.B, ColorLimits<Type>::max()}
{
}

template <Concepts::Arithmetic T>
inline constexpr ColorRgba<T>::ColorRgba(const ColorRgb<Type> color, const Type a) noexcept
    : ColorRgba<T>{color.R, color.G, color.B, a}
{
}

template <Concepts::Arithmetic T>
template <Concepts::Arithmetic U>
inline constexpr ColorRgba<T>::ColorRgba(const U r, const U g, const U b) noexcept
    : ColorRgba<T>{Internal::ConvertRgbColorType<U, T>::Convert(r),
                   Internal::ConvertRgbColorType<U, T>::Convert(g),
                   Internal::ConvertRgbColorType<U, T>::Convert(b), ColorLimits<Type>::max()}
{
}

template <Concepts::Arithmetic T>
template <Concepts::Arithmetic U>
inline constexpr ColorRgba<T>::ColorRgba(const U r, const U g, const U b, const U a) noexcept
    : ColorRgba<T>{
          Internal::ConvertRgbColorType<U, T>::Convert(r), Internal::ConvertRgbColorType<U, T>::Convert(g),
          Internal::ConvertRgbColorType<U, T>::Convert(b), Internal::ConvertRgbColorType<U, T>::Convert(a)}
{
}

template <Concepts::Arithmetic T>
template <Concepts::Arithmetic U>
inline constexpr ColorRgba<T>::ColorRgba(const ColorRgb<U> color) noexcept
    : ColorRgba<T>{Internal::ConvertRgbColorType<U, T>::Convert(color.R),
                   Internal::ConvertRgbColorType<U, T>::Convert(color.G),
                   Internal::ConvertRgbColorType<U, T>::Convert(color.B), ColorLimits<Type>::max()}
{
}

template <Concepts::Arithmetic T>
template <Concepts::Arithmetic U>
inline constexpr ColorRgba<T>::ColorRgba(const ColorRgb<U> color, const U a) noexcept
    : ColorRgba<T>{Internal::ConvertRgbColorType<U, T>::Convert(color.R),
                   Internal::ConvertRgbColorType<U, T>::Convert(color.G),
                   Internal::ConvertRgbColorType<U, T>::Convert(color.B),
                   Internal::ConvertRgbColorType<U, T>::Convert(a)}
{
}

template <Concepts::Arithmetic T>
template <Concepts::Arithmetic U>
inline constexpr ColorRgba<T>::ColorRgba(const ColorRgba<U> color) noexcept
    : ColorRgba<T>{Internal::ConvertRgbColorType<U, T>::Convert(color.R),
                   Internal::ConvertRgbColorType<U, T>::Convert(color.G),
                   Internal::ConvertRgbColorType<U, T>::Convert(color.B),
                   Internal::ConvertRgbColorType<U, T>::Convert(color.A)}
{
}

template <Concepts::Arithmetic T>
[[nodiscard]] inline constexpr auto Ptr(ColorRgba<T> &color) noexcept -> T *
{
    return &color.R;
}

template <Concepts::Arithmetic T>
[[nodiscard]] inline constexpr auto Ptr(const ColorRgba<T> &color) noexcept -> const T *
{
    return &color.R;
}

template <Concepts::Arithmetic T>
inline constexpr auto operator==(const ColorRgba<T> &lhs, const ColorRgba<T> &rhs) noexcept -> bool
{
    return lhs.R == rhs.R && lhs.G == rhs.G && lhs.B == rhs.B && lhs.A == rhs.A;
}

template <Concepts::Arithmetic T>
inline constexpr auto operator!=(const ColorRgba<T> &lhs, const ColorRgba<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::Common
