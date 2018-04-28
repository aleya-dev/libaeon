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

#include <cmath>
#include <algorithm>

namespace aeon::math
{

inline quaternion::quaternion() noexcept
    : w{}
    , x{}
    , y{}
    , z{}
{
}

inline quaternion::quaternion(const float w, const float x, const float y, const float z) noexcept
    : w{w}
    , x{x}
    , y{y}
    , z{z}
{
}

inline quaternion::quaternion(const vector3<float> &euler) noexcept
{
    const auto c = cos(euler * 0.5f);
    const auto s = sin(euler * 0.5f);

    w = c.x * c.y * c.z + s.x * s.y * s.z;
    x = s.x * c.y * c.z - c.x * s.y * s.z;
    y = c.x * s.y * c.z + s.x * c.y * s.z;
    z = c.x * c.y * s.z - s.x * s.y * c.z;
}

inline auto quaternion::indentity() noexcept -> quaternion
{
    return {1.0f, 0.0f, 0.0f, 0.0f};
}

inline void quaternion::set(const float new_w, const float new_x, const float new_y, const float new_z) noexcept
{
    w = new_w;
    x = new_x;
    y = new_y;
    z = new_z;
}

inline auto pitch(const quaternion &quat) noexcept -> float
{
    return std::atan2(2.0f * (quat.y * quat.z + quat.w * quat.x),
                      quat.w * quat.w - quat.x * quat.x - quat.y * quat.y + quat.z * quat.z);
}

inline auto yaw(const quaternion &quat) noexcept -> float
{
    return std::asin(std::clamp(-2.0f * (quat.x * quat.z - quat.w * quat.y), -1.0f, 1.0f));
}

inline auto roll(const quaternion &quat) noexcept -> float
{
    return std::atan2(2.0f * (quat.x * quat.y + quat.w * quat.z),
                      quat.w * quat.w + quat.x * quat.x - quat.y * quat.y - quat.z * quat.z);
}

inline auto euler(const quaternion &quat) noexcept -> vector3<float>
{
    return {pitch(quat), yaw(quat), roll(quat)};
}

inline auto dot(const quaternion &a, const quaternion &b) noexcept -> float
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline auto ptr(quaternion &quat) noexcept -> float *
{
    return &quat.w;
}

inline auto ptr(const quaternion &quat) noexcept -> const float *
{
    return &quat.w;
}

} // namespace aeon::math