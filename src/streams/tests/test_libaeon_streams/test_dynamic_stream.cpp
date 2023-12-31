// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/dynamic_stream.h>
#include <gtest/gtest.h>
#include <cstring>
#include <array>

using namespace aeon;

TEST(test_streams, test_streams_dynamic_stream_create)
{
    auto dynamic_device = streams::make_dynamic_stream(streams::memory_device<std::vector<char>>{});
    dynamic_device.write(reinterpret_cast<const std::byte *>("12345"), 5);

    EXPECT_TRUE(dynamic_device.is_input());
    EXPECT_TRUE(dynamic_device.is_input_seekable());
    EXPECT_TRUE(dynamic_device.is_output());
    EXPECT_TRUE(dynamic_device.is_output_seekable());
    EXPECT_FALSE(dynamic_device.has_status());
    EXPECT_TRUE(dynamic_device.has_eof());
    EXPECT_FALSE(dynamic_device.is_flushable());

    std::array<std::byte, 5> read;
    ASSERT_EQ(5, dynamic_device.read(std::data(read), std::ssize(read)));
    EXPECT_EQ(0, std::memcmp("12345", std::data(read), std::ssize(read)));
}

TEST(test_streams, test_streams_dynamic_stream_create_ptr)
{
    auto dynamic_device = streams::make_dynamic_stream_ptr(streams::memory_device<std::vector<char>>{});
    dynamic_device->write(reinterpret_cast<const std::byte *>("12345"), 5);

    EXPECT_TRUE(dynamic_device->is_input());
    EXPECT_TRUE(dynamic_device->is_input_seekable());
    EXPECT_TRUE(dynamic_device->is_output());
    EXPECT_TRUE(dynamic_device->is_output_seekable());
    EXPECT_FALSE(dynamic_device->has_status());
    EXPECT_TRUE(dynamic_device->has_eof());
    EXPECT_FALSE(dynamic_device->is_flushable());

    std::array<std::byte, 5> read;
    ASSERT_EQ(5, dynamic_device->read(std::data(read), std::ssize(read)));
    EXPECT_EQ(0, std::memcmp("12345", std::data(read), std::ssize(read)));
}
