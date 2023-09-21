// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/math/mat.h>

namespace aeon::imaging
{

inline image::image() noexcept
    : image_view{}
    , data_{}
{
}

inline image::image(const Common::ElementType type, const imaging::format format,
                    const math::size2d<dimensions_type> dimensions) noexcept
    : image_view{type, format, dimensions, nullptr}
    , data_(math::width(dimensions) * type.Stride * math::height(dimensions))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const Common::ElementType type, const imaging::format format, const dimensions_type width,
                    const dimensions_type height) noexcept
    : image_view{type, format, width, height, nullptr}
    , data_(width * type.Stride * height)
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const Common::ElementType type, const imaging::format format,
                    const math::size2d<dimensions_type> dimensions, const stride_type stride) noexcept
    : image_view{type, format, dimensions, stride, nullptr}
    , data_(stride * math::height(dimensions))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const Common::ElementType type, const imaging::format format, const dimensions_type width,
                    const dimensions_type height, const stride_type stride) noexcept
    : image_view{type, format, width, height, stride, nullptr}
    , data_(stride * height)
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const Common::ElementType type, const imaging::format format,
                    const math::size2d<dimensions_type> dimensions, std::vector<underlying_type> data) noexcept
    : image_view{type, format, dimensions, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const Common::ElementType type, const imaging::format format, const dimensions_type width,
                    const dimensions_type height, std::vector<underlying_type> data) noexcept
    : image_view{type, format, width, height, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const Common::ElementType type, const imaging::format format,
                    const math::size2d<dimensions_type> dimensions, const stride_type stride,
                    std::vector<underlying_type> data) noexcept
    : image_view{type, format, dimensions, stride, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const Common::ElementType type, const imaging::format format, const dimensions_type width,
                    const dimensions_type height, const stride_type stride, std::vector<underlying_type> data) noexcept
    : image_view{type, format, width, height, stride, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const Common::ElementType type, const imaging::format format,
                    const math::size2d<dimensions_type> dimensions, const underlying_type *data)
    : image_view{type, format, dimensions, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline image::image(const Common::ElementType type, const imaging::format format, const dimensions_type width,
                    const dimensions_type height, const underlying_type *data)
    : image_view{type, format, width, height, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline image::image(const Common::ElementType type, const imaging::format format,
                    const math::size2d<dimensions_type> dimensions, const stride_type stride,
                    const underlying_type *data)
    : image_view{type, format, dimensions, stride, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline image::image(const Common::ElementType type, const imaging::format format, const dimensions_type width,
                    const dimensions_type height, const stride_type stride, const underlying_type *data)
    : image_view{type, format, width, height, stride, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline image::image(const image_view &view)
    : image_view{math::ElementType(view), imaging::pixel_format(view), math::dimensions(view), math::stride(view),
                 nullptr}
    , data_{}
{
    copy_from_pointer(std::data(view));
}

inline image::image(const imaging::format format, const math::size2d<dimensions_type> dimensions) noexcept
    : image{to_element_type(format), format, dimensions}
{
}

inline image::image(const imaging::format format, const dimensions_type width, const dimensions_type height) noexcept
    : image{to_element_type(format), format, width, height}
{
}

inline image::image(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                    const stride_type stride) noexcept
    : image{to_element_type(format), format, dimensions, stride}
{
}

inline image::image(const imaging::format format, const dimensions_type width, const dimensions_type height,
                    const stride_type stride) noexcept
    : image{to_element_type(format), format, width, height, stride}
{
}

inline image::image(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                    std::vector<underlying_type> data) noexcept
    : image{to_element_type(format), format, dimensions, data}
{
}

inline image::image(const imaging::format format, const dimensions_type width, const dimensions_type height,
                    std::vector<underlying_type> data) noexcept
    : image{to_element_type(format), format, width, height, data}
{
}

inline image::image(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                    const stride_type stride, std::vector<underlying_type> data) noexcept
    : image{to_element_type(format), format, dimensions, stride, data}
{
}

inline image::image(const imaging::format format, const dimensions_type width, const dimensions_type height,
                    const stride_type stride, std::vector<underlying_type> data) noexcept
    : image{to_element_type(format), format, width, height, stride, data}
{
}

inline image::image(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                    const underlying_type *data)
    : image{to_element_type(format), format, dimensions, data}
{
}

inline image::image(const imaging::format format, const dimensions_type width, const dimensions_type height,
                    const underlying_type *data)
    : image{to_element_type(format), format, width, height, data}
{
}

inline image::image(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                    const stride_type stride, const underlying_type *data)
    : image{to_element_type(format), format, dimensions, stride, data}
{
}

inline image::image(const imaging::format format, const dimensions_type width, const dimensions_type height,
                    const stride_type stride, const underlying_type *data)
    : image{to_element_type(format), format, width, height, stride, data}
{
}

inline auto image::clone() const -> image
{
    return image{type_, format_, dimensions_, stride_, data_};
}

inline void image::clear() noexcept
{
    format_ = format::undefined;
    type_ = {};
    data_ptr_ = nullptr;
    dimensions_ = {};
    stride_ = 0;

    // Force data deletion. Clear does not guarantee deallocation.
    decltype(data_)().swap(data_);
}

inline void image::copy_from_pointer(const underlying_type *data)
{
    const auto size = mat_view::size();
    data_.resize(size);
    mat_view::data_ptr_ = std::data(data_);
    std::copy_n(data, size, std::begin(data_));
}

template <math::swizzle_component... components>
[[nodiscard]] inline auto swizzle_copy(const image_view &view) noexcept -> image
{
    return swizzle_copy(view, pixel_format(view));
}

template <math::swizzle_component... components>
[[nodiscard]] inline auto swizzle_copy(const image_view &view, const format format) noexcept -> image
{
    // Currently strides are not supported. They may be in the future.
    if (!view.ElementType().Continuous() || !math::continuous(view))
        std::abort();

    if (view.ElementType().IsUndefined())
        std::abort();

    auto new_element_type = view.ElementType();
    new_element_type.Count = sizeof...(components);
    new_element_type.Size = new_element_type.ComponentSize * new_element_type.Count;
    new_element_type.Stride = new_element_type.Size;

    image new_image{new_element_type, format, dimensions(view)};

    switch (view.ElementType().Name)
    {
        case Common::ElementTypeName::U8:
            math::internal::swizzle_copy<std::uint8_t, image, components...>(view, new_image);
            break;
        case Common::ElementTypeName::S8:
            math::internal::swizzle_copy<std::int8_t, image, components...>(view, new_image);
            break;
        case Common::ElementTypeName::U16:
            math::internal::swizzle_copy<std::uint16_t, image, components...>(view, new_image);
            break;
        case Common::ElementTypeName::S16:
            math::internal::swizzle_copy<std::int16_t, image, components...>(view, new_image);
            break;
        case Common::ElementTypeName::U32:
            math::internal::swizzle_copy<std::uint32_t, image, components...>(view, new_image);
            break;
        case Common::ElementTypeName::S32:
            math::internal::swizzle_copy<std::int32_t, image, components...>(view, new_image);
            break;
        case Common::ElementTypeName::U64:
            math::internal::swizzle_copy<std::uint64_t, image, components...>(view, new_image);
            break;
        case Common::ElementTypeName::S64:
            math::internal::swizzle_copy<std::int64_t, image, components...>(view, new_image);
            break;
        case Common::ElementTypeName::F32:
            math::internal::swizzle_copy<float, image, components...>(view, new_image);
            break;
        case Common::ElementTypeName::F64:
            math::internal::swizzle_copy<double, image, components...>(view, new_image);
            break;
        default:
            std::abort();
    }

    return new_image;
}

} // namespace aeon::imaging
