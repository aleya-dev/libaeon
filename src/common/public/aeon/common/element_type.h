// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/assert.h>
#include <cstdint>
#include <cstddef>

namespace aeon::Common
{

enum class ElementTypeName
{
    U8,
    S8,
    U16,
    S16,
    U32,
    S32,
    U64,
    S64,
    F32,
    F64,
    Undefined,
};

template <typename T>
struct ElementTypeNameTrait final
{
};

#define CreateDataTypeTrait(type, value)                                                                            \
    template <>                                                                                                        \
    struct ElementTypeNameTrait<type> final                                                                            \
    {                                                                                                                  \
        static constexpr auto name = value;                                                                            \
    }

CreateDataTypeTrait(std::uint8_t, ElementTypeName::U8);
CreateDataTypeTrait(std::int8_t, ElementTypeName::S8);
CreateDataTypeTrait(std::uint16_t, ElementTypeName::U16);
CreateDataTypeTrait(std::int16_t, ElementTypeName::S16);
CreateDataTypeTrait(std::uint32_t, ElementTypeName::U32);
CreateDataTypeTrait(std::int32_t, ElementTypeName::S32);
CreateDataTypeTrait(std::uint64_t, ElementTypeName::U64);
CreateDataTypeTrait(std::int64_t, ElementTypeName::S64);
CreateDataTypeTrait(float, ElementTypeName::F32);
CreateDataTypeTrait(double, ElementTypeName::F64);

template <typename T, std::size_t CountT, std::size_t StrideT = sizeof(T) * CountT,
          std::size_t ComponentSizeT = sizeof(T), std::size_t FullSizeT = sizeof(T) * CountT>
struct ElementTypeInfo
{
    static constexpr auto Name = ElementTypeNameTrait<T>::name;
    static constexpr auto ComponentSize = ComponentSizeT;
    static constexpr auto Count = CountT;
    static constexpr auto Size = FullSizeT;
    static constexpr auto Stride = StrideT;
};

struct ElementType final
{
    constexpr ElementType() noexcept
        : Name{ElementTypeName::Undefined}
        , ComponentSize{0ull}
        , Count{0ull}
        , Size{0ull}
        , Stride{0ull}
    {
    }

    template <typename T, std::size_t CountT, std::size_t StrideT, std::size_t ComponentSizeT,
              std::size_t FullSizeT>
    constexpr ElementType(ElementTypeInfo<T, CountT, StrideT, ComponentSizeT, FullSizeT> info) noexcept
        : Name{info.Name}
        , ComponentSize{info.ComponentSize}
        , Count{info.Count}
        , Size{info.Size}
        , Stride{info.Stride}
    {
    }

    template <typename T, std::size_t CountT, std::size_t StrideT, std::size_t ComponentSizeT,
              std::size_t FullSizeT>
    constexpr auto operator=(ElementTypeInfo<T, CountT, StrideT, ComponentSizeT, FullSizeT> info) noexcept
        -> ElementType &
    {
        Name = info.Name;
        ComponentSize = info.ComponentSize;
        Count = info.Count;
        Size = info.Size;
        Stride = info.Stride;
        return *this;
    }

    /*!
     * The data is either compressed, or laid out in a way that a typical element size and stride don't make sense.
     */
    [[nodiscard]] auto IsUndefined() const noexcept
    {
        return Name == ElementTypeName::Undefined && ComponentSize == 0 && Count == 0 && Size == 0 && Stride == 0;
    }

    [[nodiscard]] auto Valid() const noexcept
    {
        return (Name != ElementTypeName::Undefined && ComponentSize > 0 && Count > 0 && Size > 0 && Stride > 0) ||
               IsUndefined();
    }

    /*!
     * Check if the component is continuous (stride == size).
     * \return True if the component is continuous
     */
    [[nodiscard]] auto Continuous() const noexcept
    {
        return Stride == Size;
    }

    ElementTypeName Name;
    std::size_t ComponentSize;
    std::size_t Count;
    std::size_t Size;
    std::size_t Stride;

    static constexpr auto Undefined =
        ElementTypeInfo<std::uint8_t, 0ull, 0ull, 0ull,
                        0ull>{}; // The data is either compressed, or laid out in a way that a
                                 // typical element size and stride don't make sense.

    static constexpr auto U8_1 = ElementTypeInfo<std::uint8_t, 1ull>{}; // 1 element of uint8_t
    static constexpr auto U8_2 = ElementTypeInfo<std::uint8_t, 2ull>{}; // 2 elements of uint8_t
    static constexpr auto U8_3 = ElementTypeInfo<std::uint8_t, 3ull>{}; // 3 elements of uint8_t
    static constexpr auto U8_4 = ElementTypeInfo<std::uint8_t, 4ull>{}; // 4 elements of uint8_t

    static constexpr auto U8_1_Stride_4 =
        ElementTypeInfo<std::uint8_t, 1ull, 4ull * sizeof(std::uint8_t)>{}; // 1 element of uint8_t, with a stride of 4

    /*!
     * 1 element of uint8_t, with a stride of 4
     * This can be used for example with an RGB image that has a stride of 4 bytes.
     */
    static constexpr auto U8_3_Stride_4 = ElementTypeInfo<std::uint8_t, 3ull, 4ull>{};

    static constexpr auto S8_1 = ElementTypeInfo<std::int8_t, 1ull>{}; // 1 element of int8_t
    static constexpr auto S8_2 = ElementTypeInfo<std::int8_t, 2ull>{}; // 2 elements of int8_t
    static constexpr auto S8_3 = ElementTypeInfo<std::int8_t, 3ull>{}; // 3 elements of int8_t
    static constexpr auto S8_4 = ElementTypeInfo<std::int8_t, 4ull>{}; // 4 elements of int8_t

    static constexpr auto S8_1_Stride_4 =
        ElementTypeInfo<std::int8_t, 1ull, 4ull>{}; // 1 element of int8_t, with a stride of 4
    static constexpr auto S8_3_Stride_4 =
        ElementTypeInfo<std::int8_t, 3ull, 4ull>{}; // 3 elements of uint8_t, with a stride of 4

    static constexpr auto U16_1 = ElementTypeInfo<std::uint16_t, 1ull>{}; // 1 element of uint16_t

    static constexpr auto U16_1_Stride_4 =
        ElementTypeInfo<std::uint16_t, 1ull, 4ull>{}; // 1 element of uint16_t, with a stride of 4

    static constexpr auto U16_2 = ElementTypeInfo<std::uint16_t, 2ull>{}; // 2 elements of uint16_t
    static constexpr auto U16_3 = ElementTypeInfo<std::uint16_t, 3ull>{}; // 3 elements of uint16_t
    static constexpr auto U16_4 = ElementTypeInfo<std::uint16_t, 4ull>{}; // 4 elements of uint16_t

    static constexpr auto S16_1 = ElementTypeInfo<std::int16_t, 1ull>{}; // 1 element of int16_t
    static constexpr auto S16_2 = ElementTypeInfo<std::int16_t, 2ull>{}; // 2 elements of int16_t
    static constexpr auto S16_3 = ElementTypeInfo<std::int16_t, 3ull>{}; // 3 elements of int16_t
    static constexpr auto S16_4 = ElementTypeInfo<std::int16_t, 4ull>{}; // 4 elements of int16_t

    static constexpr auto S16_1_Stride_4 =
        ElementTypeInfo<std::int16_t, 1ull, 4ull>{}; // 1 element of int16_t, with a stride of 4

    static constexpr auto U32_1 = ElementTypeInfo<std::uint32_t, 1ull>{}; // 1 element of uint32_t
    static constexpr auto U32_2 = ElementTypeInfo<std::uint32_t, 2ull>{}; // 2 elements of uint32_t
    static constexpr auto U32_3 = ElementTypeInfo<std::uint32_t, 3ull>{}; // 3 elements of uint32_t
    static constexpr auto U32_4 = ElementTypeInfo<std::uint32_t, 4ull>{}; // 4 elements of uint32_t

    static constexpr auto U32_1_stride_8 =
        ElementTypeInfo<std::uint32_t, 1ull, 8ull>{}; // 1 element of uint32_t, with a stride of 8

    static constexpr auto S32_1 = ElementTypeInfo<std::int32_t, 1ull>{}; // 1 element of int32_t
    static constexpr auto S32_2 = ElementTypeInfo<std::int32_t, 2ull>{}; // 2 elements of int32_t
    static constexpr auto S32_3 = ElementTypeInfo<std::int32_t, 3ull>{}; // 3 elements of int32_t
    static constexpr auto S32_4 = ElementTypeInfo<std::int32_t, 4ull>{}; // 4 elements of int32_t

    static constexpr auto S32_1_Stride_8 =
        ElementTypeInfo<std::int32_t, 1ull, 8ull>{}; // 1 element of int32_t, with a stride of 8

    static constexpr auto U64_1 = ElementTypeInfo<std::uint64_t, 1ull>{}; // 1 element of uint64_t
    static constexpr auto U64_2 = ElementTypeInfo<std::uint64_t, 2ull>{}; // 2 elements of uint64_t
    static constexpr auto U64_3 = ElementTypeInfo<std::uint64_t, 3ull>{}; // 3 elements of uint64_t
    static constexpr auto U64_4 = ElementTypeInfo<std::uint64_t, 4ull>{}; // 4 elements of uint64_t

    static constexpr auto S64_1 = ElementTypeInfo<std::int64_t, 1ull>{}; // 1 element of int64_t
    static constexpr auto S64_2 = ElementTypeInfo<std::int64_t, 2ull>{}; // 2 elements of int64_t
    static constexpr auto S64_3 = ElementTypeInfo<std::int64_t, 3ull>{}; // 3 elements of int64_t
    static constexpr auto S64_4 = ElementTypeInfo<std::int64_t, 4ull>{}; // 4 elements of int64_t

    static constexpr auto F32_1 = ElementTypeInfo<float, 1ull>{}; // 1 element of float
    static constexpr auto F32_2 = ElementTypeInfo<float, 2ull>{}; // 2 elements of float
    static constexpr auto F32_3 = ElementTypeInfo<float, 3ull>{}; // 3 elements of float
    static constexpr auto F32_4 = ElementTypeInfo<float, 4ull>{}; // 4 elements of float

    static constexpr auto F32_1_Stride_8 =
        ElementTypeInfo<float, 1ull, 8ull>{}; // 1 element of float, with a stride of 8

    static constexpr auto F64_1 = ElementTypeInfo<double, 1ull>{}; // 1 element of double
    static constexpr auto F64_2 = ElementTypeInfo<double, 2ull>{}; // 2 elements of double
    static constexpr auto F64_3 = ElementTypeInfo<double, 3ull>{}; // 3 elements of double
    static constexpr auto F64_4 = ElementTypeInfo<double, 4ull>{}; // 4 elements of double
};

inline constexpr auto operator==(const ElementType &lhs, const ElementType &rhs) noexcept -> bool
{
    return lhs.Name == rhs.Name && lhs.ComponentSize == rhs.ComponentSize && lhs.Count == rhs.Count &&
           lhs.Size == rhs.Size && lhs.Stride == rhs.Stride;
}

inline constexpr auto operator!=(const ElementType &lhs, const ElementType &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

/*!
 * Calculate the offset of an element within an array of bytes
 * \param[in] type - An element type
 * \param[in] stride - The stride in bytes (Typically width * type.stride)
 * \param[in] x - The x position
 * \param[in] y - The y position
 * \return The offset in bytes that an element would be at
 */
[[nodiscard]] inline constexpr auto OffsetOf(const ElementType &type, const std::size_t stride, const std::int64_t x,
                                              const std::int64_t y) noexcept -> std::size_t
{
    AeonAssert(x >= 0, "X must be >= 0");
    AeonAssert(y >= 0, "Y must be >= 0");
    AeonAssert(stride > 0, "stride must be >= 0");

    return stride * y + type.Stride * x;
}

} // namespace aeon::Common
