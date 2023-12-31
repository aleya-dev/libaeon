// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/streams/devices/device.h>
#include <aeon/streams/seek_direction.h>
#include <aeon/streams/tags.h>
#include <span>
#include <algorithm>
#include <ios>

namespace aeon::streams
{

template <typename T>
class span_device : public device
{
public:
    using value_type = T;

    struct category : input_tag, input_seekable_tag, output_tag, output_seekable_tag, has_eof_tag, has_size_tag
    {
    };

    explicit span_device(std::span<T> span) noexcept;

    span_device(span_device &&) noexcept = default;
    auto operator=(span_device &&) noexcept -> span_device & = default;

    span_device(const span_device &) noexcept = default;
    auto operator=(const span_device &) noexcept -> span_device & = default;

    ~span_device() = default;

    auto write(const std::byte *data, const std::streamsize size) noexcept -> std::streamsize;

    auto read(std::byte *data, const std::streamsize size) noexcept -> std::streamsize;

    auto seekg(const std::streamoff offset, const seek_direction direction) noexcept -> bool;

    [[nodiscard]] auto tellg() const noexcept -> std::streamoff;

    auto seekp(const std::streamoff offset, const seek_direction direction) noexcept -> bool;

    [[nodiscard]] auto tellp() const noexcept -> std::streamoff;

    [[nodiscard]] auto eof() const noexcept -> bool;

    [[nodiscard]] auto size() const noexcept -> std::streamoff;

    [[nodiscard]] auto get_span() const noexcept -> const std::span<T> &;

    void set_span(std::span<T> span) noexcept;

protected:
    std::span<T> span_;
    std::streamoff read_idx_;
    std::streamoff write_idx_;
};

template <typename T>
inline span_device<T>::span_device(std::span<T> span) noexcept
    : span_{std::move(span)}
    , read_idx_{0}
    , write_idx_{0}
{
}

template <typename T>
inline auto span_device<T>::write(const std::byte *data, const std::streamsize size) noexcept -> std::streamsize
{
    const auto actual_size = std::min(size, static_cast<std::streamsize>(std::size(span_) - write_idx_));

    if (actual_size == 0)
        return 0;

    const auto *src_data = reinterpret_cast<const value_type *>(data);
    std::copy(src_data, src_data + actual_size, span_.data() + write_idx_);
    write_idx_ += actual_size;
    return actual_size;
}

template <typename T>
inline auto span_device<T>::read(std::byte *data, const std::streamsize size) noexcept -> std::streamsize
{
    const auto actual_size = std::min(size, static_cast<std::streamsize>(std::size(span_) - read_idx_));

    if (actual_size == 0)
        return 0;

    auto *dst_data = reinterpret_cast<value_type *>(data);
    std::copy(span_.data() + read_idx_, span_.data() + read_idx_ + actual_size, dst_data);
    read_idx_ += actual_size;
    return actual_size;
}

template <typename T>
inline auto span_device<T>::seekg(const std::streamoff offset, const seek_direction direction) noexcept -> bool
{
    std::streamoff idx = 0;
    switch (direction)
    {
        case seek_direction::begin:
        {
            idx = offset;
        }
        break;
        case seek_direction::current:
        {
            idx = read_idx_ + offset;
        }
        break;
        case seek_direction::end:
        {
            idx = (std::ssize(span_) - 1) - offset;
        }
        break;
    }

    if (idx < 0 || idx >= std::ssize(span_))
        return false;

    read_idx_ = idx;
    return true;
}

template <typename T>
[[nodiscard]] inline auto span_device<T>::tellg() const noexcept -> std::streamoff
{
    return read_idx_;
}

template <typename T>
inline auto span_device<T>::seekp(const std::streamoff offset, const seek_direction direction) noexcept -> bool
{
    std::streamoff idx = 0;
    switch (direction)
    {
        case seek_direction::begin:
        {
            idx = offset;
        }
        break;
        case seek_direction::current:
        {
            idx = read_idx_ + offset;
        }
        break;
        case seek_direction::end:
        {
            idx = (std::ssize(span_) - 1) - offset;
        }
        break;
    }

    if (idx < 0 || idx >= std::ssize(span_))
        return false;

    write_idx_ = idx;
    return true;
}

template <typename T>
[[nodiscard]] inline auto span_device<T>::tellp() const noexcept -> std::streamoff
{
    return write_idx_;
}

template <typename T>
[[nodiscard]] inline auto span_device<T>::eof() const noexcept -> bool
{
    return read_idx_ >= std::ssize(span_);
}

template <typename T>
[[nodiscard]] inline auto span_device<T>::size() const noexcept -> std::streamoff
{
    return std::ssize(span_);
}

template <typename T>
[[nodiscard]] inline auto span_device<T>::get_span() const noexcept -> const std::span<T> &
{
    return span_;
}

template <typename T>
inline void span_device<T>::set_span(std::span<T> span) noexcept
{
    span_ = std::move(span);
}

} // namespace aeon::streams
