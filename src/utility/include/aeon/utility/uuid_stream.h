// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/common/uuid.h>

template <typename device_t>
inline auto operator<<(aeon::streams::stream_writer<device_t> &stream, const aeon::common::uuid &val)
{
    const auto size = static_cast<std::streamsize>(val.size());

    if (stream.device().write(reinterpret_cast<const char *>(val.data.data()), size) != size)
        throw aeon::streams::stream_exception{};

    return stream;
}

template <typename device_t>
inline auto operator>>(aeon::streams::stream_reader<device_t> &stream, aeon::common::uuid &val)
{
    const auto size = static_cast<std::streamsize>(val.size());

    if (stream.device().read(reinterpret_cast<char *>(val.data.data()), size) != size)
        throw aeon::streams::stream_exception{};

    return stream;
}
