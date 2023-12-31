﻿// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/rdp/parser.h>
#include <aeon/rdp/matchers.h>
#include <aeon/common/bom.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_rdp, test_advance_reverse_eof_bof_current)
{
    rdp::parser parser{"123"};
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_TRUE(rdp::bof(parser));
    EXPECT_FALSE(parser.reverse());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_TRUE(rdp::bof(parser));
    EXPECT_EQ('1', rdp::current(parser));
    EXPECT_TRUE(parser.advance());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_FALSE(rdp::bof(parser));
    EXPECT_EQ('2', rdp::current(parser));
    EXPECT_TRUE(parser.advance());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_FALSE(rdp::bof(parser));
    EXPECT_EQ('3', rdp::current(parser));
    EXPECT_TRUE(parser.advance());
    EXPECT_TRUE(rdp::eof(parser));
    EXPECT_FALSE(rdp::bof(parser));
    EXPECT_FALSE(parser.advance());
    EXPECT_TRUE(parser.reverse());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_FALSE(rdp::bof(parser));
    EXPECT_EQ('3', rdp::current(parser));
    EXPECT_TRUE(parser.reverse());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_FALSE(rdp::bof(parser));
    EXPECT_EQ('2', rdp::current(parser));
    EXPECT_TRUE(parser.reverse());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_TRUE(rdp::bof(parser));
    EXPECT_EQ('1', rdp::current(parser));
    EXPECT_FALSE(parser.reverse());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_TRUE(rdp::bof(parser));
}

TEST(test_rdp, test_offset_check_char)
{
    rdp::parser parser{"123"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_TRUE(parser.check('1'));
    EXPECT_EQ(1u, rdp::offset(parser));
    EXPECT_FALSE(parser.check('1'));
    EXPECT_EQ(1u, rdp::offset(parser));
    EXPECT_TRUE(parser.check('2'));
    EXPECT_EQ(2u, rdp::offset(parser));
    EXPECT_FALSE(parser.check('2'));
    EXPECT_EQ(2u, rdp::offset(parser));
    EXPECT_TRUE(parser.check('3'));
    EXPECT_EQ(3u, rdp::offset(parser));
    EXPECT_FALSE(parser.check('3'));
    EXPECT_EQ(3u, rdp::offset(parser));
}

TEST(test_rdp, test_offset_check_string)
{
    rdp::parser parser{"123"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_FALSE(parser.check("13"));
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_TRUE(parser.check("12"));
    EXPECT_EQ(2u, rdp::offset(parser));
    EXPECT_FALSE(parser.check("34"));
    EXPECT_EQ(2u, rdp::offset(parser));
    EXPECT_TRUE(parser.check("3"));
    EXPECT_EQ(3u, rdp::offset(parser));
}

TEST(test_rdp, test_offset_check_multiple)
{
    rdp::parser parser{"123"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_TRUE(parser.check({'1', '|'}));
    EXPECT_EQ(1u, rdp::offset(parser));
    EXPECT_FALSE(parser.check({'|', '1'}));
    EXPECT_EQ(1u, rdp::offset(parser));
    EXPECT_TRUE(parser.check({'2', '5'}));
    EXPECT_EQ(2u, rdp::offset(parser));
    EXPECT_FALSE(parser.check({'5', '2'}));
    EXPECT_EQ(2u, rdp::offset(parser));
    EXPECT_TRUE(parser.check({'3', '4'}));
    EXPECT_EQ(3u, rdp::offset(parser));
    EXPECT_FALSE(parser.check({'4', '3'}));
    EXPECT_EQ(3u, rdp::offset(parser));
}

TEST(test_rdp, test_offset_skip)
{
    rdp::parser parser{"111122223333"};
    EXPECT_EQ(0u, rdp::offset(parser));
    parser.skip('2');
    EXPECT_EQ(0u, rdp::offset(parser));
    parser.skip('1');
    EXPECT_EQ(4u, rdp::offset(parser));
    parser.skip('1');
    EXPECT_EQ(4u, rdp::offset(parser));
    parser.skip('2');
    EXPECT_EQ(8u, rdp::offset(parser));
    parser.skip('3');
    EXPECT_EQ(12u, rdp::offset(parser));
}

TEST(test_rdp, test_offset_skip_multiple)
{
    rdp::parser parser{"11112222333344444555556666677777"};
    EXPECT_EQ(0u, rdp::offset(parser));
    parser.skip({'2', '3'});
    EXPECT_EQ(0u, rdp::offset(parser));
    parser.skip({'1', '2'});
    EXPECT_EQ(8u, rdp::offset(parser));
    parser.skip({'1', '2'});
    EXPECT_EQ(8u, rdp::offset(parser));
    parser.skip({'3', '4', '5', '7'});
    EXPECT_EQ(22u, rdp::offset(parser));
}

TEST(test_rdp, test_offset_skip_until)
{
    rdp::parser parser{"111122223333"};
    EXPECT_EQ(0u, rdp::offset(parser));
    parser.skip_until('1');
    EXPECT_EQ(0u, rdp::offset(parser));
    parser.skip_until('2');
    EXPECT_EQ(4u, rdp::offset(parser));
    parser.skip_until('2');
    EXPECT_EQ(4u, rdp::offset(parser));
    parser.skip_until('3');
    EXPECT_EQ(8u, rdp::offset(parser));
}

TEST(test_rdp, test_offset_skip_until_multiple)
{
    rdp::parser parser{"11112222333344444555556666677777"};
    EXPECT_EQ(0u, rdp::offset(parser));
    parser.skip_until({'1'});
    EXPECT_EQ(0u, rdp::offset(parser));
    parser.skip_until({'2', '3'});
    EXPECT_EQ(4u, rdp::offset(parser));
    parser.skip_until({'5', '6'});
    EXPECT_EQ(17u, rdp::offset(parser));
}

TEST(test_rdp, test_offset_match_until)
{
    rdp::parser parser{"111122223333"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_EQ("1111", parser.match_until('2').value());
    EXPECT_EQ(8u, parser.remaining_size());
    EXPECT_EQ("2222", parser.match_until('3').value());
    EXPECT_EQ(4u, parser.remaining_size());
    EXPECT_TRUE(parser.match_until('4').is_unmatched());
}

TEST(test_rdp, test_offset_match_until_with_eof)
{
    rdp::parser parser{"112233"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_TRUE(parser.match_until('4', rdp::eof_mode::fail).is_unmatched());
    EXPECT_EQ("112233", parser.match_until('4', rdp::eof_mode::match).value());
}

TEST(test_rdp, test_offset_match_until_multiple)
{
    rdp::parser parser{"11112,222|3333"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_EQ("1111", parser.match_until({'2', ','}).value());
    EXPECT_EQ(10u, parser.remaining_size());
    EXPECT_EQ("2", parser.match_until({'2', ','}).value());
    EXPECT_EQ(9u, parser.remaining_size());
    EXPECT_EQ(",222", parser.match_until({'3', '|'}).value());
    EXPECT_TRUE(parser.match_until('4').is_unmatched());
}

TEST(test_rdp, test_offset_match_until_multiple_with_eof)
{
    rdp::parser parser{"11|22,33"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_TRUE(parser.match_until({'4', '$'}, rdp::eof_mode::fail).is_unmatched());
    EXPECT_EQ("11|22,33", parser.match_until({'$', '4'}, rdp::eof_mode::match).value());
}

TEST(test_rdp, test_offset_match_until_string)
{
    rdp::parser parser{"112233abc123"};
    EXPECT_EQ("112233", parser.match_until("abc").value());
    EXPECT_EQ(6u, parser.remaining_size());
    EXPECT_EQ("abc1", parser.match_until("23").value());
    EXPECT_EQ(2u, parser.remaining_size());
}

TEST(test_rdp, test_offset_match_until_string_real_utf8)
{
    rdp::parser parser{u8"らき☆すた, Raki☆Suta"};

    // Unfortunately, these can not be put inside of an EXPECT_* since the macro is not
    // able to print the utf8 characters when it fails. This triggers a compiler warning.
    const bool result1 = (common::string_view{u8"らき"} == parser.match_until(u8"☆").value());
    EXPECT_TRUE(result1);

    const bool result2 = (common::string_view{u8"☆すた"} == parser.match_until(",").value());
    EXPECT_TRUE(result2);

    const bool result3 = (common::string_view{u8", Raki☆"} == parser.match_until("Suta").value());
    EXPECT_TRUE(result3);
}

TEST(test_rdp, test_offset_match_each)
{
    rdp::parser parser{"1213414adbdcacd55658758"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_TRUE(parser.match_each({'2', '3', '4'}).is_unmatched());

    EXPECT_EQ("1213414", parser.match_each({'1', '2', '3', '4'}).value());
    EXPECT_EQ("adbdcacd", parser.match_each({'a', 'b', 'c', 'd'}).value());
    EXPECT_TRUE(parser.match_each({'1', '2', '3', '4'}).is_unmatched());
    EXPECT_EQ("55658758", parser.match_each({'5', '6', '7', '8'}).value());
}

TEST(test_rdp, test_offset_match_pred)
{
    rdp::parser parser{"1234abcd5678"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_TRUE(parser.match([](const auto c) { return std::isalpha(c) != 0; }).is_unmatched());

    // TODO: A lambda cannot appear in an unevaluated context. Fix with C++20.
    EXPECT_EQ("1234", parser.match([](const auto c) { return std::isdigit(c) != 0; }).value());
    EXPECT_EQ("abcd", parser.match([](const auto c) { return std::isalpha(c) != 0; }).value());
    EXPECT_TRUE(parser.match([](const auto c) { return std::isalpha(c) != 0; }).is_unmatched());
    EXPECT_EQ("5678", parser.match([](const auto c) { return std::isdigit(c) != 0; }).value());
}

TEST(test_rdp, test_offset_match_pred_indexed)
{
    rdp::parser parser{"1a2b3c4d"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_TRUE(parser
                    .match_indexed(
                        [](const auto c, const auto i)
                        {
                            if (i % 2 == 0)
                                return std::isalpha(c) != 0;

                            return std::isdigit(c) != 0;
                        })
                    .is_unmatched());

    EXPECT_EQ("1a2b3c4d", parser
                              .match_indexed(
                                  [](const auto c, const auto i)
                                  {
                                      if (i % 2 == 0)
                                          return std::isdigit(c) != 0;

                                      return std::isalpha(c) != 0;
                                  })
                              .value());
}

TEST(test_rdp, test_offset_match_regex)
{
    rdp::parser parser{"111122223333aaaabbbbcccc1234"};
    EXPECT_EQ(0u, rdp::offset(parser));
    EXPECT_TRUE(match_regex(parser, "[a-zA-Z]+").is_unmatched());
    EXPECT_EQ("111122223333", match_regex(parser, "[1-3]+").value());
    EXPECT_TRUE(match_regex(parser, "[1-3]+").is_unmatched());
    EXPECT_EQ("aaaabbbbcccc", match_regex(parser, "[a-zA-Z]+").value());
    EXPECT_TRUE(match_regex(parser, "[a-zA-Z]+").is_unmatched());
    EXPECT_EQ("123", match_regex(parser, "[1-3]+").value());
    EXPECT_EQ("4", match_regex(parser, "[1-4]+").value());
    EXPECT_TRUE(match_regex(parser, ".*").is_unmatched());
}

TEST(test_rdp, test_offset_match_regex_empty_sequence)
{
    rdp::parser parser{"111122223333aaaabbbbcccc1234"};
    EXPECT_TRUE(match_regex(parser, "[a-zA-Z]*").is_unmatched());
}

TEST(test_rdp, test_offset_match_advanced)
{
    rdp::parser parser{"Validvariable123 somethingElse {}"};
    rdp::parser parser2{"123Inalidvariable123 Hello {}"};
    rdp::parser parser3{"__123Validvariable123 123 {}"};
    EXPECT_EQ("Validvariable123", match_regex(parser, "[a-zA-Z_][a-zA-Z0-9\\-_]*").value());
    EXPECT_TRUE(match_regex(parser2, "[a-zA-Z][a-zA-Z0-9\\-_]*").is_unmatched());
    EXPECT_EQ("__123Validvariable123", match_regex(parser3, "[a-zA-Z_][a-zA-Z0-9\\-_]*").value());
}

void check_parse_decimal_signed(const common::string_view str, const std::int64_t expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_decimal_signed(parser));
}

TEST(test_rdp, test_parse_decimal_signed)
{
    check_parse_decimal_signed("-12", -12);
    check_parse_decimal_signed("12", 12);
    check_parse_decimal_signed("-1234", -1234);
    check_parse_decimal_signed("1234", 1234);
    check_parse_decimal_signed("-123456", -123456);
    check_parse_decimal_signed("123456", 123456);
    check_parse_decimal_signed("-123456789", -123456789);
    check_parse_decimal_signed("123456789", 123456789);
}

void check_parse_decimal_unsigned(const common::string_view str, const std::uint64_t expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_decimal_unsigned(parser));
}

TEST(test_rdp, test_parse_decimal_unsigned)
{
    check_parse_decimal_unsigned("12", 12);
    check_parse_decimal_unsigned("1234", 1234);
    check_parse_decimal_unsigned("123456", 123456);
    check_parse_decimal_unsigned("123456789", 123456789);
}

void check_parse_binary(const common::string_view str, const std::uint64_t expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_binary(parser));
}

TEST(test_rdp, test_parse_binary)
{
    check_parse_binary("1010", 10);
    check_parse_binary("1001001011010101", 37589);
    check_parse_binary("10101001010001101001001011010101", 2839974613);
    check_parse_binary("100010001001100010100100101010010101001010001101001001011010101", 4921399016379814613);
}

void check_parse_binary_prefixed(const common::string_view str, const std::uint64_t expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_binary(parser, "0b"));
}

TEST(test_rdp, test_parse_binary_prefixed)
{
    check_parse_binary_prefixed("0b1010", 10);
    check_parse_binary_prefixed("0b1001001011010101", 37589);
    check_parse_binary_prefixed("0b10101001010001101001001011010101", 2839974613);
    check_parse_binary_prefixed("0b100010001001100010100100101010010101001010001101001001011010101",
                                4921399016379814613u);
}

void check_parse_hex(const common::string_view str, const std::uint64_t expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_hexadecimal(parser));
}

TEST(test_rdp, test_parse_hexadecimal)
{
    check_parse_hex("BD", 189);
    check_parse_hex("BD74", 48500);
    check_parse_hex("F1DA85FC", 4057630204);
    check_parse_hex("57DB41EA587DB4FC", 6330726175962150140u);
}

void check_parse_hex_prefixed(const common::string_view str, const std::uint64_t expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_hexadecimal(parser, "0x"));
}

TEST(test_rdp, test_parse_hexadecimal_prefixed)
{
    check_parse_hex_prefixed("0xBD", 189);
    check_parse_hex_prefixed("0xBD74", 48500);
    check_parse_hex_prefixed("0xF1DA85FC", 4057630204);
    check_parse_hex_prefixed("0x57DB41EA587DB4FC", 6330726175962150140u);
}

void check_skip_byte_order_marker(const common::string_view str, const common::string_view expected)
{
    rdp::parser parser{str};
    rdp::skip_byte_order_marker(parser);
    EXPECT_TRUE(parser.check(expected));
}

TEST(test_rdp, test_skip_byte_order_marker)
{
    check_skip_byte_order_marker("Hello", "Hello");
    check_skip_byte_order_marker(common::bom::utf8::string() + "Hello", "Hello");
}
