// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/commandline_parser.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_commandline_parser, test_commandline_parser_positional)
{
    Common::CommandlineParser parser;
    parser.AddPositional("a", "description 1");
    parser.AddPositional("b", "description 2");
    parser.AddPositional("c", "description 3");

    const auto result = parser.Parse({"1", "2", "3"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.Success());
    EXPECT_FALSE(result.Failed());

    EXPECT_EQ(result.Positional(0), "1");
    EXPECT_EQ(result.Positional(1), "2");
    EXPECT_EQ(result.Positional(2), "3");

    EXPECT_ANY_THROW([[maybe_unused]] auto arg = result.Positional(3));
}

TEST(test_commandline_parser, test_commandline_parser_short_options)
{
    Common::CommandlineParser parser;
    parser.AddOption("a", "description 1");
    parser.AddOption("b", "description 2");

    const auto result = parser.Parse({"-a", "-b"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.Success());
    EXPECT_FALSE(result.Failed());

    EXPECT_TRUE(result.HasOption("a"));
    EXPECT_TRUE(result.HasOption("b"));
    EXPECT_FALSE(result.HasOption("c"));

    EXPECT_TRUE(parser.Parse({"-a"}));
    EXPECT_TRUE(parser.Parse({"-b"}));
    EXPECT_FALSE(parser.Parse({"-c"}));
    EXPECT_FALSE(parser.Parse({"--a"}));
    EXPECT_FALSE(parser.Parse({"--b"}));
    EXPECT_FALSE(parser.Parse({"--a", "--b"}));
}

TEST(test_commandline_parser, test_commandline_parser_long_options)
{
    Common::CommandlineParser parser;
    parser.AddOption("aaa", "description 1");
    parser.AddOption("bbb", "description 2");

    const auto result = parser.Parse({"--aaa", "--bbb"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.Success());
    EXPECT_FALSE(result.Failed());

    EXPECT_TRUE(result.HasOption("aaa"));
    EXPECT_TRUE(result.HasOption("bbb"));
    EXPECT_FALSE(result.HasOption("ccc"));

    EXPECT_TRUE(parser.Parse({"--aaa"}));
    EXPECT_TRUE(parser.Parse({"--bbb"}));
    EXPECT_FALSE(parser.Parse({"-aaa"}));
    EXPECT_FALSE(parser.Parse({"-bbb"}));
    EXPECT_FALSE(parser.Parse({"--ccc"}));
    EXPECT_FALSE(parser.Parse({"-aaa", "-bbb"}));
}

TEST(test_commandline_parser, test_commandline_parser_mixed_options)
{
    Common::CommandlineParser parser;
    parser.AddOption("aaa", "description 1");
    parser.AddOption("bbb", "description 2");
    parser.AddOption("a", "description 3");
    parser.AddOption("b", "description 4");

    const auto result = parser.Parse({"--aaa", "--bbb", "-a", "-b"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.Success());
    EXPECT_FALSE(result.Failed());

    EXPECT_TRUE(result.HasOption("aaa"));
    EXPECT_TRUE(result.HasOption("bbb"));
    EXPECT_TRUE(result.HasOption("a"));
    EXPECT_TRUE(result.HasOption("b"));
    EXPECT_FALSE(result.HasOption("ccc"));

    EXPECT_TRUE(parser.Parse({"--aaa"}));
    EXPECT_TRUE(parser.Parse({"--bbb"}));
    EXPECT_TRUE(parser.Parse({"-a"}));
    EXPECT_TRUE(parser.Parse({"-b"}));
    EXPECT_TRUE(parser.Parse({"--aaa", "-a"}));
    EXPECT_TRUE(parser.Parse({"--bbb", "-b"}));
    EXPECT_FALSE(parser.Parse({"-aaa", "--a"}));
    EXPECT_FALSE(parser.Parse({"-bbb", "--b"}));
    EXPECT_FALSE(parser.Parse({"-aaa"}));
    EXPECT_FALSE(parser.Parse({"-bbb"}));
    EXPECT_FALSE(parser.Parse({"--a"}));
    EXPECT_FALSE(parser.Parse({"--b"}));
}

TEST(test_commandline_parser, test_commandline_parser_short_args)
{
    Common::CommandlineParser parser;
    parser.AddArgument("a", "description 1");
    parser.AddArgument("b", "description 2");

    const auto result = parser.Parse({"-a", "value_a", "-b", "value_b"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.Success());
    EXPECT_FALSE(result.Failed());

    ASSERT_TRUE(result.HasArgument("a"));
    EXPECT_EQ("value_a", result.GetArgument("a"));
    ASSERT_TRUE(result.HasArgument("b"));
    EXPECT_EQ("value_b", result.GetArgument("b"));

    EXPECT_TRUE(parser.Parse({"-a", "value_a"}));
    EXPECT_FALSE(parser.Parse({"-a", "value_a", "-b"}));
    EXPECT_FALSE(parser.Parse({"--a", "value_a"}));
}

TEST(test_commandline_parser, test_commandline_parser_long_args)
{
    Common::CommandlineParser parser;
    parser.AddArgument("aaa", "description 1");
    parser.AddArgument("bbb", "description 2");

    const auto result = parser.Parse({"--aaa", "value_a", "--bbb", "value_b"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.Success());
    EXPECT_FALSE(result.Failed());

    ASSERT_TRUE(result.HasArgument("aaa"));
    EXPECT_EQ("value_a", result.GetArgument("aaa"));
    ASSERT_TRUE(result.HasArgument("bbb"));
    EXPECT_EQ("value_b", result.GetArgument("bbb"));

    EXPECT_TRUE(parser.Parse({"--aaa", "value_a"}));
    EXPECT_FALSE(parser.Parse({"--aaa", "value_a", "--bbb"}));
    EXPECT_FALSE(parser.Parse({"-aaa", "value_a"}));
}

TEST(test_commandline_parser, test_commandline_parser_all_mixed)
{
    Common::CommandlineParser parser;
    parser.AddPositional("a", "description 1");
    parser.AddPositional("bbb", "description 2");
    parser.AddOption("c", "description 3");
    parser.AddOption("ccc", "description 4");
    parser.AddArgument("d", "description 5");
    parser.AddArgument("ddd", "description 6");

    const auto result = parser.Parse({"1", "2", "--ccc", "-c", "--ddd", "value_ddd", "-d", "value_d"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.Success());
    EXPECT_FALSE(result.Failed());

    EXPECT_EQ(result.Positional(0), "1");
    EXPECT_EQ(result.Positional(1), "2");
    EXPECT_TRUE(result.HasOption("c"));
    EXPECT_TRUE(result.HasOption("ccc"));
    ASSERT_TRUE(result.HasArgument("ddd"));
    EXPECT_EQ("value_ddd", result.GetArgument("ddd"));
    ASSERT_TRUE(result.HasArgument("d"));
    EXPECT_EQ("value_d", result.GetArgument("d"));
}
