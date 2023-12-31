// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/flags.h>
#include <gtest/gtest.h>

enum class test_flags : std::uint64_t
{
    flag_1 = 0x01,
    flag_2 = 0x02,
    flag_3 = 0x04,
    flag_4 = 0x08,
    flag_5 = 0x10
};

aeon_declare_flag_operators(test_flags)

enum class test_flags2 : std::uint8_t
{
    flag_1 = 0x01,
    flag_2 = 0x02,
    flag_3 = 0x04,
    flag_4 = 0x08,
    flag_5 = 0x10
};

aeon_declare_flag_operators(test_flags2)

TEST(test_flags, test_flags_create)
{
    const aeon::common::flags<test_flags> test;
    ASSERT_FALSE(test.is_set(test_flags::flag_1));
    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_FALSE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));
}

TEST(test_flags, test_flags_is_set)
{
    const aeon::common::flags<test_flags> test = test_flags::flag_1 | test_flags::flag_4;
    ASSERT_TRUE(test.is_set(test_flags::flag_1));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));

    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));
}

TEST(test_flags, test_flags_set_unset)
{
    aeon::common::flags<test_flags> test;

    test.set(test_flags::flag_1);

    ASSERT_TRUE(test.is_set(test_flags::flag_1));
    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_FALSE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));

    test.set(test_flags::flag_2);

    ASSERT_TRUE(test.is_set(test_flags::flag_1));
    ASSERT_TRUE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_FALSE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));

    test.set(test_flags::flag_4);

    ASSERT_TRUE(test.is_set(test_flags::flag_1));
    ASSERT_TRUE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));

    test.unset(test_flags::flag_1);

    ASSERT_FALSE(test.is_set(test_flags::flag_1));
    ASSERT_TRUE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));

    test.unset(test_flags::flag_2);

    ASSERT_FALSE(test.is_set(test_flags::flag_1));
    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));
}

TEST(test_flags, test_flags_operators)
{
    aeon::common::flags test = test_flags::flag_1 | test_flags::flag_4;

    test |= test_flags::flag_5;
    test ^= test_flags::flag_1;

    ASSERT_FALSE(test.is_set(test_flags::flag_1));
    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_TRUE(test.is_set(test_flags::flag_5));

    test ^= test_flags::flag_1;

    ASSERT_TRUE(test.is_set(test_flags::flag_1));
    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_TRUE(test.is_set(test_flags::flag_5));
}

TEST(test_flags, test_flags_operators_other_type)
{
    aeon::common::flags test = test_flags2::flag_1 | test_flags2::flag_4;

    EXPECT_EQ(sizeof(test), sizeof(std::uint8_t));

    test |= test_flags2::flag_5;
    test ^= test_flags2::flag_1;

    ASSERT_FALSE(test.is_set(test_flags2::flag_1));
    ASSERT_FALSE(test.is_set(test_flags2::flag_2));
    ASSERT_TRUE(test.is_set(test_flags2::flag_4));
    ASSERT_FALSE(test.is_set(test_flags2::flag_3));
    ASSERT_TRUE(test.is_set(test_flags2::flag_5));

    test ^= test_flags2::flag_1;

    ASSERT_TRUE(test.is_set(test_flags2::flag_1));
    ASSERT_FALSE(test.is_set(test_flags2::flag_2));
    ASSERT_TRUE(test.is_set(test_flags2::flag_4));
    ASSERT_FALSE(test.is_set(test_flags2::flag_3));
    ASSERT_TRUE(test.is_set(test_flags2::flag_5));
}