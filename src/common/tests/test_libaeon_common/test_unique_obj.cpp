// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/unique_obj.h>
#include <gtest/gtest.h>
#include <vector>
#include <type_traits>

using namespace aeon;

TEST(test_unique_obj, test_default_create)
{
    Common::UniqueObj obj = 3;
    Common::UniqueObj obj2 = std::vector{1, 2, 3, 4};

    EXPECT_FALSE(std::is_copy_assignable_v<decltype(obj)>);
    EXPECT_FALSE(std::is_copy_constructible_v<decltype(obj)>);

    EXPECT_FALSE(std::is_copy_assignable_v<decltype(obj2)>);
    EXPECT_FALSE(std::is_copy_constructible_v<decltype(obj2)>);

    EXPECT_TRUE(std::is_move_assignable_v<decltype(obj)>);
    EXPECT_TRUE(std::is_move_constructible_v<decltype(obj)>);

    EXPECT_TRUE(std::is_move_assignable_v<decltype(obj2)>);
    EXPECT_TRUE(std::is_move_constructible_v<decltype(obj2)>);
}

TEST(test_unique_obj, test_move)
{
    Common::UniqueObj obj = std::vector{1, 2, 3, 4};
    const auto obj2 = std::move(obj);
    EXPECT_EQ(4, std::size(*obj2));
}

TEST(test_unique_obj, test_get)
{
    Common::UniqueObj obj = std::vector{1, 2, 3, 4};
    EXPECT_EQ(4, std::size(obj.Get()));
}

TEST(test_unique_obj, test_release)
{
    Common::UniqueObj obj = std::vector{1, 2, 3, 4};
    EXPECT_EQ(4, std::size(*obj));

    auto vector = obj.Release();
    EXPECT_EQ(4, std::size(vector));

    Common::UniqueObj obj2 = std::move(vector);
    EXPECT_EQ(4, std::size(*obj2));
}
