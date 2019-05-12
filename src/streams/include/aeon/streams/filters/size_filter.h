// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/filters/filter.h>
#include <aeon/streams/stream_traits.h>
#include <aeon/streams/tags.h>
#include <iostream>
#include <algorithm>

namespace aeon::streams
{

template <std::streamoff max_size = 0>
class size_filter : public filter
{
public:
    struct category : has_size
    {
    };

    explicit size_filter() = default;
    ~size_filter() = default;

    size_filter(size_filter &&) noexcept = default;
    auto operator=(size_filter &&) noexcept -> size_filter & = default;

    size_filter(const size_filter &) noexcept = default;
    auto operator=(const size_filter &) noexcept -> size_filter & = default;

    template <typename source_t>
    [[nodiscard]] auto size(source_t &source) const noexcept -> std::streamoff
    {
        if constexpr (has_size_v<source_t>)
            return std::min(source.size(), max_size);
        else
            return max_size;
    }
};

} // namespace aeon::streams