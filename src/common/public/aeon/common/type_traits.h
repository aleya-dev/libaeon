// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <cstdint>
#include <vector>
#include <atomic>

namespace aeon::Common::TypeTraits
{

namespace Internal
{

template <typename T>
struct EmptyBase
{
};

} // namespace internal

/*!
 * Get the amount of arguments in a function signature type.
 */
template <typename ReturnTypeT>
struct FunctionSignatureArgumentCount;

template <typename ReturnTypeT, typename... ArgsT>
struct FunctionSignatureArgumentCount<ReturnTypeT(ArgsT...)>
{
    static constexpr auto Value = sizeof...(ArgsT);
};

/*!
 * Derive from another class/struct optionally based on a given condition.
 * If the condition is false, a dummy inheritance will take place instead.
 */
template <bool Condition, typename T>
using OptionalBase = std::conditional_t<Condition, T, Internal::EmptyBase<T>>;

/*!
 * Get a representing integer type based on given number of bits
 */
template <unsigned int Bits>
struct IntegerTypeFromBits;

template <>
struct IntegerTypeFromBits<8>
{
    using SignedT = std::int8_t;
    using UnsignedT = std::uint8_t;
};

template <>
struct IntegerTypeFromBits<16>
{
    using SignedT = std::int16_t;
    using UnsignedT = std::uint16_t;
};

template <>
struct IntegerTypeFromBits<32>
{
    using SignedT = std::int32_t;
    using UnsignedT = std::uint32_t;
};

template <>
struct IntegerTypeFromBits<64>
{
    using SignedT = std::int64_t;
    using UnsignedT = std::uint64_t;
};

template <typename>
struct IsStdVector : std::false_type
{
};

template <typename T, typename A>
struct IsStdVector<std::vector<T, A>> : std::true_type
{
};

/*!
 * Check if a given type is an std::vector
 */
template <typename T>
static constexpr auto IsStdVectorV = IsStdVector<T>::value;

template <typename>
struct IsAtomic : std::false_type
{
};

template <typename T>
struct IsAtomic<std::atomic<T>> : std::true_type
{
};

/*!
 * Check if a given type is an std::atomic
 */
template <typename T>
static constexpr auto IsAtomicV = IsAtomic<T>::value;

/*!
 * Variadic version of is_same_v
 */
template <class T, class... U>
static constexpr auto IsAnySameV = (std::is_same_v<T, U> || ...);

/*!
 * Change one type into another while preserving const
 */
template <typename T, typename U>
struct PreserveConst
{
    using Type = std::conditional_t<std::is_const_v<std::remove_pointer_t<T>>, const U, U>;
};

/*!
 * Change one type into another while preserving const
 */
template <typename T, typename U>
using PreserveConstT = typename PreserveConst<T, U>::Type;

/*!
 * Change one type into another while preserving volatile
 */
template <typename T, typename U>
struct PreserveVolatile
{
    using Type = std::conditional_t<std::is_volatile_v<std::remove_pointer_t<T>>, volatile U, U>;
};

/*!
 * Change one type into another while preserving volatile
 */
template <typename T, typename U>
using PreserveVolatileT = typename PreserveVolatile<T, U>::Type;

/*!
 * Change one type into another while preserving const and volatile
 */
template <typename T, typename U>
struct PreserveCv
{
    using Type = PreserveConstT<T, PreserveVolatileT<T, U>>;
};

/*!
 * Change one type into another while preserving const and volatile
 */
template <typename T, typename U>
using PreserveCvt = typename PreserveCv<T, U>::Type;

/*!
 * Check if the given type is convertible to any integer
 */
template <typename T>
struct IsConvertibleToIntegral
{
    static constexpr auto Value = std::is_convertible_v<T, std::int8_t> || std::is_convertible_v<T, std::uint8_t> ||
                                  std::is_convertible_v<T, std::int16_t> || std::is_convertible_v<T, std::uint16_t> ||
                                  std::is_convertible_v<T, std::int32_t> || std::is_convertible_v<T, std::uint32_t> ||
                                  std::is_convertible_v<T, std::int64_t> || std::is_convertible_v<T, std::uint64_t>;
};

/*!
 * Check if the given type is convertible to any integer
 */
template <typename T>
static constexpr auto IsConvertibleToIntegralV = IsConvertibleToIntegral<T>::Value;

/*!
 * Check if the given type is convertible to a floating point value
 */
template <typename T>
struct IsConvertibleToFloatingPoint
{
    static constexpr auto Value = std::is_convertible_v<T, float> || std::is_convertible_v<T, double>;
};

/*!
 * Check if the given type is convertible to a floating point value
 */
template <typename T>
static constexpr auto IsConvertibleToFloatingPointV = IsConvertibleToFloatingPoint<T>::Value;

/*!
 * Check if the given type is convertible to any number
 */
template <typename T>
struct IsConvertibleToArithmetic
{
    static constexpr auto Value = IsConvertibleToIntegralV<T> || IsConvertibleToFloatingPointV<T>;
};

/*!
 * Check if the given type is convertible to any number
 */
template <typename T>
static constexpr auto IsConvertibleToArithmeticV = IsConvertibleToArithmetic<T>::Value;

} // namespace aeon::Common::type_traits
