// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/containers/general_tree.h>
#include <aeon/common/string.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_general_tree, test_create_empty)
{
    Common::Containers::GeneralTree tree{123};
    Common::Containers::GeneralTree<Common::String> tree2{"hello"};
}

TEST(test_general_tree, test_tree_interface)
{
    Common::Containers::GeneralTree<char> tree{'R'};
    auto root = tree.Root();
    auto a_chd = root.EmplaceChild('A');
    auto b_chd = root.EmplaceChild('B');
    a_chd.AddChild('C');
    a_chd.AddChild('D');
    a_chd.AddChild('E');
    auto f = b_chd.EmplaceChild('F');

    EXPECT_TRUE(root.IsRoot());
    EXPECT_FALSE(a_chd.IsRoot());
    EXPECT_FALSE(b_chd.IsRoot());
    EXPECT_FALSE(f.IsRoot());

    EXPECT_ANY_THROW([[maybe_unused]] auto parent = root.Parent());
    EXPECT_NO_THROW([[maybe_unused]] auto a_parent = a_chd.Parent());
    EXPECT_NO_THROW([[maybe_unused]] auto b_parent = b_chd.Parent());

    EXPECT_EQ(*a_chd, 'A');
    EXPECT_EQ(*b_chd, 'B');
    EXPECT_EQ(*f, 'F');

    EXPECT_EQ(2u, root.ChildCount());
    EXPECT_EQ(3u, a_chd.ChildCount());
    EXPECT_EQ(1u, b_chd.ChildCount());
    EXPECT_EQ(0u, f.ChildCount());

    EXPECT_EQ(*root.At(0), 'A');
    EXPECT_EQ(*root.At(1), 'B');

    EXPECT_EQ(*a_chd.At(0), 'C');
    EXPECT_EQ(*a_chd.At(1), 'D');
    EXPECT_EQ(*a_chd.At(2), 'E');
}
