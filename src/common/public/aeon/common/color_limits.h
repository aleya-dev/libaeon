// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/concepts.h>
#include <limits>

namespace aeon::common
{

template <concepts::arithmetic T>
struct color_limits final
{
    [[nodiscard]] static constexpr auto min() noexcept -> T
    {
        return std::numeric_limits<T>::min();
    }

    [[nodiscard]] static constexpr auto max() noexcept -> T
    {
        return std::numeric_limits<T>::max();
    }
};

template <>
struct color_limits<float> final
{
    [[nodiscard]] static constexpr auto min() noexcept -> float
    {
        return 0.0f;
    }

    [[nodiscard]] static constexpr auto max() noexcept -> float
    {
        return 1.0f;
    }
};

template <>
struct color_limits<double> final
{
    [[nodiscard]] static constexpr auto min() noexcept -> double
    {
        return 0.0;
    }

    [[nodiscard]] static constexpr auto max() noexcept -> double
    {
        return 1.0;
    }
};

} // namespace aeon::common
