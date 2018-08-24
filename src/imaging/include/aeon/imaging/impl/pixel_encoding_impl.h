/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <algorithm>

namespace aeon::imaging
{

inline auto operator*(const rgb24 lhs, const float rhs) noexcept -> rgb24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r * rhs, 0.0f, 255.0f)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs, 0.0f, 255.0f)),
            static_cast<std::uint8_t>(std::clamp(lhs.b * rhs, 0.0f, 255.0f))};
}

inline auto operator*=(rgb24 &lhs, const float rhs) noexcept -> rgb24
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*(const rgb24 lhs, const rgb24 rhs) noexcept -> rgb24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r * rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b * rhs.b, 0, 255))};
}

inline auto operator*=(rgb24 &lhs, const rgb24 rhs) noexcept -> rgb24
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator+(const rgb24 lhs, const rgb24 rhs) noexcept -> rgb24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r + rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g + rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b + rhs.b, 0, 255))};
}

inline auto operator+=(rgb24 &lhs, const rgb24 rhs) noexcept -> rgb24
{
    lhs = lhs + rhs;
    return lhs;
}

inline auto operator-(const rgb24 lhs, const rgb24 rhs) noexcept -> rgb24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r - rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g - rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b - rhs.b, 0, 255))};
}

inline auto operator-=(rgb24 &lhs, const rgb24 rhs) noexcept -> rgb24
{
    lhs = lhs - rhs;
    return lhs;
}

inline auto operator*(const rgba32 lhs, const float rhs) noexcept -> rgba32
{
    return {
        static_cast<std::uint8_t>(std::clamp(lhs.r * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.g * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.b * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.a * rhs, 0.0f, 255.0f)),
    };
}

inline auto operator*=(rgba32 &lhs, const float rhs) noexcept -> rgba32
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*(const rgba32 lhs, const rgba32 rhs) noexcept -> rgba32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r * rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b * rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a * rhs.a, 0, 255))};
}

inline auto operator*=(rgba32 &lhs, const rgba32 rhs) noexcept -> rgba32
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator+(const rgba32 lhs, const rgba32 rhs) noexcept -> rgba32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r + rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g + rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b + rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a + rhs.a, 0, 255))};
}

inline auto operator+=(rgba32 &lhs, const rgba32 rhs) noexcept -> rgba32
{
    lhs = lhs + rhs;
    return lhs;
}

inline auto operator-(const rgba32 lhs, const rgba32 rhs) noexcept -> rgba32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r - rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g - rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b - rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a - rhs.a, 0, 255))};
}

inline auto operator-=(rgba32 &lhs, const rgba32 rhs) noexcept -> rgba32
{
    lhs = lhs - rhs;
    return lhs;
}

inline auto operator*(const bgr24 lhs, const float rhs) noexcept -> bgr24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b * rhs, 0.0f, 255.0f)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs, 0.0f, 255.0f)),
            static_cast<std::uint8_t>(std::clamp(lhs.r * rhs, 0.0f, 255.0f))};
}

inline auto operator*=(bgr24 &lhs, const float rhs) noexcept -> bgr24
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*(const bgr24 lhs, const bgr24 rhs) noexcept -> bgr24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b * rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r * rhs.r, 0, 255))};
}

inline auto operator*=(bgr24 &lhs, const bgr24 rhs) noexcept -> bgr24
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator+(const bgr24 lhs, const bgr24 rhs) noexcept -> bgr24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b + rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g + rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r + rhs.r, 0, 255))};
}

inline auto operator+=(bgr24 &lhs, const bgr24 rhs) noexcept -> bgr24
{
    lhs = lhs + rhs;
    return lhs;
}

inline auto operator-(const bgr24 lhs, const bgr24 rhs) noexcept -> bgr24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b - rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g - rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r - rhs.r, 0, 255))};
}

inline auto operator-=(bgr24 &lhs, const bgr24 rhs) noexcept -> bgr24
{
    lhs = lhs - rhs;
    return lhs;
}

inline auto operator*(const bgra32 lhs, const float rhs) noexcept -> bgra32
{
    return {
        static_cast<std::uint8_t>(std::clamp(lhs.b * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.g * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.r * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.a * rhs, 0.0f, 255.0f)),
    };
}

inline auto operator*=(bgra32 &lhs, const float rhs) noexcept -> bgra32
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*(const bgra32 lhs, const bgra32 rhs) noexcept -> bgra32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b * rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r * rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a * rhs.a, 0, 255))};
}

inline auto operator*=(bgra32 &lhs, const bgra32 rhs) noexcept -> bgra32
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator+(const bgra32 lhs, const bgra32 rhs) noexcept -> bgra32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b + rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g + rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r + rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a + rhs.a, 0, 255))};
}

inline auto operator+=(bgra32 &lhs, const bgra32 rhs) noexcept -> bgra32
{
    lhs = lhs + rhs;
    return lhs;
}

inline auto operator-(const bgra32 lhs, const bgra32 rhs) noexcept -> bgra32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b - rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g - rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r - rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a - rhs.a, 0, 255))};
}

inline auto operator-=(bgra32 &lhs, const bgra32 rhs) noexcept -> bgra32
{
    lhs = lhs - rhs;
    return lhs;
}

} // namespace aeon::imaging