// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/preprocessor.h>
#include <cassert>

#define AeonAssert(condition, message) assert((condition) && message)
#define AeonAssertFail(message) AeonAssert(false, message)

#define AeonAssertValueMin(val, min)                                                                                \
    AeonAssert((val >= min), "Value " #val " is out of range. Given value must be >= " #min)
#define AeonAssertValueMax(val, max)                                                                                \
    AeonAssert((val <= max), "Value " #val " is out of range. Given value must be <= " #max)
#define AeonAssertValueInRange(val, min, max)                                                                      \
    AeonAssert((val >= min && val <= max),                                                                            \
                "Value " #val " is out of range. Given value must be >= " #min " and <= " #max)

#define AeonAssertIndexBounds(val, count)                                                                           \
    AeonAssert((val < count), "Value " #val " is out of bounds. Given index must be < " #count)
#define AeonAssertArrayBounds(val, index)                                                                           \
    AeonAssert((index < (AeonArrayLength(val))), "Array index " #index " is out of bounds for " #val)
#define AeonAssertSizeBounds(val, index)                                                                            \
    AeonAssert((static_cast<std::size_t>(index) < (std::size(val))),                                                  \
                "Array index " #index " is out of bounds for " #val)
