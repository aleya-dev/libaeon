// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/concepts.h>

namespace aeon::math
{

class mat;

template <typename T>
class mat_view_base;

class mat3;

class mat4;

class quaternion;

template <Common::Concepts::ArithmeticConvertible T>
class vector2;

template <Common::Concepts::ArithmeticConvertible T>
class vector3;

template <Common::Concepts::ArithmeticConvertible T>
class vector4;

template <Common::Concepts::ArithmeticConvertible T>
class size2d;

template <Common::Concepts::ArithmeticConvertible T>
class size3d;

template <typename T>
class range;

template <Common::Concepts::ArithmeticConvertible T>
class rectangle;

} // namespace aeon::math
