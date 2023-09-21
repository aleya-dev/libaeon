// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/concepts.h>
#include <limits>

namespace aeon::Common
{

template <Concepts::Arithmetic T>
struct ColorLimits final
{
    [[nodiscard]] static constexpr auto Min() noexcept -> T
    {
        return std::numeric_limits<T>::min();
    }

    [[nodiscard]] static constexpr auto Max() noexcept -> T
    {
        return std::numeric_limits<T>::max();
    }
};

template <>
struct ColorLimits<float> final
{
    [[nodiscard]] static constexpr auto Min() noexcept -> float
    {
        return 0.0f;
    }

    [[nodiscard]] static constexpr auto Max() noexcept -> float
    {
        return 1.0f;
    }
};

template <>
struct ColorLimits<double> final
{
    [[nodiscard]] static constexpr auto Min() noexcept -> double
    {
        return 0.0;
    }

    [[nodiscard]] static constexpr auto Max() noexcept -> double
    {
        return 1.0;
    }
};

} // namespace aeon::Common
