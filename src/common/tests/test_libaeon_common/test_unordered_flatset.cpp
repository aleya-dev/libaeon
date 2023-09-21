// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/containers/unordered_flatset.h>
#include <aeon/common/string.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_unordered_flatset, test_unordered_flatset_unique_insert)
{
    Common::Containers::UnorderedFlatset<Common::String> set;

    EXPECT_EQ(0u, set.Size());
    EXPECT_TRUE(set.Empty());

    set.Insert("A");
    EXPECT_EQ(1u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Insert("B");
    EXPECT_EQ(2u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Insert("A");
    EXPECT_EQ(2u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Insert("B");
    EXPECT_EQ(2u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Insert("C");
    EXPECT_EQ(3u, set.Size());
    EXPECT_FALSE(set.Empty());
}

TEST(test_unordered_flatset, test_unordered_flatset_unique_emplace)
{
    Common::Containers::UnorderedFlatset<Common::String> set;

    EXPECT_EQ(0u, set.Size());
    EXPECT_TRUE(set.Empty());

    set.Emplace("A");
    EXPECT_EQ(1u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Emplace("B");
    EXPECT_EQ(2u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Emplace("A");
    EXPECT_EQ(2u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Emplace("B");
    EXPECT_EQ(2u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Emplace("C");
    EXPECT_EQ(3u, set.Size());
    EXPECT_FALSE(set.Empty());
}

TEST(test_unordered_flatset, test_unordered_flatset_unique_insert_emplace_mixed)
{
    Common::Containers::UnorderedFlatset<Common::String> set;

    EXPECT_EQ(0u, set.Size());
    EXPECT_TRUE(set.Empty());

    set.Emplace("A");
    EXPECT_EQ(1u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Emplace("B");
    EXPECT_EQ(2u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Insert("A");
    EXPECT_EQ(2u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Insert("B");
    EXPECT_EQ(2u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Emplace("C");
    EXPECT_EQ(3u, set.Size());
    EXPECT_FALSE(set.Empty());

    set.Insert("C");
    EXPECT_EQ(3u, set.Size());
    EXPECT_FALSE(set.Empty());
}

TEST(test_unordered_flatset, test_unordered_flatset_remove_by_value)
{
    Common::Containers::UnorderedFlatset<Common::String> set;
    set.Emplace("A");
    set.Emplace("B");
    set.Emplace("C");
    set.Emplace("D");

    EXPECT_EQ(4u, set.Size());

    EXPECT_TRUE(set.Contains("B"));
    set.Erase("B");
    EXPECT_EQ(3u, set.Size());
    EXPECT_FALSE(set.Contains("B"));

    set.Erase("ABCD");
    EXPECT_EQ(3u, set.Size());
}

TEST(test_unordered_flatset, test_unordered_flatset_remove_by_iterator)
{
    Common::Containers::UnorderedFlatset<Common::String> set;
    set.Emplace("A");
    set.Emplace("B");
    set.Emplace("C");
    set.Emplace("D");

    EXPECT_EQ(4u, set.Size());

    EXPECT_TRUE(set.Contains("A"));
    set.Erase(std::begin(set));
    EXPECT_FALSE(set.Contains("A"));
    EXPECT_EQ(3u, set.Size());

    EXPECT_TRUE(set.Contains("B"));
    set.Erase(std::begin(set));
    EXPECT_FALSE(set.Contains("B"));
    EXPECT_EQ(2u, set.Size());

    EXPECT_TRUE(set.Contains("C"));
    set.Erase(std::begin(set));
    EXPECT_FALSE(set.Contains("C"));
    EXPECT_EQ(1u, set.Size());

    EXPECT_TRUE(set.Contains("D"));
    set.Erase(std::begin(set));
    EXPECT_FALSE(set.Contains("D"));
    EXPECT_EQ(0u, set.Size());
}

TEST(test_unordered_flatset, test_unordered_flatset_compare)
{
    Common::Containers::UnorderedFlatset<Common::String> set;
    set.Emplace("A");
    set.Emplace("B");
    set.Emplace("C");

    Common::Containers::UnorderedFlatset<Common::String> set2;
    set2.Emplace("A");
    set2.Emplace("B");
    set2.Emplace("C");

    EXPECT_TRUE(set == set2);
    EXPECT_FALSE(set != set2);

    set.Emplace("D");
    EXPECT_FALSE(set == set2);
    EXPECT_TRUE(set != set2);
}
