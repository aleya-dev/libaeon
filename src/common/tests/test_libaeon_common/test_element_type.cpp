// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/element_type.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_element_type, test_element_type_names)
{
    EXPECT_EQ(Common::ElementTypeName::S8, Common::ElementType::S8_1.Name);
    EXPECT_EQ(Common::ElementTypeName::S8, Common::ElementType::S8_2.Name);
    EXPECT_EQ(Common::ElementTypeName::S8, Common::ElementType::S8_3.Name);
    EXPECT_EQ(Common::ElementTypeName::S8, Common::ElementType::S8_4.Name);
    EXPECT_EQ(Common::ElementTypeName::U8, Common::ElementType::U8_1.Name);
    EXPECT_EQ(Common::ElementTypeName::U8, Common::ElementType::U8_2.Name);
    EXPECT_EQ(Common::ElementTypeName::U8, Common::ElementType::U8_3.Name);
    EXPECT_EQ(Common::ElementTypeName::U8, Common::ElementType::U8_4.Name);

    EXPECT_EQ(Common::ElementTypeName::S16, Common::ElementType::S16_1.Name);
    EXPECT_EQ(Common::ElementTypeName::S16, Common::ElementType::S16_2.Name);
    EXPECT_EQ(Common::ElementTypeName::S16, Common::ElementType::S16_3.Name);
    EXPECT_EQ(Common::ElementTypeName::S16, Common::ElementType::S16_4.Name);
    EXPECT_EQ(Common::ElementTypeName::U16, Common::ElementType::U16_1.Name);
    EXPECT_EQ(Common::ElementTypeName::U16, Common::ElementType::U16_2.Name);
    EXPECT_EQ(Common::ElementTypeName::U16, Common::ElementType::U16_3.Name);
    EXPECT_EQ(Common::ElementTypeName::U16, Common::ElementType::U16_4.Name);

    EXPECT_EQ(Common::ElementTypeName::S32, Common::ElementType::S32_1.Name);
    EXPECT_EQ(Common::ElementTypeName::S32, Common::ElementType::S32_2.Name);
    EXPECT_EQ(Common::ElementTypeName::S32, Common::ElementType::S32_3.Name);
    EXPECT_EQ(Common::ElementTypeName::S32, Common::ElementType::S32_4.Name);
    EXPECT_EQ(Common::ElementTypeName::U32, Common::ElementType::U32_1.Name);
    EXPECT_EQ(Common::ElementTypeName::U32, Common::ElementType::U32_2.Name);
    EXPECT_EQ(Common::ElementTypeName::U32, Common::ElementType::U32_3.Name);
    EXPECT_EQ(Common::ElementTypeName::U32, Common::ElementType::U32_4.Name);

    EXPECT_EQ(Common::ElementTypeName::S64, Common::ElementType::S64_1.Name);
    EXPECT_EQ(Common::ElementTypeName::S64, Common::ElementType::S64_2.Name);
    EXPECT_EQ(Common::ElementTypeName::S64, Common::ElementType::S64_3.Name);
    EXPECT_EQ(Common::ElementTypeName::S64, Common::ElementType::S64_4.Name);
    EXPECT_EQ(Common::ElementTypeName::U64, Common::ElementType::U64_1.Name);
    EXPECT_EQ(Common::ElementTypeName::U64, Common::ElementType::U64_2.Name);
    EXPECT_EQ(Common::ElementTypeName::U64, Common::ElementType::U64_3.Name);
    EXPECT_EQ(Common::ElementTypeName::U64, Common::ElementType::U64_4.Name);

    EXPECT_EQ(Common::ElementTypeName::F32, Common::ElementType::F32_1.Name);
    EXPECT_EQ(Common::ElementTypeName::F32, Common::ElementType::F32_2.Name);
    EXPECT_EQ(Common::ElementTypeName::F32, Common::ElementType::F32_3.Name);
    EXPECT_EQ(Common::ElementTypeName::F32, Common::ElementType::F32_4.Name);

    EXPECT_EQ(Common::ElementTypeName::F64, Common::ElementType::F64_1.Name);
    EXPECT_EQ(Common::ElementTypeName::F64, Common::ElementType::F64_2.Name);
    EXPECT_EQ(Common::ElementTypeName::F64, Common::ElementType::F64_3.Name);
    EXPECT_EQ(Common::ElementTypeName::F64, Common::ElementType::F64_4.Name);
}

TEST(test_element_type, test_element_type_sizes)
{
    EXPECT_EQ(sizeof(std::int8_t) * 1, Common::ElementType::S8_1.Size);
    EXPECT_EQ(sizeof(std::int8_t) * 2, Common::ElementType::S8_2.Size);
    EXPECT_EQ(sizeof(std::int8_t) * 3, Common::ElementType::S8_3.Size);
    EXPECT_EQ(sizeof(std::int8_t) * 4, Common::ElementType::S8_4.Size);
    EXPECT_EQ(sizeof(std::uint8_t) * 1, Common::ElementType::U8_1.Size);
    EXPECT_EQ(sizeof(std::uint8_t) * 2, Common::ElementType::U8_2.Size);
    EXPECT_EQ(sizeof(std::uint8_t) * 3, Common::ElementType::U8_3.Size);
    EXPECT_EQ(sizeof(std::uint8_t) * 4, Common::ElementType::U8_4.Size);

    EXPECT_EQ(sizeof(std::int16_t) * 1, Common::ElementType::S16_1.Size);
    EXPECT_EQ(sizeof(std::int16_t) * 2, Common::ElementType::S16_2.Size);
    EXPECT_EQ(sizeof(std::int16_t) * 3, Common::ElementType::S16_3.Size);
    EXPECT_EQ(sizeof(std::int16_t) * 4, Common::ElementType::S16_4.Size);
    EXPECT_EQ(sizeof(std::uint16_t) * 1, Common::ElementType::U16_1.Size);
    EXPECT_EQ(sizeof(std::uint16_t) * 2, Common::ElementType::U16_2.Size);
    EXPECT_EQ(sizeof(std::uint16_t) * 3, Common::ElementType::U16_3.Size);
    EXPECT_EQ(sizeof(std::uint16_t) * 4, Common::ElementType::U16_4.Size);

    EXPECT_EQ(sizeof(std::int32_t) * 1, Common::ElementType::S32_1.Size);
    EXPECT_EQ(sizeof(std::int32_t) * 2, Common::ElementType::S32_2.Size);
    EXPECT_EQ(sizeof(std::int32_t) * 3, Common::ElementType::S32_3.Size);
    EXPECT_EQ(sizeof(std::int32_t) * 4, Common::ElementType::S32_4.Size);
    EXPECT_EQ(sizeof(std::uint32_t) * 1, Common::ElementType::U32_1.Size);
    EXPECT_EQ(sizeof(std::uint32_t) * 2, Common::ElementType::U32_2.Size);
    EXPECT_EQ(sizeof(std::uint32_t) * 3, Common::ElementType::U32_3.Size);
    EXPECT_EQ(sizeof(std::uint32_t) * 4, Common::ElementType::U32_4.Size);

    EXPECT_EQ(sizeof(std::int64_t) * 1, Common::ElementType::S64_1.Size);
    EXPECT_EQ(sizeof(std::int64_t) * 2, Common::ElementType::S64_2.Size);
    EXPECT_EQ(sizeof(std::int64_t) * 3, Common::ElementType::S64_3.Size);
    EXPECT_EQ(sizeof(std::int64_t) * 4, Common::ElementType::S64_4.Size);
    EXPECT_EQ(sizeof(std::uint64_t) * 1, Common::ElementType::U64_1.Size);
    EXPECT_EQ(sizeof(std::uint64_t) * 2, Common::ElementType::U64_2.Size);
    EXPECT_EQ(sizeof(std::uint64_t) * 3, Common::ElementType::U64_3.Size);
    EXPECT_EQ(sizeof(std::uint64_t) * 4, Common::ElementType::U64_4.Size);

    EXPECT_EQ(sizeof(float) * 1, Common::ElementType::F32_1.Size);
    EXPECT_EQ(sizeof(float) * 2, Common::ElementType::F32_2.Size);
    EXPECT_EQ(sizeof(float) * 3, Common::ElementType::F32_3.Size);
    EXPECT_EQ(sizeof(float) * 4, Common::ElementType::F32_4.Size);

    EXPECT_EQ(sizeof(double) * 1, Common::ElementType::F64_1.Size);
    EXPECT_EQ(sizeof(double) * 2, Common::ElementType::F64_2.Size);
    EXPECT_EQ(sizeof(double) * 3, Common::ElementType::F64_3.Size);
    EXPECT_EQ(sizeof(double) * 4, Common::ElementType::F64_4.Size);

    EXPECT_EQ(sizeof(std::uint8_t), Common::ElementType::U8_1_Stride_4.Size);
    EXPECT_EQ(sizeof(std::uint16_t), Common::ElementType::U16_1_Stride_4.Size);
}

TEST(test_element_type, test_element_type_component_size)
{
    EXPECT_EQ(sizeof(std::int8_t), Common::ElementType::S8_1.ComponentSize);
    EXPECT_EQ(sizeof(std::int8_t), Common::ElementType::S8_2.ComponentSize);
    EXPECT_EQ(sizeof(std::int8_t), Common::ElementType::S8_3.ComponentSize);
    EXPECT_EQ(sizeof(std::int8_t), Common::ElementType::S8_4.ComponentSize);
    EXPECT_EQ(sizeof(std::uint8_t), Common::ElementType::U8_1.ComponentSize);
    EXPECT_EQ(sizeof(std::uint8_t), Common::ElementType::U8_2.ComponentSize);
    EXPECT_EQ(sizeof(std::uint8_t), Common::ElementType::U8_3.ComponentSize);
    EXPECT_EQ(sizeof(std::uint8_t), Common::ElementType::U8_4.ComponentSize);

    EXPECT_EQ(sizeof(std::int16_t), Common::ElementType::S16_1.ComponentSize);
    EXPECT_EQ(sizeof(std::int16_t), Common::ElementType::S16_2.ComponentSize);
    EXPECT_EQ(sizeof(std::int16_t), Common::ElementType::S16_3.ComponentSize);
    EXPECT_EQ(sizeof(std::int16_t), Common::ElementType::S16_4.ComponentSize);
    EXPECT_EQ(sizeof(std::uint16_t), Common::ElementType::U16_1.ComponentSize);
    EXPECT_EQ(sizeof(std::uint16_t), Common::ElementType::U16_2.ComponentSize);
    EXPECT_EQ(sizeof(std::uint16_t), Common::ElementType::U16_3.ComponentSize);
    EXPECT_EQ(sizeof(std::uint16_t), Common::ElementType::U16_4.ComponentSize);

    EXPECT_EQ(sizeof(std::int32_t), Common::ElementType::S32_1.ComponentSize);
    EXPECT_EQ(sizeof(std::int32_t), Common::ElementType::S32_2.ComponentSize);
    EXPECT_EQ(sizeof(std::int32_t), Common::ElementType::S32_3.ComponentSize);
    EXPECT_EQ(sizeof(std::int32_t), Common::ElementType::S32_4.ComponentSize);
    EXPECT_EQ(sizeof(std::uint32_t), Common::ElementType::U32_1.ComponentSize);
    EXPECT_EQ(sizeof(std::uint32_t), Common::ElementType::U32_2.ComponentSize);
    EXPECT_EQ(sizeof(std::uint32_t), Common::ElementType::U32_3.ComponentSize);
    EXPECT_EQ(sizeof(std::uint32_t), Common::ElementType::U32_4.ComponentSize);

    EXPECT_EQ(sizeof(std::int64_t), Common::ElementType::S64_1.ComponentSize);
    EXPECT_EQ(sizeof(std::int64_t), Common::ElementType::S64_2.ComponentSize);
    EXPECT_EQ(sizeof(std::int64_t), Common::ElementType::S64_3.ComponentSize);
    EXPECT_EQ(sizeof(std::int64_t), Common::ElementType::S64_4.ComponentSize);
    EXPECT_EQ(sizeof(std::uint64_t), Common::ElementType::U64_1.ComponentSize);
    EXPECT_EQ(sizeof(std::uint64_t), Common::ElementType::U64_2.ComponentSize);
    EXPECT_EQ(sizeof(std::uint64_t), Common::ElementType::U64_3.ComponentSize);
    EXPECT_EQ(sizeof(std::uint64_t), Common::ElementType::U64_4.ComponentSize);

    EXPECT_EQ(sizeof(float), Common::ElementType::F32_1.ComponentSize);
    EXPECT_EQ(sizeof(float), Common::ElementType::F32_2.ComponentSize);
    EXPECT_EQ(sizeof(float), Common::ElementType::F32_3.ComponentSize);
    EXPECT_EQ(sizeof(float), Common::ElementType::F32_4.ComponentSize);

    EXPECT_EQ(sizeof(double), Common::ElementType::F64_1.ComponentSize);
    EXPECT_EQ(sizeof(double), Common::ElementType::F64_2.ComponentSize);
    EXPECT_EQ(sizeof(double), Common::ElementType::F64_3.ComponentSize);
    EXPECT_EQ(sizeof(double), Common::ElementType::F64_4.ComponentSize);

    EXPECT_EQ(sizeof(std::uint8_t), Common::ElementType::U8_1_Stride_4.ComponentSize);
    EXPECT_EQ(sizeof(std::uint16_t), Common::ElementType::U16_1_Stride_4.ComponentSize);
}

TEST(test_element_type, test_element_type_strides)
{
    EXPECT_EQ(sizeof(std::int8_t) * 1, Common::ElementType::S8_1.Stride);
    EXPECT_EQ(sizeof(std::int8_t) * 2, Common::ElementType::S8_2.Stride);
    EXPECT_EQ(sizeof(std::int8_t) * 3, Common::ElementType::S8_3.Stride);
    EXPECT_EQ(sizeof(std::int8_t) * 4, Common::ElementType::S8_4.Stride);
    EXPECT_EQ(sizeof(std::uint8_t) * 1, Common::ElementType::U8_1.Stride);
    EXPECT_EQ(sizeof(std::uint8_t) * 2, Common::ElementType::U8_2.Stride);
    EXPECT_EQ(sizeof(std::uint8_t) * 3, Common::ElementType::U8_3.Stride);
    EXPECT_EQ(sizeof(std::uint8_t) * 4, Common::ElementType::U8_4.Stride);

    EXPECT_EQ(sizeof(std::int16_t) * 1, Common::ElementType::S16_1.Stride);
    EXPECT_EQ(sizeof(std::int16_t) * 2, Common::ElementType::S16_2.Stride);
    EXPECT_EQ(sizeof(std::int16_t) * 3, Common::ElementType::S16_3.Stride);
    EXPECT_EQ(sizeof(std::int16_t) * 4, Common::ElementType::S16_4.Stride);
    EXPECT_EQ(sizeof(std::uint16_t) * 1, Common::ElementType::U16_1.Stride);
    EXPECT_EQ(sizeof(std::uint16_t) * 2, Common::ElementType::U16_2.Stride);
    EXPECT_EQ(sizeof(std::uint16_t) * 3, Common::ElementType::U16_3.Stride);
    EXPECT_EQ(sizeof(std::uint16_t) * 4, Common::ElementType::U16_4.Stride);

    EXPECT_EQ(sizeof(std::int32_t) * 1, Common::ElementType::S32_1.Stride);
    EXPECT_EQ(sizeof(std::int32_t) * 2, Common::ElementType::S32_2.Stride);
    EXPECT_EQ(sizeof(std::int32_t) * 3, Common::ElementType::S32_3.Stride);
    EXPECT_EQ(sizeof(std::int32_t) * 4, Common::ElementType::S32_4.Stride);
    EXPECT_EQ(sizeof(std::uint32_t) * 1, Common::ElementType::U32_1.Stride);
    EXPECT_EQ(sizeof(std::uint32_t) * 2, Common::ElementType::U32_2.Stride);
    EXPECT_EQ(sizeof(std::uint32_t) * 3, Common::ElementType::U32_3.Stride);
    EXPECT_EQ(sizeof(std::uint32_t) * 4, Common::ElementType::U32_4.Stride);

    EXPECT_EQ(sizeof(std::int64_t) * 1, Common::ElementType::S64_1.Stride);
    EXPECT_EQ(sizeof(std::int64_t) * 2, Common::ElementType::S64_2.Stride);
    EXPECT_EQ(sizeof(std::int64_t) * 3, Common::ElementType::S64_3.Stride);
    EXPECT_EQ(sizeof(std::int64_t) * 4, Common::ElementType::S64_4.Stride);
    EXPECT_EQ(sizeof(std::uint64_t) * 1, Common::ElementType::U64_1.Stride);
    EXPECT_EQ(sizeof(std::uint64_t) * 2, Common::ElementType::U64_2.Stride);
    EXPECT_EQ(sizeof(std::uint64_t) * 3, Common::ElementType::U64_3.Stride);
    EXPECT_EQ(sizeof(std::uint64_t) * 4, Common::ElementType::U64_4.Stride);

    EXPECT_EQ(sizeof(float) * 1, Common::ElementType::F32_1.Stride);
    EXPECT_EQ(sizeof(float) * 2, Common::ElementType::F32_2.Stride);
    EXPECT_EQ(sizeof(float) * 3, Common::ElementType::F32_3.Stride);
    EXPECT_EQ(sizeof(float) * 4, Common::ElementType::F32_4.Stride);

    EXPECT_EQ(sizeof(double) * 1, Common::ElementType::F64_1.Stride);
    EXPECT_EQ(sizeof(double) * 2, Common::ElementType::F64_2.Stride);
    EXPECT_EQ(sizeof(double) * 3, Common::ElementType::F64_3.Stride);
    EXPECT_EQ(sizeof(double) * 4, Common::ElementType::F64_4.Stride);

    EXPECT_EQ(sizeof(std::uint8_t) * 4, Common::ElementType::U8_1_Stride_4.Stride);
    EXPECT_EQ(sizeof(std::uint8_t) * 4, Common::ElementType::U16_1_Stride_4.Stride);
}

TEST(test_element_type, test_element_type_ctor)
{
    const Common::ElementType t{Common::ElementType::F32_4};
    EXPECT_EQ(Common::ElementTypeName::F32, t.Name);
    EXPECT_EQ(4ull, t.Count);
    EXPECT_EQ(sizeof(float) * 4, t.Size);
}

TEST(test_element_type, test_element_type_assign)
{
    const Common::ElementType t = Common::ElementType::F32_4;
    EXPECT_EQ(Common::ElementTypeName::F32, t.Name);
    EXPECT_EQ(4ull, t.Count);
    EXPECT_EQ(sizeof(float) * 4, t.Size);
}

TEST(test_element_type, test_element_type_compare)
{
    const Common::ElementType t{Common::ElementType::F32_4};
    const Common::ElementType t2{Common::ElementType::F32_4};
    const Common::ElementType t3{Common::ElementType::F32_3};
    const Common::ElementType t4{Common::ElementType::U32_4};

    EXPECT_TRUE(t == t2);
    EXPECT_FALSE(t != t2);

    EXPECT_FALSE(t == t3);
    EXPECT_FALSE(t2 == t3);
    EXPECT_TRUE(t != t3);
    EXPECT_TRUE(t2 != t3);

    EXPECT_FALSE(t == t4);
    EXPECT_FALSE(t2 == t4);
    EXPECT_FALSE(t3 == t4);
    EXPECT_TRUE(t != t4);
    EXPECT_TRUE(t2 != t4);
    EXPECT_TRUE(t3 != t4);

    const Common::ElementType t5{Common::ElementType::U8_4};
    const Common::ElementType t6{Common::ElementType::U8_3_Stride_4};

    EXPECT_TRUE(t5 != t6);
    EXPECT_FALSE(t5 == t6);
    EXPECT_TRUE(t6 != t5);
    EXPECT_FALSE(t6 == t5);
}

TEST(test_element_type, test_element_type_copy)
{
    const Common::ElementType t{Common::ElementType::F32_4};
    const auto t2 = t;

    EXPECT_TRUE(t == t2);
    EXPECT_FALSE(t != t2);
}

TEST(test_element_type, test_element_offset_of)
{
    const Common::ElementType t{Common::ElementType::F32_4};
    const auto width = 4;
    const auto stride = t.Stride * width;

    EXPECT_EQ(0ull, Common::OffsetOf(t, stride, 0, 0));
    EXPECT_EQ(sizeof(float) * 4, Common::OffsetOf(t, stride, 1, 0));
    EXPECT_EQ(sizeof(float) * 8, Common::OffsetOf(t, stride, 2, 0));
    EXPECT_EQ(sizeof(float) * 12, Common::OffsetOf(t, stride, 3, 0));
    EXPECT_EQ(sizeof(float) * 16, Common::OffsetOf(t, stride, 0, 1));
}

TEST(test_element_type, test_element_offset_of_with_stride_element)
{
    const Common::ElementType t{Common::ElementType::U8_3_Stride_4};
    const auto width = 4ull;
    const auto stride = t.Stride * width;

    EXPECT_EQ(0ull, Common::OffsetOf(t, stride, 0, 0));
    EXPECT_EQ(4ull, Common::OffsetOf(t, stride, 1, 0));
    EXPECT_EQ(8ull, Common::OffsetOf(t, stride, 2, 0));
    EXPECT_EQ(12ull, Common::OffsetOf(t, stride, 3, 0));
    EXPECT_EQ(16ull, Common::OffsetOf(t, stride, 0, 1));
}
