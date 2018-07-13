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

#include <aeon/common/deprecated.h>
#include <exception>

namespace aeon::common
{

class optional_value_exception : public std::exception
{
};

template <typename T>
AEON_DEPRECATED("Replaced by std::optional.")
class optional
{
public:
    optional()
        : value_{}
        , has_value_{false}
    {
    }

    optional(T val)
        : value_{std::move(val)}
        , has_value_{true}
    {
    }

    optional(optional &&) noexcept = default;
    auto operator=(optional &&) noexcept -> optional & = default;

    optional(const optional &) = default;
    auto operator=(const optional &) -> optional & = default;

    bool has_value() const noexcept
    {
        return has_value_;
    }

    const T &get_value() const
    {
        if (!has_value_)
            throw optional_value_exception();

        return value_;
    }

    void reset() noexcept
    {
        has_value_ = false;
    }

    operator T() const
    {
        if (!has_value_)
            throw optional_value_exception();

        return value_;
    }

    auto &operator=(const T &val)
    {
        value_ = val;
        has_value_ = true;
        return *this;
    }

private:
    T value_;
    bool has_value_;
};

} // namespace aeon::common
