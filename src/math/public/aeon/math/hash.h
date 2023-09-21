// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

/*!
 * \file
 * \brief Provides simple hashing implementations for various math types so they can be used in set, map, or any other
 * hash based container.
 */

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/math/vector3.h>
#include <aeon/math/vector4.h>
#include <aeon/math/size2d.h>
#include <aeon/math/size3d.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/range.h>
#include <aeon/math/quaternion.h>
#include <aeon/common/concepts.h>
#include <aeon/common/hash.h>

template <aeon::Common::Concepts::ArithmeticConvertible T>
struct std::hash<aeon::math::vector2<T>>
{
    inline auto operator()(const aeon::math::vector2<T> &val) const noexcept -> std::size_t
    {
        return aeon::Common::hash_combined(val.x, val.y);
    }
};

template <aeon::Common::Concepts::ArithmeticConvertible T>
struct std::hash<aeon::math::vector3<T>>
{
    inline auto operator()(const aeon::math::vector3<T> &val) const noexcept -> std::size_t
    {
        return aeon::Common::hash_combined(val.x, val.y, val.z);
    }
};

template <aeon::Common::Concepts::ArithmeticConvertible T>
struct std::hash<aeon::math::vector4<T>>
{
    inline auto operator()(const aeon::math::vector4<T> &val) const noexcept -> std::size_t
    {
        return aeon::Common::hash_combined(val.x, val.y, val.z, val.w);
    }
};

template <aeon::Common::Concepts::ArithmeticConvertible T>
struct std::hash<aeon::math::size2d<T>>
{
    inline auto operator()(const aeon::math::size2d<T> &val) const noexcept -> std::size_t
    {
        return aeon::Common::hash_combined(val.width, val.height);
    }
};

template <aeon::Common::Concepts::ArithmeticConvertible T>
struct std::hash<aeon::math::size3d<T>>
{
    inline auto operator()(const aeon::math::size3d<T> &val) const noexcept -> std::size_t
    {
        return aeon::Common::hash_combined(val.width, val.height, val.depth);
    }
};

template <aeon::Common::Concepts::ArithmeticConvertible T>
struct std::hash<aeon::math::rectangle<T>>
{
    inline auto operator()(const aeon::math::rectangle<T> &val) const noexcept -> std::size_t
    {
        return aeon::Common::hash_combined(val.left, val.top, val.right, val.bottom);
    }
};

template <aeon::Common::Concepts::ArithmeticConvertible T>
struct std::hash<aeon::math::range<T>>
{
    inline auto operator()(const aeon::math::range<T> &val) const noexcept -> std::size_t
    {
        return aeon::Common::hash_combined(val.begin, val.end);
    }
};

template <>
struct std::hash<aeon::math::quaternion>
{
    inline auto operator()(const aeon::math::quaternion &val) const noexcept -> std::size_t
    {
        return aeon::Common::HashCombined(val.w, val.x, val.y, val.z);
    }
};
