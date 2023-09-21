// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/color.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_color, test_color_rgb_default_u8)
{
    const Common::ColorRgbU color;
    EXPECT_EQ(0, color.R);
    EXPECT_EQ(0, color.G);
    EXPECT_EQ(0, color.B);
}

TEST(test_color, test_color_rgb_default_float)
{
    const Common::ColorRgbF color;
    EXPECT_EQ(0.0f, color.R);
    EXPECT_EQ(0.0f, color.G);
    EXPECT_EQ(0.0f, color.B);
}

TEST(test_color, test_color_rgb_default_double)
{
    const Common::ColorRgbD color;
    EXPECT_EQ(0.0, color.R);
    EXPECT_EQ(0.0, color.G);
    EXPECT_EQ(0.0, color.B);
}

TEST(test_color, test_color_rgba_default_u8)
{
    const Common::ColorRgbaU color;
    EXPECT_EQ(0, color.R);
    EXPECT_EQ(0, color.G);
    EXPECT_EQ(0, color.B);
    EXPECT_EQ(255, color.A);
}

TEST(test_color, test_color_rgba_default_float)
{
    const Common::ColorRgbaF color;
    EXPECT_EQ(0.0f, color.R);
    EXPECT_EQ(0.0f, color.G);
    EXPECT_EQ(0.0f, color.B);
    EXPECT_EQ(1.0f, color.A);
}

TEST(test_color, test_color_rgba_default_double)
{
    const Common::ColorRgbaD color;
    EXPECT_EQ(0.0, color.R);
    EXPECT_EQ(0.0, color.G);
    EXPECT_EQ(0.0, color.B);
    EXPECT_EQ(1.0, color.A);
}

TEST(test_color, test_color_rgba_from_rgb_u8)
{
    const Common::ColorRgbU ColorRgb{10, 20, 30};
    const Common::ColorRgbaU color{ColorRgb, 40};
    EXPECT_EQ(10, color.R);
    EXPECT_EQ(20, color.G);
    EXPECT_EQ(30, color.B);
    EXPECT_EQ(40, color.A);
}

TEST(test_color, test_color_rgba_from_rgb_float)
{
    const Common::ColorRgbF ColorRgb{10.0f, 20.0f, 30.0f};
    const Common::ColorRgbaF color{ColorRgb, 40.0f};
    EXPECT_EQ(10.0f, color.R);
    EXPECT_EQ(20.0f, color.G);
    EXPECT_EQ(30.0f, color.B);
    EXPECT_EQ(40.0f, color.A);
}

TEST(test_color, test_color_rgba_from_rgb_double)
{
    const Common::ColorRgbD ColorRgb{10.0, 20.0, 30.0};
    const Common::ColorRgbaD color{ColorRgb, 40.0};
    EXPECT_EQ(10.0, color.R);
    EXPECT_EQ(20.0, color.G);
    EXPECT_EQ(30.0, color.B);
    EXPECT_EQ(40.0, color.A);
}

TEST(test_color, test_color_rgba_double_from_rgba_u8)
{
    const Common::ColorRgbaU color{128, 255, 64, 32};
    const Common::ColorRgbaD color_dbl{color};
    EXPECT_NEAR(0.5, color_dbl.R, 0.005);
    EXPECT_NEAR(1.0, color_dbl.G, 0.005);
    EXPECT_NEAR(0.25, color_dbl.B, 0.005);
    EXPECT_NEAR(0.125, color_dbl.A, 0.005);

    const Common::ColorRgbaU color_u8{color_dbl};
    EXPECT_EQ(color, color_u8);
}
