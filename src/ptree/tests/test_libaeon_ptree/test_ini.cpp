// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/serialization_ini.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/common/string_utils.h>
#include <gtest/gtest.h>

#include <ptree_unittest_data.h>

using namespace aeon;

static const ptree::property_tree ini_test_pt{
    {{"header1", ptree::object{{"value1", 100}, {"value2", 10.0}, {"value3", false}, {"value4", true}}},
     {"header2", ptree::object{{"value_a", 200},
                               {"value_b", 15.0},
                               {"value_c", Common::Uuid::Parse("f976d1e3-0f0d-4c9c-b7c5-2e31eb4bae89")},
                               {"value_d", "This is a string test."}}},
     {"header3", ptree::object{{"value1", "This is a string value"},
                               {"value2", "This is a string value"},
                               {"value3", "This is a string value"},
                               {"value4", "This is a string value"}}}}};

TEST(test_ptree, serialize_ini)
{
    const auto str = ptree::serialization::to_ini(ini_test_pt);

    streams::file_source_device stream{AEON_PTREE_UNITTEST_DATA_PATH "serialize_expect.ini"};
    streams::stream_reader reader{stream};

    // Strip all \r's to workaround git's auto line-endings on windows
    auto expected = reader.read_to_string();
    Common::String expected_str = expected;
    Common::StringUtils::Replace(expected_str, "\r", "");

    EXPECT_EQ(expected_str.Str(), str);
}

TEST(test_ptree, serialize_deserialize_compare_ini)
{
    const auto str = ptree::serialization::to_ini(ini_test_pt);
    const auto result = ptree::serialization::from_ini(str);

    EXPECT_EQ(result, ini_test_pt);
}

TEST(test_ptree, deserialize_ini)
{
    auto stream = streams::make_dynamic_stream(streams::file_source_device{AEON_PTREE_UNITTEST_DATA_PATH "simple.ini"});
    const auto result = ptree::serialization::from_ini(stream);

    const auto &headers = result.object_value();
    EXPECT_EQ(2u, headers.Size());
    EXPECT_TRUE(headers.Contains("header1"));
    EXPECT_TRUE(headers.Contains("another_header"));

    const auto &header1 = headers.At("header1").object_value();
    EXPECT_EQ(7u, header1.Size());
    EXPECT_EQ(42, header1.At("value").integer_value());
    EXPECT_EQ(false, header1.At("another_value").bool_value());
    EXPECT_EQ(true, header1.At("another_bool").bool_value());
    EXPECT_EQ("This is a string", header1.At("string").string_value());
    EXPECT_EQ(1.0, header1.At("value2").double_value());
    EXPECT_EQ(42e-1, header1.At("value3").double_value());
    EXPECT_EQ(-10, header1.At("value4").integer_value());

    const auto &another_header = headers.At("another_header").object_value();
    EXPECT_EQ(2u, another_header.Size());
    EXPECT_EQ(1337, another_header.At("val").integer_value());
    EXPECT_EQ(Common::Uuid::Parse("f976d1e3-0f0d-4c9c-b7c5-2e31eb4bae89"),
              another_header.At("uuid_value").uuid_value());
}
