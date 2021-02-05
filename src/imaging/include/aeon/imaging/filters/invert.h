// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/imaging/image_view.h>

namespace aeon::imaging::filters
{

namespace detail
{

template <typename T>
struct invert_horizontally_impl
{
    static auto process(const image_view<T> &img) -> image<T>
    {
        const auto w = width(img);
        const auto h = height(img);

        image<T> new_image(descriptor(img));

        for (auto y = 0; y < h; ++y)
        {
            for (auto x = 0; x < w; ++x)
            {
                const auto pixel_offset = img.template data<std::uint8_t>({x, y});
                const auto new_pixel_offset = new_image.template data<std::uint8_t>({w - x - 1, y});

                for (auto offset = 0u; offset < sizeof(T); ++offset)
                    *(new_pixel_offset + offset) = *(pixel_offset + offset);
            }
        }

        return new_image;
    }
};

template <typename T>
struct invert_vertically_impl
{
    static auto process(const image_view<T> &img) -> image<T>
    {
        aeon_assert(continuous(img), "invert_vertically only works on continuous images.");

        image<T> new_image(descriptor(img));

        const auto src_data = img.template data<std::uint8_t>();
        const auto dst_data = new_image.template data<std::uint8_t>();

        for (auto y = 0; y < height(img); ++y)
        {
            const auto offset = y * stride(img);
            const auto src_scanline = &src_data[offset];
            const auto src_scanline_end = &src_data[offset + width(img) * sizeof(T)];

            const auto dst_offset = (static_cast<std::ptrdiff_t>(height(img)) - y - 1) * stride(new_image);
            const auto dst_scanline = &dst_data[dst_offset];

            std::copy(src_scanline, src_scanline_end, dst_scanline);
        }

        return new_image;
    }
};

} // namespace detail

template <typename T>
[[nodiscard]] inline auto invert_horizontally(const image_view<T> &img) -> image<T>
{
    return detail::invert_horizontally_impl<T>::process(img);
}

[[nodiscard]] inline auto invert_horizontally(const dynamic_image &img) -> dynamic_image
{
    return process_image_to_copy<detail::invert_horizontally_impl>(img);
}

template <typename T>
[[nodiscard]] inline auto invert_vertically(const image_view<T> &img) -> image<T>
{
    return detail::invert_vertically_impl<T>::process(img);
}

[[nodiscard]] inline auto invert_vertically(const dynamic_image &img) -> dynamic_image
{
    return process_image_to_copy<detail::invert_horizontally_impl>(img);
}

} // namespace aeon::imaging::filters
