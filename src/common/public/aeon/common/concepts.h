// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/type_traits.h>
#include <concepts>
#include <type_traits>
#include <tuple>

namespace aeon::Common::Concepts
{

/*!
 * Given type must be Arithmetic (int, float, etc.)
 */
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

/*!
 * Given type must be Arithmetic (int, float, etc.), or convertible to one
 */
template <typename T>
concept ArithmeticConvertible =
    (std::is_arithmetic_v<T> || TypeTraits::IsConvertibleToArithmeticV<T>)&&!std::is_enum_v<T>;

/*!
 * The given type must be an enum
 */
template <typename T>
concept Enumerable = std::is_enum_v<T>;

/*!
 * The given type must be an enum, with a signed underlying type (such as int)
 */
template <typename T>
concept SignedEnumerable = Enumerable<T> && std::is_signed_v<std::underlying_type_t<T>>;

/*!
 * The given type must be an enum, with an unsigned underlying type (such as unsigned int)
 */
template <typename T>
concept UnsignedEnumerable = Enumerable<T> && std::is_unsigned_v<std::underlying_type_t<T>>;

/*!
 * The given type must be integral or std::atomic integral
 */
template <typename T>
concept IntegralOrAtomicIntegral =
    std::integral<T> || (TypeTraits::IsAtomicV<T> && std::integral<typename T::value_type>);

/*!
 * Helper struct to be used with BraceConstructible. Can use used to check if a given type is brace constructible with
 * a certain amount of types; but the type itself doesn't matter.
 */
struct AnyConvertible
{
    template <class T>
    constexpr operator T();
};

/*!
 * The given type T must be brace constructible with the given argument types
 */
template <typename T, typename... ArgsT>
concept BraceConstructible = requires { T{std::declval<ArgsT>()...}; };

/*!
 * The given type T must be brace constructible with the given argument types
 */
template <BraceConstructible T, typename... ArgsT>
inline constexpr bool IsBraceConstructibleV = BraceConstructible<T, ArgsT...>;

/*!
 * Check if an index is valid for the given tuple.
 */
template <typename T, std::size_t N>
constexpr bool IsTupleElement = requires(T t) {
    typename std::tuple_element_t<N - 1, std::remove_const_t<T>>;
    {
        get<N - 1>(t)
    } -> std::convertible_to<std::tuple_element_t<N - 1, T> &>;
} && IsTupleElement<T, N - 1>;

/*!
 * Check if an index is valid for the given tuple.
 */
template <typename T>
constexpr bool IsTupleElement<T, 0> = true;

/*!
 * The given type T must be a tuple-like type. A type is tuple-like when the tuple functions apply to it: std::get,
 * std::tuple_element and std::tuple_size.
 */
template <typename T>
concept TupleLike = !std::is_reference_v<T> && requires {
    typename std::tuple_size<T>::type;
    requires std::same_as<decltype(std::tuple_size_v<T>), size_t>;
} && IsTupleElement<T, std::tuple_size_v<T>>;

} // namespace aeon::Common::concepts
