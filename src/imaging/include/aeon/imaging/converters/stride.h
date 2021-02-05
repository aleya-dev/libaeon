// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/exceptions.h>

namespace aeon::imaging::convert
{

namespace detail
{

template <typename T>
struct remove_stride_impl
{
    static auto process(const image_view<T> &img) -> image<T>
    {
        const image_descriptor<T> d{width(img), height(img)};
        image<T> new_image{d};

        const auto src_data = img.template data<std::uint8_t>();
        const auto dst_data = new_image.template data<std::uint8_t>();

        for (auto y = 0; y < height(img); ++y)
        {
            const auto offset = y * stride(img);
            const auto src_scanline = &src_data[offset];
            const auto src_scanline_end = &src_data[offset + width(img) * sizeof(T)];

            const auto dst_offset = y * stride(new_image);
            const auto dst_scanline = &dst_data[dst_offset];

            std::copy(src_scanline, src_scanline_end, dst_scanline);
        }

        return new_image;
    }
};

} // namespace detail

template <typename T>
[[nodiscard]] inline auto remove_stride(const image_view<T> &img) -> image<T>
{
    return detail::remove_stride_impl<T>::process(img);
}

[[nodiscard]] inline auto remove_stride(const dynamic_image &img) -> dynamic_image
{
    return process_image_to_copy<detail::remove_stride_impl>(img);
}

} // namespace aeon::imaging::convert
