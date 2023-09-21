// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/containers/unordered_flatmap.h>
#include <aeon/common/string.h>
#include <gtest/gtest.h>

using namespace aeon;

struct TestFixtureUnorderedFlatmapDefaultData : ::testing::Test
{
    TestFixtureUnorderedFlatmapDefaultData()
    {
        UnorderedFlatmap["One"] = 1;
        UnorderedFlatmap["Two"] = 2;
        UnorderedFlatmap["Three"] = 3;
        UnorderedFlatmap["Four"] = 4;
        UnorderedFlatmap["Five"] = 5;
    }

    void SetUp() override
    {
        ASSERT_EQ(5u, UnorderedFlatmap.Size());
    }

    Common::Containers::UnorderedFlatmap<Common::String, int> UnorderedFlatmap;
};

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_at)
{
    const auto atOne = UnorderedFlatmap.At("One");
    const auto atTwo = UnorderedFlatmap.At("Two");
    const auto atThree = UnorderedFlatmap.At("Three");
    const auto atFour = UnorderedFlatmap.At("Four");
    const auto atFive = UnorderedFlatmap.At("Five");

    ASSERT_EQ(1, atOne);
    ASSERT_EQ(2, atTwo);
    ASSERT_EQ(3, atThree);
    ASSERT_EQ(4, atFour);
    ASSERT_EQ(5, atFive);
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_index_operator)
{
    const auto atOne = UnorderedFlatmap["One"];
    const auto atTwo = UnorderedFlatmap["Two"];
    const auto atThree = UnorderedFlatmap["Three"];
    const auto atFour = UnorderedFlatmap["Four"];
    const auto atFive = UnorderedFlatmap["Five"];

    ASSERT_EQ(1, atOne);
    ASSERT_EQ(2, atTwo);
    ASSERT_EQ(3, atThree);
    ASSERT_EQ(4, atFour);
    ASSERT_EQ(5, atFive);
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_index_operator_overwrite)
{
    UnorderedFlatmap["Three"] = 42;
    UnorderedFlatmap["Four"] = 32;

    const auto atOne = UnorderedFlatmap["One"];
    const auto atTwo = UnorderedFlatmap["Two"];
    const auto atThree = UnorderedFlatmap["Three"];
    const auto atFour = UnorderedFlatmap["Four"];
    const auto atFive = UnorderedFlatmap["Five"];

    ASSERT_EQ(1, atOne);
    ASSERT_EQ(2, atTwo);
    ASSERT_EQ(42, atThree);
    ASSERT_EQ(32, atFour);
    ASSERT_EQ(5, atFive);

    ASSERT_EQ(5u, UnorderedFlatmap.Size());
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_push_back)
{
    UnorderedFlatmap.PushBack("Three", 15);
    auto atThree = UnorderedFlatmap["Three"];
    ASSERT_EQ(3, atThree);
    UnorderedFlatmap.Insert("Three", 15);
    atThree = UnorderedFlatmap["Three"];
    ASSERT_EQ(15, atThree);
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_index_operator_default)
{
    const auto cantFind = UnorderedFlatmap["Something! 123"];

    ASSERT_EQ(0, cantFind);
    ASSERT_EQ(6u, UnorderedFlatmap.Size());
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_empty_and_clear)
{
    ASSERT_FALSE(UnorderedFlatmap.Empty());
    UnorderedFlatmap.Clear();
    ASSERT_TRUE(UnorderedFlatmap.Empty());
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_find)
{
    const auto result = UnorderedFlatmap.Find("Three");

    ASSERT_EQ("Three", result->first);
    ASSERT_EQ(3, result->second);
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_not_found)
{
    const auto result = UnorderedFlatmap.Find("Something! 123");

    ASSERT_TRUE(result == UnorderedFlatmap.end());
    ASSERT_EQ(5u, UnorderedFlatmap.Size());
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_iterate)
{
    auto loopTimes = 0;
    for (const auto &[key, value] : UnorderedFlatmap)
    {
        if (key == "One")
            ASSERT_EQ(1, value);

        if (key == "Two")
            ASSERT_EQ(2, value);

        if (key == "Three")
            ASSERT_EQ(3, value);

        if (key == "Four")
            ASSERT_EQ(4, value);

        if (key == "Five")
            ASSERT_EQ(5, value);

        ++loopTimes;
    }

    ASSERT_EQ(5u, UnorderedFlatmap.Size());
    ASSERT_EQ(5, loopTimes);
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_erase_by_key)
{
    UnorderedFlatmap.Erase("Something! 123");
    ASSERT_EQ(5u, UnorderedFlatmap.Size());

    UnorderedFlatmap.Erase("Three");
    ASSERT_EQ(4u, UnorderedFlatmap.Size());

    UnorderedFlatmap.Erase("Two");
    ASSERT_EQ(3u, UnorderedFlatmap.Size());
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_erase_by_iterator)
{
    ASSERT_EQ(5u, UnorderedFlatmap.Size());

    auto result = UnorderedFlatmap.Find("Three");
    UnorderedFlatmap.Erase(result);

    ASSERT_EQ(4u, UnorderedFlatmap.Size());

    result = UnorderedFlatmap.Find("Two");
    UnorderedFlatmap.Erase(result);

    ASSERT_EQ(3u, UnorderedFlatmap.Size());
}

TEST_F(TestFixtureUnorderedFlatmapDefaultData, test_unordered_flatmap_erase_if)
{
    ASSERT_EQ(5u, UnorderedFlatmap.Size());
    UnorderedFlatmap.EraseIf([](const auto &pair) { return (pair.first == "Two" || pair.first == "Four"); });
    ASSERT_EQ(3u, UnorderedFlatmap.Size());
}

TEST(test_fixture_unordered_flatmap, test_unordered_flatmap_compare_different_size)
{
    const Common::Containers::UnorderedFlatmap<Common::String, int> map1{{"hello", 3}, {"bye", 4}};
    const Common::Containers::UnorderedFlatmap<Common::String, int> map2{{"hello", 3}, {"bye", 4}, {"another", 6}};
    EXPECT_FALSE(map1 == map2);
    EXPECT_TRUE(map1 != map2);
}

TEST(test_fixture_unordered_flatmap, test_unordered_flatmap_compare_different_key)
{
    const Common::Containers::UnorderedFlatmap<Common::String, int> map1{{"hello", 3}, {"bye", 4}};
    const Common::Containers::UnorderedFlatmap<Common::String, int> map2{{"hello", 3}, {"bye2", 4}};
    EXPECT_FALSE(map1 == map2);
    EXPECT_TRUE(map1 != map2);
}

TEST(test_fixture_unordered_flatmap, test_unordered_flatmap_compare_different_value)
{
    const Common::Containers::UnorderedFlatmap<Common::String, int> map1{{"hello", 3}, {"bye", 4}};
    const Common::Containers::UnorderedFlatmap<Common::String, int> map2{{"hello", 3}, {"bye", 5}};
    EXPECT_FALSE(map1 == map2);
    EXPECT_TRUE(map1 != map2);
}

TEST(test_fixture_unordered_flatmap, test_unordered_flatmap_compare_equal)
{
    const Common::Containers::UnorderedFlatmap<Common::String, int> map1{{"hello", 3}, {"bye", 4}};
    const Common::Containers::UnorderedFlatmap<Common::String, int> map2{{"hello", 3}, {"bye", 4}};
    EXPECT_TRUE(map1 == map2);
    EXPECT_FALSE(map1 != map2);
}
