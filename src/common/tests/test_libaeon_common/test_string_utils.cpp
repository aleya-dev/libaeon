// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/string_utils.h>
#include <aeon/common/compilers.h>
#include <gtest/gtest.h>

AEON_IGNORE_VS_WARNING(4189)

using namespace aeon;

TEST(test_string_utils, test_string_utils_ltrim_none)
{
    common::string str = "value";
    common::string_utils::ltrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_ltrim_spaces)
{
    common::string str = "   value";
    common::string_utils::ltrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_ltrimsv_spaces)
{
    common::string str = "   value";
    common::string_view strsv = str;
    common::string_utils::ltrimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_ltrim_spaces_at_end)
{
    common::string str = "value  ";
    common::string_utils::ltrim(str);
    EXPECT_EQ("value  ", str);
}

TEST(test_string_utils, test_string_utils_ltrimsv_spaces_at_end)
{
    common::string str = "value  ";
    common::string_view strsv = str;
    common::string_utils::ltrimsv(strsv);
    EXPECT_EQ("value  ", strsv);
}

TEST(test_string_utils, test_string_utils_ltrim_spaces_at_end2)
{
    common::string str = "  value  ";
    common::string_utils::ltrim(str);
    EXPECT_EQ("value  ", str);
}

TEST(test_string_utils, test_string_utils_ltrimsv_spaces_at_end2)
{
    common::string str = "  value  ";
    common::string_view strsv = str;
    common::string_utils::ltrimsv(strsv);
    EXPECT_EQ("value  ", strsv);
}

TEST(test_string_utils, test_string_utils_rtrim_spaces)
{
    common::string str = "value   ";
    common::string_utils::rtrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_rtrimsv_spaces)
{
    common::string str = "value   ";
    common::string_view strsv = str;
    common::string_utils::rtrimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_rtrim_spaces_at_beginning)
{
    common::string str = "   value";
    common::string_utils::rtrim(str);
    EXPECT_EQ("   value", str);
}

TEST(test_string_utils, test_string_utils_rtrimsv_spaces_at_beginning)
{
    common::string str = "   value";
    common::string_view strsv = str;
    common::string_utils::rtrimsv(strsv);
    EXPECT_EQ("   value", strsv);
}

TEST(test_string_utils, test_string_utils_rtrim_spaces_at_beginning2)
{
    common::string str = "   value   ";
    common::string_utils::rtrim(str);
    EXPECT_EQ("   value", str);
}

TEST(test_string_utils, test_string_utils_rtrimsv_spaces_at_beginning2)
{
    common::string str = "   value   ";
    common::string_view strsv = str;
    common::string_utils::rtrimsv(strsv);
    EXPECT_EQ("   value", strsv);
}

TEST(test_string_utils, test_string_utils_trim)
{
    common::string str = "   value   ";
    common::string_utils::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_trimsv)
{
    common::string str = "   value   ";
    common::string_view strsv = str;
    common::string_utils::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_trim2)
{
    common::string str = "   value";
    common::string_utils::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_trimsv2)
{
    common::string str = "   value";
    common::string_view strsv = str;
    common::string_utils::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_trim3)
{
    common::string str = "value  ";
    common::string_utils::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_trimsv3)
{
    common::string str = "value  ";
    common::string_view strsv = str;
    common::string_utils::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_trim4)
{
    common::string str = "value";
    common::string_utils::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_trimsv4)
{
    common::string str = "value";
    common::string_view strsv = str;
    common::string_utils::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_ltrimmed)
{
    EXPECT_EQ("value", common::string_utils::ltrimmed("   value"));
}

TEST(test_string_utils, test_string_utils_ltrimmedsv)
{
    EXPECT_EQ("value", common::string_utils::ltrimmedsv("   value"));
}

TEST(test_string_utils, test_string_utils_rtrimmed)
{
    EXPECT_EQ("value", common::string_utils::rtrimmed("value   "));
}

TEST(test_string_utils, test_string_utils_rtrimmedsv)
{
    EXPECT_EQ("value", common::string_utils::rtrimmedsv("value   "));
}

TEST(test_string_utils, test_string_utils_trimmed)
{
    EXPECT_EQ("value", common::string_utils::trimmed("   value   "));
}

TEST(test_string_utils, test_string_utils_trimmedsv)
{
    EXPECT_EQ("value", common::string_utils::trimmedsv("   value   "));
}

TEST(test_string_utils, test_string_utils_trim_tabs)
{
    common::string str = "\t\tvalue\t\t";
    common::string_utils::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_trimsv_tabs)
{
    common::string str = "\t\tvalue\t\t";
    common::string_view strsv = str;
    common::string_utils::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string_utils, test_string_utils_trim_mixed)
{
    common::string str = " \t \t \t value \t \t \t ";
    common::string_utils::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string_utils, test_string_utils_split_empty)
{
    common::string str = "";
    auto result = common::string_utils::split(str, ' ');
    ASSERT_TRUE(result.empty());
}

TEST(test_string_utils, test_string_utils_splitsv_empty)
{
    common::string str = "";
    auto result = common::string_utils::splitsv(str, ' ');
    ASSERT_TRUE(result.empty());
}

TEST(test_string_utils, test_string_utils_split)
{
    common::string str = "one two three";
    auto result = common::string_utils::split(str, ' ');
    ASSERT_EQ(3u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("two", result[1]);
    EXPECT_EQ("three", result[2]);
}

TEST(test_string_utils, test_string_utils_splitsv)
{
    common::string str = "one two three";
    auto result = common::string_utils::splitsv(str, ' ');
    ASSERT_EQ(3u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("two", result[1]);
    EXPECT_EQ("three", result[2]);
}

TEST(test_string_utils, test_string_utils_split_double_space)
{
    common::string str = "one  two three";
    auto result = common::string_utils::split(str, ' ');
    ASSERT_EQ(4u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("two", result[2]);
    EXPECT_EQ("three", result[3]);
}

TEST(test_string_utils, test_string_utils_splitsv_double_space)
{
    common::string str = "one  two three";
    auto result = common::string_utils::splitsv(str, ' ');
    ASSERT_EQ(4u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("two", result[2]);
    EXPECT_EQ("three", result[3]);
}

TEST(test_string_utils, test_string_utils_split_one_token)
{
    common::string str = "one";
    const auto result = common::string_utils::split(str, ' ');
    ASSERT_EQ(1u, std::size(result));
    EXPECT_EQ("one", result[0]);
}

TEST(test_string_utils, test_string_utils_splitsv_one_token)
{
    common::string str = "one";
    const auto result = common::string_utils::splitsv(str, ' ');
    ASSERT_EQ(1u, std::size(result));
    EXPECT_EQ("one", result[0]);
}

TEST(test_string_utils, test_string_utils_left)
{
    EXPECT_EQ("one", common::string_utils::left("one two three", 3));
}

TEST(test_string_utils, test_string_utils_leftsv)
{
    EXPECT_EQ("one", common::string_utils::leftsv("one two three", 3));
}

TEST(test_string_utils, test_string_utils_right)
{
    EXPECT_EQ("ree", common::string_utils::right("one two three", 3));
}

TEST(test_string_utils, test_string_utils_rightsv)
{
    EXPECT_EQ("ree", common::string_utils::rightsv("one two three", 3));
}

TEST(test_string_utils, test_string_utils_strip_left)
{
    EXPECT_EQ("two three", common::string_utils::stripped_left("one two three", 4));

    common::string str = "one two three";
    common::string_utils::strip_left(str, 4);
    EXPECT_EQ("two three", str);
}

TEST(test_string_utils, test_string_utils_strip_leftsv)
{
    EXPECT_EQ("two three", common::string_utils::stripped_leftsv("one two three", 4));

    const common::string str = "one two three";
    common::string_view view = str;
    common::string_utils::strip_leftsv(view, 4);
    EXPECT_EQ("two three", view);
}

TEST(test_string_utils, test_string_utils_strip_right)
{
    EXPECT_EQ("one two ", common::string_utils::stripped_right("one two three", 5));

    common::string str = "one two three";
    common::string_utils::strip_right(str, 5);
    EXPECT_EQ("one two ", str);
}

TEST(test_string_utils, test_string_utils_strip_rightsv)
{
    EXPECT_EQ("one two ", common::string_utils::stripped_rightsv("one two three", 5));

    const common::string str = "one two three";
    common::string_view view = str;
    common::string_utils::strip_rightsv(view, 5);
    EXPECT_EQ("one two ", view);
}

TEST(test_string_utils, test_string_utils_strip_both)
{
    EXPECT_EQ("test", common::string_utils::stripped_both("test", 0));
    EXPECT_EQ("test", common::string_utils::stripped_both("'test'", 1));
    EXPECT_EQ("ABC", common::string_utils::stripped_both("123ABC123", 3));
    EXPECT_EQ("", common::string_utils::stripped_both("''", 1));

    common::string test = "test";
    common::string_utils::strip_both(test, 0);
    EXPECT_EQ("test", test);

    common::string test2 = "'test'";
    common::string_utils::strip_both(test2, 1);
    EXPECT_EQ("test", test2);

    common::string test3 = "123ABC123";
    common::string_utils::strip_both(test3, 3);
    EXPECT_EQ("ABC", test3);

    common::string test4 = "''";
    common::string_utils::strip_both(test4, 1);
    EXPECT_EQ("", test4);
}

TEST(test_string_utils, test_string_utils_strip_bothsv)
{
    EXPECT_EQ("test", common::string_utils::stripped_bothsv("test", 0));
    EXPECT_EQ("test", common::string_utils::stripped_bothsv("'test'", 1));
    EXPECT_EQ("ABC", common::string_utils::stripped_bothsv("123ABC123", 3));
    EXPECT_EQ("", common::string_utils::stripped_bothsv("''", 1));

    const common::string test = "test";
    common::string_view view = test;
    common::string_utils::strip_bothsv(view, 0);
    EXPECT_EQ("test", view);

    const common::string test2 = "'test'";
    common::string_view view2 = test2;
    common::string_utils::strip_bothsv(view2, 1);
    EXPECT_EQ("test", view2);

    const common::string test3 = "123ABC123";
    common::string_view view3 = test3;
    common::string_utils::strip_bothsv(view3, 3);
    EXPECT_EQ("ABC", view3);

    const common::string test4 = "''";
    common::string_view view4 = test4;
    common::string_utils::strip_bothsv(view4, 1);
    EXPECT_EQ("", view4);
}

TEST(test_string_utils, test_string_utils_char_strip_left)
{
    EXPECT_EQ("two three", common::string_utils::char_stripped_left("--two three", '-'));
    EXPECT_EQ("--two three", common::string_utils::char_stripped_left("--two three", '+'));

    common::string str = "--two three";
    common::string_utils::char_strip_left(str, '-');
    EXPECT_EQ("two three", str);
}

TEST(test_string_utils, test_string_utils_char_strip_leftsv)
{
    EXPECT_EQ("two three--", common::string_utils::char_stripped_leftsv("--two three--", '-'));
    EXPECT_EQ("--two three--", common::string_utils::char_stripped_leftsv("--two three--", '+'));

    common::string_view str = "--two three--";
    common::string_utils::char_strip_leftsv(str, '-');
    EXPECT_EQ("two three--", str);
}

TEST(test_string_utils, test_string_utils_char_strip_right)
{
    EXPECT_EQ("--two three", common::string_utils::char_stripped_right("--two three--", '-'));
    EXPECT_EQ("--two three--", common::string_utils::char_stripped_right("--two three--", '+'));

    common::string str = "--two three--";
    common::string_utils::char_strip_right(str, '-');
    EXPECT_EQ("--two three", str);
}

TEST(test_string_utils, test_string_utils_char_strip_rightsv)
{
    EXPECT_EQ("--two three", common::string_utils::char_stripped_rightsv("--two three--", '-'));
    EXPECT_EQ("--two three--", common::string_utils::char_stripped_rightsv("--two three--", '+'));

    common::string_view str = "--two three--";
    common::string_utils::char_strip_rightsv(str, '-');
    EXPECT_EQ("--two three", str);
}

TEST(test_string_utils, test_string_utils_char_strip_both)
{
    EXPECT_EQ("two three", common::string_utils::char_stripped_both("--two three--", '-'));
    EXPECT_EQ("--two three--", common::string_utils::char_stripped_both("--two three--", '+'));

    common::string str = "--two three--";
    common::string_utils::char_strip_both(str, '-');
    EXPECT_EQ("two three", str);
}

TEST(test_string_utils, test_string_utils_char_strip_bothsv)
{
    EXPECT_EQ("two three", common::string_utils::char_stripped_bothsv("--two three--", '-'));
    EXPECT_EQ("--two three--", common::string_utils::char_stripped_bothsv("--two three--", '+'));

    common::string_view str = "--two three--";
    common::string_utils::char_strip_bothsv(str, '-');
    EXPECT_EQ("two three", str);
}

TEST(test_string_utils, test_string_utils_to_lower)
{
    EXPECT_EQ("test", common::string_utils::to_lower_copy("TeSt"));
    EXPECT_EQ("this is a test.", common::string_utils::to_lower_copy("THIS iS a TeSt."));

    common::string test = "TeSt";
    common::string_utils::to_lower(test);
    EXPECT_EQ("test", test);

    common::string this_is_a_test = "THIS iS a TeSt.";
    common::string_utils::to_lower(this_is_a_test);
    EXPECT_EQ("this is a test.", this_is_a_test);
}

TEST(test_string_utils, test_string_utils_to_upper)
{
    EXPECT_EQ("TEST", common::string_utils::to_upper_copy("TeSt"));
    EXPECT_EQ("THIS IS A TEST.", common::string_utils::to_upper_copy("THiS iS a TeSt."));

    common::string test = "TeSt";
    common::string_utils::to_upper(test);
    EXPECT_EQ("TEST", test);

    common::string this_is_a_test = "THIS iS a TeSt.";
    common::string_utils::to_upper(this_is_a_test);
    EXPECT_EQ("THIS IS A TEST.", this_is_a_test);
}

TEST(test_string_utils, test_string_utils_begins_with)
{
    EXPECT_TRUE(common::string_utils::begins_with("", ""));
    EXPECT_TRUE(common::string_utils::begins_with("This is a test", "T"));
    EXPECT_TRUE(common::string_utils::begins_with("This is a test", "Th"));
    EXPECT_TRUE(common::string_utils::begins_with("This is a test", "This"));
    EXPECT_TRUE(common::string_utils::begins_with("1234 blah", "123"));

    EXPECT_FALSE(common::string_utils::begins_with("This is a test", "test"));
    EXPECT_FALSE(common::string_utils::begins_with("This is a test", "this"));
    EXPECT_FALSE(common::string_utils::begins_with("This is a test", "his"));
    EXPECT_FALSE(common::string_utils::begins_with("1234 blah", "blah"));
    EXPECT_FALSE(common::string_utils::begins_with("", "Blah"));
}

TEST(test_string_utils, test_string_utils_ends_with)
{
    EXPECT_TRUE(common::string_utils::ends_with("", ""));
    EXPECT_TRUE(common::string_utils::ends_with("This is a test", "t"));
    EXPECT_TRUE(common::string_utils::ends_with("This is a test", "est"));
    EXPECT_TRUE(common::string_utils::ends_with("This is a test", "test"));
    EXPECT_TRUE(common::string_utils::ends_with("1234 blah", " blah"));

    EXPECT_FALSE(common::string_utils::ends_with("This is a test", "This"));
    EXPECT_FALSE(common::string_utils::ends_with("This is a test", "is"));
    EXPECT_FALSE(common::string_utils::ends_with("This is a test", "Test"));
    EXPECT_FALSE(common::string_utils::ends_with("1234 blah", "1234"));
    EXPECT_FALSE(common::string_utils::ends_with("", "Blah"));
}

TEST(test_string_utils, test_iequals)
{
    EXPECT_TRUE(common::string_utils::iequals("Test", "test"));
    EXPECT_TRUE(common::string_utils::iequals("Test", "TeSt"));
    EXPECT_TRUE(common::string_utils::iequals("Test", "TESt"));
    EXPECT_TRUE(common::string_utils::iequals("Test", "TEST"));
    EXPECT_TRUE(common::string_utils::iequals(common::string{"Test"}, "TEST"));
    EXPECT_TRUE(common::string_utils::iequals(common::string_view{"Test"}, "TEST"));

    EXPECT_FALSE(common::string_utils::iequals("Test", "test2"));
    EXPECT_FALSE(common::string_utils::iequals("Test", "TeSt2"));
    EXPECT_FALSE(common::string_utils::iequals("Test", "TESt2"));
    EXPECT_FALSE(common::string_utils::iequals("Test", "TEST2"));
    EXPECT_FALSE(common::string_utils::iequals(common::string{"Test"}, "TEST2"));
    EXPECT_FALSE(common::string_utils::iequals(common::string_view{"Test"}, "TEST2"));
}
