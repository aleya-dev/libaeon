﻿// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/unicode/encoding.h>
#include <aeon/common/bom.h>
#include <gtest/gtest.h>
#include <array>

using namespace aeon;

TEST(test_encoding, test_encoding_convert)
{
    const auto str = u8"I like Π, and らき☆すた, Raki☆Suta ";
    const auto converted = unicode::utf8::to_utf16(str);
    const auto converted2 = unicode::utf16::to_utf8(converted);

    EXPECT_TRUE(str == converted2);
}

TEST(test_encoding, test_encoding_convert_with_bom)
{
    const auto str = common::bom::utf8::string() + u8"I like Π, and らき☆すた, Raki☆Suta ";
    const auto converted = unicode::utf8::to_utf16(str);
    const auto converted2 = unicode::utf16::to_utf8(converted);

    EXPECT_TRUE(str == converted2);
}

TEST(test_encoding, test_encoding_utf32)
{
    const auto str1 = unicode::utf32::to_utf8('A');
    EXPECT_EQ(1u, std::size(str1));

    const auto str2 = unicode::utf32::to_utf8(U"ę");
    EXPECT_EQ(2u, std::size(str2));

    const auto str3 = unicode::utf32::to_utf8(U"ら");
    EXPECT_EQ(3u, std::size(str3));

    const auto str4 = unicode::utf32::to_utf8(U"𠜎");
    EXPECT_EQ(4u, std::size(str4));

    const auto banana = unicode::utf32::to_utf8(U"🍌");
    EXPECT_EQ(4u, std::size(banana));
}
