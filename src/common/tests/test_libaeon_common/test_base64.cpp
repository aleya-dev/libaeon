// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/base64.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_bits, test_base64_encode)
{
    EXPECT_EQ(Common::Base64::Encode(""), "");
    EXPECT_EQ(Common::Base64::Encode(" "), "IA==");
    EXPECT_EQ(Common::Base64::Encode("  "), "ICA=");
    EXPECT_EQ(Common::Base64::Encode("   "), "ICAg");
    EXPECT_EQ(Common::Base64::Encode("This is a test"), "VGhpcyBpcyBhIHRlc3Q=");
}

void check_decode(const Common::StringView input)
{
    const auto result = Common::Base64::Encode(input);
    EXPECT_EQ(Common::Base64::DecodeString(result), input);
}

TEST(test_bits, test_base64_decode)
{
    check_decode("");
    check_decode(" ");
    check_decode("  ");
    check_decode("   ");
    check_decode("This is a test");
}
