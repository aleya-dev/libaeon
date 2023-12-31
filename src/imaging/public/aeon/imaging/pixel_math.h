// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/imaging/pixel_encoding.h>

namespace aeon::imaging
{

template <typename T>
struct pixel_math final
{
    [[nodiscard]] static constexpr auto component_min() noexcept -> T
    {
        return std::numeric_limits<T>::min();
    }

    [[nodiscard]] static constexpr auto min() noexcept -> T
    {
        return std::numeric_limits<T>::min();
    }

    [[nodiscard]] static constexpr auto component_max() noexcept -> T
    {
        return std::numeric_limits<T>::max();
    }

    [[nodiscard]] static constexpr auto max() noexcept -> T
    {
        return std::numeric_limits<T>::max();
    }

    [[nodiscard]] static constexpr auto clamp(const int value) noexcept -> T
    {
        return static_cast<T>(std::clamp(value, static_cast<int>(min()), static_cast<int>(max())));
    }

    [[nodiscard]] static constexpr auto clamp(const unsigned int value) noexcept -> T
    {
        return static_cast<T>(std::clamp(static_cast<int>(value), static_cast<int>(min()), static_cast<int>(max())));
    }

    [[nodiscard]] static constexpr auto clamp(const float value) noexcept -> T
    {
        return static_cast<T>(std::clamp(static_cast<int>(value), static_cast<int>(min()), static_cast<int>(max())));
    }

    [[nodiscard]] static constexpr auto alpha(const T value) noexcept -> T
    {
        return value;
    }

    [[nodiscard]] static constexpr auto alpha_ratio(const T value) noexcept -> float
    {
        return static_cast<float>(value) / static_cast<float>(max());
    }
};

template <>
struct pixel_math<float> final
{
    [[nodiscard]] static constexpr auto component_min() noexcept -> float
    {
        return 0.0f;
    }

    [[nodiscard]] static constexpr auto min() noexcept -> float
    {
        return 0.0f;
    }

    [[nodiscard]] static constexpr auto component_max() noexcept -> float
    {
        return 1.0f;
    }

    [[nodiscard]] static constexpr auto max() noexcept -> float
    {
        return 1.0f;
    }

    [[nodiscard]] static constexpr auto clamp(const float value) noexcept -> float
    {
        return std::clamp(value, min(), max());
    }

    [[nodiscard]] static constexpr auto alpha(const float value) noexcept -> float
    {
        return value;
    }

    [[nodiscard]] static constexpr auto alpha_ratio(const float value) noexcept -> float
    {
        return value / max();
    }
};

template <>
struct pixel_math<rgb24> final
{
    [[nodiscard]] static constexpr auto component_min() noexcept -> std::uint8_t
    {
        return 0;
    }

    [[nodiscard]] static constexpr auto min() noexcept -> rgb24
    {
        return rgb24{component_min(), component_min(), component_min()};
    }

    [[nodiscard]] static constexpr auto component_max() noexcept -> std::uint8_t
    {
        return 255;
    }

    [[nodiscard]] static constexpr auto max() noexcept -> rgb24
    {
        return rgb24{component_max(), component_max(), component_max()};
    }

    [[nodiscard]] static constexpr auto clamp(const rgb24 value) noexcept -> rgb24
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255))};
    }

    [[nodiscard]] static constexpr auto alpha([[maybe_unused]] const rgb24 value) noexcept -> std::uint8_t
    {
        return 255;
    }

    [[nodiscard]] static constexpr auto alpha_ratio([[maybe_unused]] const rgb24 value) noexcept -> float
    {
        return 1.0f;
    }
};

template <>
struct pixel_math<rgba32> final
{
    [[nodiscard]] static constexpr auto component_min() noexcept -> std::uint8_t
    {
        return 0;
    }

    [[nodiscard]] static constexpr auto min() noexcept -> rgba32
    {
        return rgba32{component_min(), component_min(), component_min(), component_min()};
    }

    [[nodiscard]] static constexpr auto component_max() noexcept -> std::uint8_t
    {
        return 255;
    }

    [[nodiscard]] static constexpr auto max() noexcept -> rgba32
    {
        return rgba32{component_max(), component_max(), component_max(), component_max()};
    }

    [[nodiscard]] static constexpr auto clamp(const rgba32 value) noexcept -> rgba32
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.a), 0, 255))};
    }

    [[nodiscard]] static constexpr auto alpha(const rgba32 value) noexcept -> std::uint8_t
    {
        return value.a;
    }

    [[nodiscard]] static constexpr auto alpha_ratio(const rgba32 value) noexcept -> float
    {
        return static_cast<float>(alpha(value)) / static_cast<float>(component_max());
    }
};

template <>
struct pixel_math<bgr24> final
{
    [[nodiscard]] static constexpr auto component_min() noexcept -> std::uint8_t
    {
        return 0;
    }

    [[nodiscard]] static constexpr auto min() noexcept -> bgr24
    {
        return bgr24{component_min(), component_min(), component_min()};
    }

    [[nodiscard]] static constexpr auto component_max() noexcept -> std::uint8_t
    {
        return 255;
    }

    [[nodiscard]] static constexpr auto max() noexcept -> bgr24
    {
        return bgr24{component_max(), component_max(), component_max()};
    }

    [[nodiscard]] static constexpr auto clamp(const bgr24 value) noexcept -> bgr24
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255))};
    }

    [[nodiscard]] static constexpr auto alpha([[maybe_unused]] const bgr24 value) noexcept -> std::uint8_t
    {
        return 255;
    }

    [[nodiscard]] static constexpr auto alpha_ratio([[maybe_unused]] const bgr24 value) noexcept -> float
    {
        return 1.0f;
    }
};

template <>
struct pixel_math<bgra32> final
{
    [[nodiscard]] static constexpr auto component_min() noexcept -> std::uint8_t
    {
        return 0;
    }

    [[nodiscard]] static constexpr auto min() noexcept -> bgra32
    {
        return bgra32{component_min(), component_min(), component_min(), component_min()};
    }

    [[nodiscard]] static constexpr auto component_max() noexcept -> std::uint8_t
    {
        return 255;
    }

    [[nodiscard]] static constexpr auto max() noexcept -> bgra32
    {
        return bgra32{component_max(), component_max(), component_max(), component_max()};
    }

    [[nodiscard]] static constexpr auto clamp(const bgra32 value) noexcept -> bgra32
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.a), 0, 255))};
    }

    [[nodiscard]] static constexpr auto alpha(const bgra32 value) noexcept -> std::uint8_t
    {
        return value.a;
    }

    [[nodiscard]] static constexpr auto alpha_ratio(const bgra32 value) noexcept -> float
    {
        return static_cast<float>(alpha(value)) / static_cast<float>(component_max());
    }
};

} // namespace aeon::imaging
