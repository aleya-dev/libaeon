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

#include <aeon/math/impl/units_prefixes.h>
#include <aeon/common/type_traits.h>
#include <type_traits>

namespace aeon::math
{

/*!
 * Check if a given unit is of the same type (ie. a unit of distance, or a unit of mass etc.)
 */
template <typename T, typename U>
struct unit_is_same_type
{
    static constexpr auto value = std::is_same<typename T::type, typename U::type>::value;
};

/*!
 * Convenience value variant of unit_is_same_type.
 */
template <typename T, typename U>
inline constexpr auto unit_is_same_type_v = unit_is_same_type<T, U>::value;

/*!
 * Get the unit type from a given combination of unit template arguments
 * <type, void> or <prefix, type>
 */
template <typename T, typename U>
struct unit_type
{
    using type = std::conditional_t<std::is_same_v<U, void>, T, U>;
};

/*!
 * Convenience type variant of unit_type.
 */
template <typename T, typename U>
using unit_type_t = typename unit_type<T, U>::type;

/*!
 * Get the prefix multiplication modifier value for a given template.
 * If the template isn't a prefix, value is 1.0.
 */
template <typename T>
struct prefix_value
{
private:
    static constexpr auto get() noexcept -> double
    {
        if constexpr (std::is_base_of_v<prefix, T>)
        {
            return T::value;
        }
        else
        {
            return 1.0;
        }
    }

public:
    static constexpr auto value = get();
};

/*!
 * Convenience value variant of prefix_value.
 */
template <typename T>
inline constexpr auto prefix_value_v = prefix_value<T>::value;

/*!
 * Check if a given unit type is a base type (like meters or grams)
 */
template <typename T>
struct is_base_type
{
    static constexpr auto value = std::is_same_v<T, typename T::type::base_type>;
};

/*!
 * Convenience value variant of is_base_type.
 */
template <typename T>
inline constexpr auto is_base_type_v = is_base_type<T>::value;

/*!
 * Check if a given unit type has a multiplier conversion value.
 */
aeon_define_member_value_check_trait(type_has_multiplier_value, double, multiplier);

/*!
 * Convenience value variant of type_has_multiplier_value.
 */
template <typename T>
inline constexpr auto type_has_multiplier_value_v = type_has_multiplier_value<T>::value;

/*!
 * Check if a given unit type has an offset conversion value.
 */
aeon_define_member_value_check_trait(type_has_offset_value, double, offset);

/*!
 * Convenience value variant of type_has_offset_value.
 */
template <typename T>
inline constexpr auto type_has_offset_value_v = type_has_offset_value<T>::value;

} // namespace aeon::math