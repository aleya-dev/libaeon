// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

/*!
 * \file
 * \brief Base class for image_view with common methods and functions.
 * An image view provides a way to access and modify image data.
 */

#pragma once

#include <aeon/imaging/image_descriptor.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>
#include <cstdint>
#include <cstddef>

namespace aeon::imaging
{

/*!
 * Base class for image_view with common methods and functions.
 * An image view provides a way to access and modify image data.
 *
 * An image_view does not own the data that it provides a view on.
 */
template <typename T>
class image_view_base
{
public:
    virtual ~image_view_base() noexcept;

    image_view_base(const image_view_base<T> &) = default;
    auto operator=(const image_view_base<T> &) -> image_view_base<T> & = default;

    image_view_base(image_view_base<T> &&) noexcept = default;
    auto operator=(image_view_base<T> &&) noexcept -> image_view_base<T> & = default;

    /*!
     * Get the descriptor of the image view.
     * \return The descriptor of the image view.
     */
    [[nodiscard]] auto descriptor() const noexcept -> image_descriptor<T>;

protected:
    /*!
     * Create an empty image view with a null descriptor.
     */
    image_view_base() noexcept;

    /*!
     * Create an image view from a given descriptor.
     */
    explicit image_view_base(const image_descriptor<T> &descriptor) noexcept;

    image_descriptor<T> descriptor_;
};

/*!
 * Get the descriptor of the given image view
 * \param[in] view - An image view
 * \return The descriptor of the image view.
 */
template <typename T>
[[nodiscard]] inline auto descriptor(const image_view_base<T> &view) noexcept -> image_descriptor<T>;

/*!
 * Get the width of the given image view.
 * \param[in] view - An image view
 * \return The width of the image view.
 */
template <typename T>
[[nodiscard]] inline auto width(const image_view_base<T> &view) noexcept;

/*!
 * Get the height of the given image view.
 * \param[in] view - An image view
 * \return The height of the image view.
 */
template <typename T>
[[nodiscard]] inline auto height(const image_view_base<T> &view) noexcept;

/*!
 * Get the dimensions of the given image view (width, height).
 * \param[in] view - An image view
 * \return The dimensions of the image view.
 */
template <typename T>
[[nodiscard]] inline auto dimensions(const image_view_base<T> &view) noexcept;

/*!
 * Get the rectangle of the image view (based on the dimensions).
 * The rectangle is constructed with top and left as 0, and right and bottom as width and height
 * respectively.
 * \param[in] view - An image view
 * \return The rectangle surrounding the image view.
 */
template <typename T>
[[nodiscard]] inline auto rectangle(const image_view_base<T> &view) noexcept;

/*!
 * Get the stride of the given image view.
 * The stride is the amount of bytes between 2 lines/rows.
 * \param[in] view - An image view
 * \return The stride of the image view.
 */
template <typename T>
[[nodiscard]] inline auto stride(const image_view_base<T> &view) noexcept;

/*!
 * Returns true if the data described by the given image view is laid out in memory in a
 * continuous fashion
 * (ie. stride=bytes_per_pixel(encoding)*width)
 * \param[in] view - An image view
 * \return True if the image view's data is continuous.
 */
template <typename T>
[[nodiscard]] inline auto continuous(const image_view_base<T> &view) noexcept;

/*!
 * Returns true if the given coordinate falls within the dimensions of the given image view.
 * \param[in] view - An image view
 * \param[in] coord - A coordinate (X, Y)
 * \return True if the coordinate is within the dimensions of the image view.
 */
template <typename T>
[[nodiscard]] inline auto contains(const image_view_base<T> &view, const math::vector2<dimension> coord) noexcept;

/*!
 * Get the full size in bytes of the data described by the image view in
 * memory (stride * height).
 * \param[in] view - An image view
 * \return The size in bytes.
 */
template <typename T>
[[nodiscard]] inline auto size(const image_view_base<T> &view) noexcept -> std::ptrdiff_t;

} // namespace aeon::imaging

#include <aeon/imaging/impl/image_view_base_impl.h>
