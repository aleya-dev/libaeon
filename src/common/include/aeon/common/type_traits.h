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

#include <cstdint>

namespace aeon::common::type_traits
{

/*!
 * Get the amount of arguments in a function signature type.
 */
template <typename return_type_t>
struct function_signature_argument_count;

template <typename return_type_t, typename... args_t>
struct function_signature_argument_count<return_type_t(args_t...)>
{
    static constexpr auto value = sizeof...(args_t);
};

/*!
 * Get a representing integer type based on given number of bits
 */
template <unsigned int bits>
struct integer_type_from_bits;

template<>
struct integer_type_from_bits<8>
{
    using signed_t = std::int8_t;
    using unsigned_t = std::uint8_t;
};

template<>
struct integer_type_from_bits<16>
{
    using signed_t = std::int16_t;
    using unsigned_t = std::uint16_t;
};

template<>
struct integer_type_from_bits<32>
{
    using signed_t = std::int32_t;
    using unsigned_t = std::uint32_t;
};

template<>
struct integer_type_from_bits<64>
{
    using signed_t = std::int64_t;
    using unsigned_t = std::uint64_t;
};

} // namespace aeon::common::type_traits
