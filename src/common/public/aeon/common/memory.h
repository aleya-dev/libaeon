// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <memory>
#include <stdexcept>

namespace aeon::Common
{

/*!
 * Dynamic cast a unique_ptr to another type. If the cast fails, a nullptr will be returned.
 * Be aware that this means that the originally given unique_ptr gets deleted.
 */
template <typename T, typename U>
[[nodiscard]] inline auto DynamicUniquePtrCast(std::unique_ptr<U> &&ptr) -> std::unique_ptr<T>
{
    auto result = dynamic_cast<T *>(ptr.get());

    if (!result)
        return nullptr;

    auto retVal = std::unique_ptr<T>{result};
    ptr.release();
    return retVal;
}

/*!
 * Static cast a unique_ptr to another type.
 */
template <typename T, typename U>
[[nodiscard]] inline auto StaticUniquePtrCast(std::unique_ptr<U> &&ptr) noexcept -> std::unique_ptr<T>
{
    return std::unique_ptr<T>{static_cast<T *>(ptr.release())};
}

} // namespace aeon::Common
