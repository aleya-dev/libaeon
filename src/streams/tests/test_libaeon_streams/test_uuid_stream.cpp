// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/uuid.h>
#include <aeon/streams/uuid_stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_uuid_stream, test_write_to_stream)
{
    auto Uuid = Common::Uuid::Generate();

    streams::memory_device<std::vector<char>> memstream;
    streams::stream_writer writer{memstream};

    writer << Uuid;

    ASSERT_EQ(static_cast<std::streamoff>(Uuid.Size()), memstream.size());
}

TEST(test_uuid_stream, test_read_from_stream)
{
    auto Uuid = Common::Uuid::Generate();

    streams::memory_device<std::vector<char>> memstream;
    memstream.write(reinterpret_cast<const std::byte *>(Uuid.Data.data()), Uuid.Size());

    streams::stream_reader reader(memstream);

    Common::Uuid uuid2;
    reader >> uuid2;

    ASSERT_EQ(Uuid, uuid2);
}
