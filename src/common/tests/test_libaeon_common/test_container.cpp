// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/container.h>
#include <aeon/common/string.h>
#include <gtest/gtest.h>
#include <array>

using namespace aeon;
using namespace std::string_literals;

TEST(test_container, test_transform_string_to_char_ptr)
{
    const std::vector<Common::String> data{"Hello", "1234", "testing"};
    const auto dataPtr = Common::Container::Transform<const char *>(data, [](const auto &str) { return str.CStr(); });
    ASSERT_EQ(std::size(data), std::size(dataPtr));

    EXPECT_EQ(Common::StringView{dataPtr.at(0)}, "Hello");
    EXPECT_EQ(Common::StringView{dataPtr.at(1)}, "1234");
    EXPECT_EQ(Common::StringView{dataPtr.at(2)}, "testing");
}

TEST(test_container, test_adjacent_execute)
{
    std::array data{1, 2, 3, 4, 5, 6, 7, 8};
    Common::Container::AdjacentExecute(std::begin(data), std::end(data),
                                        [](const auto first, const auto second)
                                        {
                                            EXPECT_EQ(1, second - first);
                                            return true;
                                        });
}

TEST(test_container, test_contains_int)
{
    std::array data{1, 2, 3, 4, 5, 6, 7, 8};
    EXPECT_TRUE(Common::Container::Contains(std::begin(data), std::end(data), 1));
    EXPECT_TRUE(Common::Container::Contains(std::begin(data), std::end(data), 5));
    EXPECT_TRUE(Common::Container::Contains(std::begin(data), std::end(data), 8));

    EXPECT_FALSE(Common::Container::Contains(std::begin(data), std::end(data), 9));
    EXPECT_FALSE(Common::Container::Contains(std::begin(data), std::end(data), -1));
    EXPECT_FALSE(Common::Container::Contains(std::begin(data), std::end(data), 1337));
}

TEST(test_container, test_contains_string)
{
    std::array data{"1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s};
    EXPECT_TRUE(Common::Container::Contains(std::begin(data), std::end(data), "1"s));
    EXPECT_TRUE(Common::Container::Contains(std::begin(data), std::end(data), "5"s));
    EXPECT_TRUE(Common::Container::Contains(std::begin(data), std::end(data), "8"s));

    EXPECT_FALSE(Common::Container::Contains(std::begin(data), std::end(data), "9"s));
    EXPECT_FALSE(Common::Container::Contains(std::begin(data), std::end(data), "-1"s));
    EXPECT_FALSE(Common::Container::Contains(std::begin(data), std::end(data), "1337"s));
    EXPECT_FALSE(Common::Container::Contains(std::begin(data), std::end(data), "one"s));
}
