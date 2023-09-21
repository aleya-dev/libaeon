// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/uuid.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_uuid, test_uuid_default_nil)
{
    Common::Uuid Uuid;
    ASSERT_TRUE(Uuid.IsNil());
}

TEST(test_uuid, test_uuid_is_nil)
{
    Common::Uuid Uuid;
    ASSERT_TRUE(Uuid.IsNil());
    ASSERT_TRUE(Uuid == false);

    Uuid.Data[0] = 1;
    ASSERT_FALSE(Uuid.IsNil());
    ASSERT_FALSE(Uuid == false);

    Uuid.Data[0] = 0;
    ASSERT_TRUE(Uuid.IsNil());
    ASSERT_TRUE(Uuid == false);
}

TEST(test_uuid, test_uuid_create_nil_is_nil)
{
    auto Uuid = Common::Uuid::Nil();
    Common::Uuid uuid2;
    ASSERT_TRUE(Uuid.IsNil());
    ASSERT_EQ(Uuid, uuid2);

    ASSERT_TRUE(Uuid == false);
    ASSERT_FALSE(Uuid != false);
}

TEST(test_uuid, test_uuid_random)
{
    auto Uuid = Common::Uuid::Generate();
    ASSERT_FALSE(Uuid.IsNil());

    for (int i = 0; i < 100; ++i)
    {
        auto uuid2 = Common::Uuid::Generate();
        ASSERT_NE(Uuid, uuid2);
    }
}

TEST(test_uuid, test_uuid_nil_string)
{
    ASSERT_TRUE(Common::Uuid::Parse("00000000-0000-0000-0000-000000000000").IsNil());
    ASSERT_TRUE(Common::Uuid::Parse("{00000000-0000-0000-0000-000000000000}").IsNil());
    ASSERT_TRUE(Common::Uuid::Parse("00000000000000000000000000000000").IsNil());
    ASSERT_TRUE(Common::Uuid::Parse("{00000000000000000000000000000000}").IsNil());
    ASSERT_ANY_THROW(const auto result = Common::Uuid::Parse("0"); (void)result;);
}

TEST(test_uuid, test_uuid_from_and_to_string)
{
    auto str = "00000000-0000-0000-0000-000000000000";
    auto Uuid = Common::Uuid::Parse("00000000-0000-0000-0000-000000000000");
    ASSERT_EQ(str, Uuid.Str());
}

TEST(test_uuid, test_uuid_from_and_to_string_random)
{
    for (int i = 0; i < 100; ++i)
    {
        auto Uuid = Common::Uuid::Generate();
        auto str = Uuid.Str();

        auto uuid2 = Common::Uuid::Parse(str);

        ASSERT_EQ(Uuid, uuid2);
        ASSERT_EQ(str, uuid2.Str());
    }
}
