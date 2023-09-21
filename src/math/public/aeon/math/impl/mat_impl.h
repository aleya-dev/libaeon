// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::math
{

inline mat::mat() noexcept
    : mat_view{}
    , data_{}
{
}

inline mat::mat(const Common::ElementType type, const size2d<dimensions_type> dimensions) noexcept
    : mat_view{type, dimensions, nullptr}
    , data_(mat_view::stride_ * math::height(mat_view::dimensions_))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const Common::ElementType type, const dimensions_type width, const dimensions_type height) noexcept
    : mat_view{type, width, height, nullptr}
    , data_(mat_view::stride_ * math::height(mat_view::dimensions_))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const Common::ElementType type, const size2d<dimensions_type> dimensions,
                const stride_type stride) noexcept
    : mat_view{type, dimensions, stride, nullptr}
    , data_(mat_view::stride_ * math::height(mat_view::dimensions_))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const Common::ElementType type, const dimensions_type width, const dimensions_type height,
                const stride_type stride) noexcept
    : mat_view{type, width, height, stride, nullptr}
    , data_(mat_view::stride_ * math::height(mat_view::dimensions_))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const Common::ElementType type, const size2d<dimensions_type> dimensions,
                std::vector<underlying_type> data) noexcept
    : mat_view{type, dimensions, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const Common::ElementType type, const dimensions_type width, const dimensions_type height,
                std::vector<underlying_type> data) noexcept
    : mat_view{type, width, height, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const Common::ElementType type, const size2d<dimensions_type> dimensions, const stride_type stride,
                std::vector<underlying_type> data) noexcept
    : mat_view{type, dimensions, stride, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const Common::ElementType type, const dimensions_type width, const dimensions_type height,
                const stride_type stride, std::vector<underlying_type> data) noexcept
    : mat_view{type, width, height, stride, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const Common::ElementType type, const size2d<dimensions_type> dimensions, const underlying_type *data)
    : mat_view{type, dimensions, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline mat::mat(const Common::ElementType type, const dimensions_type width, const dimensions_type height,
                const underlying_type *data)
    : mat_view{type, width, height, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline mat::mat(const Common::ElementType type, const size2d<dimensions_type> dimensions, const stride_type stride,
                const underlying_type *data)
    : mat_view{type, dimensions, stride, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline mat::mat(const Common::ElementType type, const dimensions_type width, const dimensions_type height,
                const stride_type stride, const underlying_type *data)
    : mat_view{type, width, height, stride, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline mat::mat(const mat_view &other)
    : mat_view{math::ElementType(other), math::dimensions(other), math::stride(other), nullptr}
    , data_{}
{
    copy_from_pointer(std::data(other));
}

inline auto mat::operator=(const mat_view &other) -> mat &
{
    if (this != &other) [[likely]]
    {
        mat_view::type_ = math::ElementType(other);
        mat_view::dimensions_ = math::dimensions(other);
        mat_view::stride_ = math::stride(other);
        copy_from_pointer(std::data(other));
    }

    return *this;
}

[[nodiscard]] inline auto mat::clone() const -> mat
{
    return mat{type_, dimensions_, stride_, data_};
}

inline void mat::clear() noexcept
{
    type_ = {};
    data_ptr_ = nullptr;
    dimensions_ = {};
    stride_ = 0;

    // Force data deletion. Clear does not guarantee deallocation.
    decltype(data_)().swap(data_);
}

inline void mat::copy_from_pointer(const underlying_type *data)
{
    const auto size = mat_view::size();
    data_.resize(size);
    mat_view::data_ptr_ = std::data(data_);
    std::copy_n(data, size, std::begin(data_));
}

namespace internal
{

template <typename T, typename MatType_T, swizzle_component... components>
inline void swizzle_copy(const mat_view &src, MatType_T &dst) noexcept
{
    constexpr auto component_count = sizeof...(components);
    const auto source_component_count = src.ElementType().Count;

    auto src_data = reinterpret_cast<const T *>(src.data());
    auto dst_data = reinterpret_cast<T *>(dst.data());

    const auto area = math::area(src.dimensions());

    for (auto i = 0; i < area; ++i)
    {
        std::size_t index = 0;
        (swizzle_apply<T, components>(src_data, dst_data, index++), ...);

        src_data += source_component_count;
        dst_data += component_count;
    }
}

} // namespace internal

template <swizzle_component... components>
[[nodiscard]] inline auto swizzle_copy(const mat_view &view) noexcept -> mat
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

    mat new_mat{new_element_type, dimensions(view)};

    switch (view.ElementType().Name)
    {
        case Common::ElementTypeName::U8:
            internal::swizzle_copy<std::uint8_t, mat, components...>(view, new_mat);
            break;
        case Common::ElementTypeName::S8:
            internal::swizzle_copy<std::int8_t, mat, components...>(view, new_mat);
            break;
        case Common::ElementTypeName::U16:
            internal::swizzle_copy<std::uint16_t, mat, components...>(view, new_mat);
            break;
        case Common::ElementTypeName::S16:
            internal::swizzle_copy<std::int16_t, mat, components...>(view, new_mat);
            break;
        case Common::ElementTypeName::U32:
            internal::swizzle_copy<std::uint32_t, mat, components...>(view, new_mat);
            break;
        case Common::ElementTypeName::S32:
            internal::swizzle_copy<std::int32_t, mat, components...>(view, new_mat);
            break;
        case Common::ElementTypeName::U64:
            internal::swizzle_copy<std::uint64_t, mat, components...>(view, new_mat);
            break;
        case Common::ElementTypeName::S64:
            internal::swizzle_copy<std::int64_t, mat, components...>(view, new_mat);
            break;
        case Common::ElementTypeName::F32:
            internal::swizzle_copy<float, mat, components...>(view, new_mat);
            break;
        case Common::ElementTypeName::F64:
            internal::swizzle_copy<double, mat, components...>(view, new_mat);
            break;
        default:
            std::abort();
    }

    return new_mat;
}

} // namespace aeon::math
