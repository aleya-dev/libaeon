// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/string_utils.h>
#include <aeon/common/compilers.h>
#include <gtest/gtest.h>

AEON_IGNORE_VS_WARNING(4189)

using namespace aeon;

TEST(test_string_utils, test_string_utils_ltrim_none)
{
    Common::String str = "value";
    Common::StringUtils::Ltrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_ltrim_spaces)
{
    Common::String str = "   value";
    Common::StringUtils::Ltrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_ltrimsv_spaces)
{
    Common::String str = "   value";
    Common::StringView strsv = str;
    Common::StringUtils::Ltrimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_ltrim_spaces_at_end)
{
    Common::String str = "value  ";
    Common::StringUtils::Ltrim(str);
    EXPECT_EQ("value  ", str);
}

TEST(test_string_utils, test_string_utils_ltrimsv_spaces_at_end)
{
    Common::String str = "value  ";
    Common::StringView strsv = str;
    Common::StringUtils::Ltrimsv(strsv);
    EXPECT_EQ("value  ", strsv);
}

TEST(test_string_utils, test_string_utils_ltrim_spaces_at_end2)
{
    Common::String str = "  value  ";
    Common::StringUtils::Ltrim(str);
    EXPECT_EQ("value  ", str);
}

TEST(test_string_utils, test_string_utils_ltrimsv_spaces_at_end2)
{
    Common::String str = "  value  ";
    Common::StringView strsv = str;
    Common::StringUtils::Ltrimsv(strsv);
    EXPECT_EQ("value  ", strsv);
}

TEST(test_string_utils, test_string_utils_rtrim_spaces)
{
    Common::String str = "value   ";
    Common::StringUtils::Rtrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_rtrimsv_spaces)
{
    Common::String str = "value   ";
    Common::StringView strsv = str;
    Common::StringUtils::Rtrimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_rtrim_spaces_at_beginning)
{
    Common::String str = "   value";
    Common::StringUtils::Rtrim(str);
    EXPECT_EQ("   value", str);
}

TEST(test_string_utils, test_string_utils_rtrimsv_spaces_at_beginning)
{
    Common::String str = "   value";
    Common::StringView strsv = str;
    Common::StringUtils::Rtrimsv(strsv);
    EXPECT_EQ("   value", strsv);
}

TEST(test_string_utils, test_string_utils_rtrim_spaces_at_beginning2)
{
    Common::String str = "   value   ";
    Common::StringUtils::Rtrim(str);
    EXPECT_EQ("   value", str);
}

TEST(test_string_utils, test_string_utils_rtrimsv_spaces_at_beginning2)
{
    Common::String str = "   value   ";
    Common::StringView strsv = str;
    Common::StringUtils::Rtrimsv(strsv);
    EXPECT_EQ("   value", strsv);
}

TEST(test_string_utils, test_string_utils_trim)
{
    Common::String str = "   value   ";
    Common::StringUtils::Trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_trimsv)
{
    Common::String str = "   value   ";
    Common::StringView strsv = str;
    Common::StringUtils::Trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_trim2)
{
    Common::String str = "   value";
    Common::StringUtils::Trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_trimsv2)
{
    Common::String str = "   value";
    Common::StringView strsv = str;
    Common::StringUtils::Trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_trim3)
{
    Common::String str = "value  ";
    Common::StringUtils::Trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_trimsv3)
{
    Common::String str = "value  ";
    Common::StringView strsv = str;
    Common::StringUtils::Trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_trim4)
{
    Common::String str = "value";
    Common::StringUtils::Trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_trimsv4)
{
    Common::String str = "value";
    Common::StringView strsv = str;
    Common::StringUtils::Trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_ltrimmed)
{
    EXPECT_EQ("value", Common::StringUtils::Ltrimmed("   value"));
}

TEST(test_string_utils, test_string_utils_ltrimmedsv)
{
    EXPECT_EQ("value", Common::StringUtils::Ltrimmedsv("   value"));
}

TEST(test_string_utils, test_string_utils_rtrimmed)
{
    EXPECT_EQ("value", Common::StringUtils::Rtrimmed("value   "));
}

TEST(test_string_utils, test_string_utils_rtrimmedsv)
{
    EXPECT_EQ("value", Common::StringUtils::Rtrimmedsv("value   "));
}

TEST(test_string_utils, test_string_utils_trimmed)
{
    EXPECT_EQ("value", Common::StringUtils::Trimmed("   value   "));
}

TEST(test_string_utils, test_string_utils_trimmedsv)
{
    EXPECT_EQ("value", Common::StringUtils::Trimmedsv("   value   "));
}

TEST(test_string_utils, test_string_utils_trim_tabs)
{
    Common::String str = "\t\tvalue\t\t";
    Common::StringUtils::Trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_trimsv_tabs)
{
    Common::String str = "\t\tvalue\t\t";
    Common::StringView strsv = str;
    Common::StringUtils::Trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_trim_mixed)
{
    Common::String str = " \t \t \t value \t \t \t ";
    Common::StringUtils::Trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_split_empty)
{
    Common::String str = "";
    auto result = Common::StringUtils::Split(str, ' ');
    ASSERT_TRUE(result.empty());
}

TEST(test_string_utils, test_string_utils_splitsv_empty)
{
    Common::String str = "";
    auto result = Common::StringUtils::Splitsv(str, ' ');
    ASSERT_TRUE(result.empty());
}

TEST(test_string_utils, test_string_utils_split)
{
    Common::String str = "one two three";
    auto result = Common::StringUtils::Split(str, ' ');
    ASSERT_EQ(3u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("two", result[1]);
    EXPECT_EQ("three", result[2]);
}

TEST(test_string_utils, test_string_utils_splitsv)
{
    Common::String str = "one two three";
    auto result = Common::StringUtils::Splitsv(str, ' ');
    ASSERT_EQ(3u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("two", result[1]);
    EXPECT_EQ("three", result[2]);
}

TEST(test_string_utils, test_string_utils_split_double_space)
{
    Common::String str = "one  two three";
    auto result = Common::StringUtils::Split(str, ' ');
    ASSERT_EQ(4u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("two", result[2]);
    EXPECT_EQ("three", result[3]);
}

TEST(test_string_utils, test_string_utils_splitsv_double_space)
{
    Common::String str = "one  two three";
    auto result = Common::StringUtils::Splitsv(str, ' ');
    ASSERT_EQ(4u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("two", result[2]);
    EXPECT_EQ("three", result[3]);
}

TEST(test_string_utils, test_string_utils_split_one_token)
{
    Common::String str = "one";
    const auto result = Common::StringUtils::Split(str, ' ');
    ASSERT_EQ(1u, std::size(result));
    EXPECT_EQ("one", result[0]);
}

TEST(test_string_utils, test_string_utils_splitsv_one_token)
{
    Common::String str = "one";
    const auto result = Common::StringUtils::Splitsv(str, ' ');
    ASSERT_EQ(1u, std::size(result));
    EXPECT_EQ("one", result[0]);
}

TEST(test_string_utils, test_string_utils_left)
{
    EXPECT_EQ("one", Common::StringUtils::Left("one two three", 3));
}

TEST(test_string_utils, test_string_utils_leftsv)
{
    EXPECT_EQ("one", Common::StringUtils::Leftsv("one two three", 3));
}

TEST(test_string_utils, test_string_utils_right)
{
    EXPECT_EQ("ree", Common::StringUtils::Right("one two three", 3));
}

TEST(test_string_utils, test_string_utils_rightsv)
{
    EXPECT_EQ("ree", Common::StringUtils::Rightsv("one two three", 3));
}

TEST(test_string_utils, test_string_utils_strip_left)
{
    EXPECT_EQ("two three", Common::StringUtils::StrippedLeft("one two three", 4));

    Common::String str = "one two three";
    Common::StringUtils::StripLeft(str, 4);
    EXPECT_EQ("two three", str);
}

TEST(test_string_utils, test_string_utils_strip_leftsv)
{
    EXPECT_EQ("two three", Common::StringUtils::StrippedLeftsv("one two three", 4));

    const Common::String str = "one two three";
    Common::StringView view = str;
    Common::StringUtils::StripLeftsv(view, 4);
    EXPECT_EQ("two three", view);
}

TEST(test_string_utils, test_string_utils_strip_right)
{
    EXPECT_EQ("one two ", Common::StringUtils::StrippedRight("one two three", 5));

    Common::String str = "one two three";
    Common::StringUtils::StripRight(str, 5);
    EXPECT_EQ("one two ", str);
}

TEST(test_string_utils, test_string_utils_strip_rightsv)
{
    EXPECT_EQ("one two ", Common::StringUtils::StrippedRightsv("one two three", 5));

    const Common::String str = "one two three";
    Common::StringView view = str;
    Common::StringUtils::StripRightsv(view, 5);
    EXPECT_EQ("one two ", view);
}

TEST(test_string_utils, test_string_utils_strip_both)
{
    EXPECT_EQ("test", Common::StringUtils::StrippedBoth("test", 0));
    EXPECT_EQ("test", Common::StringUtils::StrippedBoth("'test'", 1));
    EXPECT_EQ("ABC", Common::StringUtils::StrippedBoth("123ABC123", 3));
    EXPECT_EQ("", Common::StringUtils::StrippedBoth("''", 1));

    Common::String test = "test";
    Common::StringUtils::StripBoth(test, 0);
    EXPECT_EQ("test", test);

    Common::String test2 = "'test'";
    Common::StringUtils::StripBoth(test2, 1);
    EXPECT_EQ("test", test2);

    Common::String test3 = "123ABC123";
    Common::StringUtils::StripBoth(test3, 3);
    EXPECT_EQ("ABC", test3);

    Common::String test4 = "''";
    Common::StringUtils::StripBoth(test4, 1);
    EXPECT_EQ("", test4);
}

TEST(test_string_utils, test_string_utils_strip_bothsv)
{
    EXPECT_EQ("test", Common::StringUtils::StrippedBothsv("test", 0));
    EXPECT_EQ("test", Common::StringUtils::StrippedBothsv("'test'", 1));
    EXPECT_EQ("ABC", Common::StringUtils::StrippedBothsv("123ABC123", 3));
    EXPECT_EQ("", Common::StringUtils::StrippedBothsv("''", 1));

    const Common::String test = "test";
    Common::StringView view = test;
    Common::StringUtils::StripBothsv(view, 0);
    EXPECT_EQ("test", view);

    const Common::String test2 = "'test'";
    Common::StringView view2 = test2;
    Common::StringUtils::StripBothsv(view2, 1);
    EXPECT_EQ("test", view2);

    const Common::String test3 = "123ABC123";
    Common::StringView view3 = test3;
    Common::StringUtils::StripBothsv(view3, 3);
    EXPECT_EQ("ABC", view3);

    const Common::String test4 = "''";
    Common::StringView view4 = test4;
    Common::StringUtils::StripBothsv(view4, 1);
    EXPECT_EQ("", view4);
}

TEST(test_string_utils, test_string_utils_char_strip_left)
{
    EXPECT_EQ("two three", Common::StringUtils::CharStrippedLeft("--two three", '-'));
    EXPECT_EQ("--two three", Common::StringUtils::CharStrippedLeft("--two three", '+'));

    Common::String str = "--two three";
    Common::StringUtils::CharStripLeft(str, '-');
    EXPECT_EQ("two three", str);
}

TEST(test_string_utils, test_string_utils_char_strip_leftsv)
{
    EXPECT_EQ("two three--", Common::StringUtils::CharStrippedLeftsv("--two three--", '-'));
    EXPECT_EQ("--two three--", Common::StringUtils::CharStrippedLeftsv("--two three--", '+'));

    Common::StringView str = "--two three--";
    Common::StringUtils::CharStripLeftsv(str, '-');
    EXPECT_EQ("two three--", str);
}

TEST(test_string_utils, test_string_utils_char_strip_right)
{
    EXPECT_EQ("--two three", Common::StringUtils::CharStrippedRight("--two three--", '-'));
    EXPECT_EQ("--two three--", Common::StringUtils::CharStrippedRight("--two three--", '+'));

    Common::String str = "--two three--";
    Common::StringUtils::CharStripRight(str, '-');
    EXPECT_EQ("--two three", str);
}

TEST(test_string_utils, test_string_utils_char_strip_rightsv)
{
    EXPECT_EQ("--two three", Common::StringUtils::CharStrippedRightsv("--two three--", '-'));
    EXPECT_EQ("--two three--", Common::StringUtils::CharStrippedRightsv("--two three--", '+'));

    Common::StringView str = "--two three--";
    Common::StringUtils::CharStripRightsv(str, '-');
    EXPECT_EQ("--two three", str);
}

TEST(test_string_utils, test_string_utils_char_strip_both)
{
    EXPECT_EQ("two three", Common::StringUtils::CharStrippedBoth("--two three--", '-'));
    EXPECT_EQ("--two three--", Common::StringUtils::CharStrippedBoth("--two three--", '+'));

    Common::String str = "--two three--";
    Common::StringUtils::CharStripBoth(str, '-');
    EXPECT_EQ("two three", str);
}

TEST(test_string_utils, test_string_utils_char_strip_bothsv)
{
    EXPECT_EQ("two three", Common::StringUtils::CharStrippedBothsv("--two three--", '-'));
    EXPECT_EQ("--two three--", Common::StringUtils::CharStrippedBothsv("--two three--", '+'));

    Common::StringView str = "--two three--";
    Common::StringUtils::CharStripBothsv(str, '-');
    EXPECT_EQ("two three", str);
}

TEST(test_string_utils, test_string_utils_to_lower)
{
    EXPECT_EQ("test", Common::StringUtils::ToLowerCopy("TeSt"));
    EXPECT_EQ("this is a test.", Common::StringUtils::ToLowerCopy("THIS iS a TeSt."));

    Common::String test = "TeSt";
    Common::StringUtils::ToLower(test);
    EXPECT_EQ("test", test);

    Common::String this_is_a_test = "THIS iS a TeSt.";
    Common::StringUtils::ToLower(this_is_a_test);
    EXPECT_EQ("this is a test.", this_is_a_test);
}

TEST(test_string_utils, test_string_utils_to_upper)
{
    EXPECT_EQ("TEST", Common::StringUtils::ToUpperCopy("TeSt"));
    EXPECT_EQ("THIS IS A TEST.", Common::StringUtils::ToUpperCopy("THiS iS a TeSt."));

    Common::String test = "TeSt";
    Common::StringUtils::ToUpper(test);
    EXPECT_EQ("TEST", test);

    Common::String this_is_a_test = "THIS iS a TeSt.";
    Common::StringUtils::ToUpper(this_is_a_test);
    EXPECT_EQ("THIS IS A TEST.", this_is_a_test);
}

TEST(test_string_utils, test_string_utils_begins_with)
{
    EXPECT_TRUE(Common::StringUtils::BeginsWith("", ""));
    EXPECT_TRUE(Common::StringUtils::BeginsWith("This is a test", "T"));
    EXPECT_TRUE(Common::StringUtils::BeginsWith("This is a test", "Th"));
    EXPECT_TRUE(Common::StringUtils::BeginsWith("This is a test", "This"));
    EXPECT_TRUE(Common::StringUtils::BeginsWith("1234 blah", "123"));

    EXPECT_FALSE(Common::StringUtils::BeginsWith("This is a test", "test"));
    EXPECT_FALSE(Common::StringUtils::BeginsWith("This is a test", "this"));
    EXPECT_FALSE(Common::StringUtils::BeginsWith("This is a test", "his"));
    EXPECT_FALSE(Common::StringUtils::BeginsWith("1234 blah", "blah"));
    EXPECT_FALSE(Common::StringUtils::BeginsWith("", "Blah"));
}

TEST(test_string_utils, test_string_utils_ends_with)
{
    EXPECT_TRUE(Common::StringUtils::EndsWith("", ""));
    EXPECT_TRUE(Common::StringUtils::EndsWith("This is a test", "t"));
    EXPECT_TRUE(Common::StringUtils::EndsWith("This is a test", "est"));
    EXPECT_TRUE(Common::StringUtils::EndsWith("This is a test", "test"));
    EXPECT_TRUE(Common::StringUtils::EndsWith("1234 blah", " blah"));

    EXPECT_FALSE(Common::StringUtils::EndsWith("This is a test", "This"));
    EXPECT_FALSE(Common::StringUtils::EndsWith("This is a test", "is"));
    EXPECT_FALSE(Common::StringUtils::EndsWith("This is a test", "Test"));
    EXPECT_FALSE(Common::StringUtils::EndsWith("1234 blah", "1234"));
    EXPECT_FALSE(Common::StringUtils::EndsWith("", "Blah"));
}

TEST(test_string_utils, test_iequals)
{
    EXPECT_TRUE(Common::StringUtils::IEquals("Test", "test"));
    EXPECT_TRUE(Common::StringUtils::IEquals("Test", "TeSt"));
    EXPECT_TRUE(Common::StringUtils::IEquals("Test", "TESt"));
    EXPECT_TRUE(Common::StringUtils::IEquals("Test", "TEST"));
    EXPECT_TRUE(Common::StringUtils::IEquals(Common::String{"Test"}, "TEST"));
    EXPECT_TRUE(Common::StringUtils::IEquals(Common::StringView{"Test"}, "TEST"));

    EXPECT_FALSE(Common::StringUtils::IEquals("Test", "test2"));
    EXPECT_FALSE(Common::StringUtils::IEquals("Test", "TeSt2"));
    EXPECT_FALSE(Common::StringUtils::IEquals("Test", "TESt2"));
    EXPECT_FALSE(Common::StringUtils::IEquals("Test", "TEST2"));
    EXPECT_FALSE(Common::StringUtils::IEquals(Common::String{"Test"}, "TEST2"));
    EXPECT_FALSE(Common::StringUtils::IEquals(Common::StringView{"Test"}, "TEST2"));
}
