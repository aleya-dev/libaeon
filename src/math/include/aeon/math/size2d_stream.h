// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/math/size2d.h>
#include <ostream>

namespace aeon::math
{

template <typename T>
inline auto operator<<(std::ostream &os, const size2d<T> &s) -> std::ostream &
{
    return os << "size2d<" << typeid(T).name() << ">(" << width(s) << ", " << height(s) << ")";
}

} // namespace aeon::math
