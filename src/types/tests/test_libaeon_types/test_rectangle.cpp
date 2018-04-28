/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <gtest/gtest.h>
#include <aeon/types/rectangle.h>

using namespace aeon;

TEST(test_rectangle, test_rectangle_default_int)
{
    const types::rectangle<int> rect;

    EXPECT_EQ(types::left(rect), 0);
    EXPECT_EQ(types::top(rect), 0);
    EXPECT_EQ(types::right(rect), 0);
    EXPECT_EQ(types::bottom(rect), 0);

    EXPECT_EQ(types::width(rect), 0);
    EXPECT_EQ(types::height(rect), 0);

    EXPECT_TRUE(types::empty(rect));
    EXPECT_EQ(types::size(rect), types::size2d<int>{});
}

TEST(test_rectangle, test_rectangle_default_float)
{
    const types::rectangle<float> rect;

    EXPECT_EQ(types::left(rect), 0.0f);
    EXPECT_EQ(types::top(rect), 0.0f);
    EXPECT_EQ(types::right(rect), 0.0f);
    EXPECT_EQ(types::bottom(rect), 0.0f);

    EXPECT_EQ(types::width(rect), 0.0f);
    EXPECT_EQ(types::height(rect), 0.0f);

    EXPECT_TRUE(types::empty(rect));
    EXPECT_EQ(types::size(rect), types::size2d<float>{});
}

TEST(test_rectangle, test_rectangle_width_height)
{
    const types::rectangle<int> rect{0, 0, 10, 20};

    EXPECT_EQ(types::width(rect), 10);
    EXPECT_EQ(types::height(rect), 20);

    EXPECT_EQ(types::size(rect), types::size2d<int>(10, 20));
}

TEST(test_rectangle, test_rectangle_translate_positive)
{
    const types::rectangle<int> rect{5, 10, 15, 20};
    const auto new_rect = types::translate(rect, 10, 20);

    EXPECT_EQ(types::left(new_rect), 15);
    EXPECT_EQ(types::top(new_rect), 30);
    EXPECT_EQ(types::right(new_rect), 25);
    EXPECT_EQ(types::bottom(new_rect), 40);

    EXPECT_EQ(types::width(new_rect), types::width(rect));
    EXPECT_EQ(types::height(new_rect), types::height(rect));

    EXPECT_EQ(types::size(new_rect), types::size(rect));
}

TEST(test_rectangle, test_rectangle_translate_positive_vector2)
{
    const types::rectangle<int> rect{5, 10, 15, 20};
    const math::vector2<int> translation_vec{10, 20};

    const auto new_rect = types::translate(rect, translation_vec);

    EXPECT_EQ(types::left(new_rect), 15);
    EXPECT_EQ(types::top(new_rect), 30);
    EXPECT_EQ(types::right(new_rect), 25);
    EXPECT_EQ(types::bottom(new_rect), 40);

    EXPECT_EQ(types::width(new_rect), types::width(rect));
    EXPECT_EQ(types::height(new_rect), types::height(rect));

    EXPECT_EQ(types::size(new_rect), types::size(rect));
}