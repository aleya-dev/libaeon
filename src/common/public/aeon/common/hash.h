// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <functional>
#include <cstdint>
#include <cstddef>

namespace aeon::Common
{

/*!
 * Magic number used in the TEA algorithm (Tiny Encryption Algorithm)
 *
 * The value originates from the golden ratio:
 * phi = (1 + sqrt(5)) / 2 = 1,6180339887498948482045868343656.
 * (int)(2^32 / phi) = 2654435769 = 0x9e3779b97f4a7c16
 */
template <typename T>
struct HashConstants
{
};

template <>
struct HashConstants<std::size_t>
{
    static constexpr auto GoldenRatio = 0x9e3779b97f4a7c16ull;
};

namespace Internal
{
template <typename T>
void HashCombineImpl(std::size_t &seed, const T &v)
{
    seed ^= std::hash<T>{}(v) + HashConstants<std::size_t>::GoldenRatio + (seed << 6) + (seed >> 2);
}
} // namespace internal

/*!
 * Helper function that can be used to combine multiple values into a single hash
 * Should be called for each value that needs to be hashed.
 */
template <typename... ArgsT>
void HashCombine(std::size_t &seed, ArgsT &&...args)
{
    (Internal::HashCombineImpl(seed, std::forward<ArgsT>(args)), ...);
}

/*!
 * Helper function that can be used to combine multiple values into a single hash
 * This version of the function returns the final hash instead of applying it to an existing value.
 */
template <typename... ArgsT>
[[nodiscard]] auto HashCombined(ArgsT &&...args)
{
    std::size_t seed = 0;
    (Internal::HashCombineImpl(seed, std::forward<ArgsT>(args)), ...);
    return seed;
}

} // namespace aeon::Common

template <typename T, typename U>
struct std::hash<std::pair<T, U>>
{
    inline auto operator()(const std::pair<T, U> &val) const noexcept -> std::size_t
    {
        return aeon::Common::HashCombined(val.first, val.second);
    }
};

template <typename... args_t>
struct std::hash<std::tuple<args_t...>>
{
    inline auto operator()(const std::tuple<args_t...> &val) const noexcept -> std::size_t
    {
        return std::apply([](auto &...arg) { return aeon::Common::HashCombined(arg...); }, val);
    }
};
