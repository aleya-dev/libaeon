// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline constexpr auto operator==(const plane<T> &lhs, const plane<T> &rhs) noexcept -> bool
{
    return normal(lhs) == normal(rhs) && distance(lhs) == distance(rhs);
}

template <typename T>
inline constexpr auto operator!=(const plane<T> &lhs, const plane<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math