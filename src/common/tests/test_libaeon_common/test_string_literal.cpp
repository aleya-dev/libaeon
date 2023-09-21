// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/string_literal.h>
#include <aeon/common/string.h>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace aeon::Common;

TEST(test_string_literal, test_string_literal_create_char)
{
    StringLiteral<6> s{"Hello"};
    StringLiteral<6> s2 = "Hello";

    EXPECT_EQ(s.size(), strlen("Hello") + 1);
    EXPECT_EQ(s2.size(), strlen("Hello") + 1);

    EXPECT_EQ(String{s.c_str()}, String{s2.c_str()});
}
