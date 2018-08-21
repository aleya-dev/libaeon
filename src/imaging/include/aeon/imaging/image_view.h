/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
 * \file
 * \brief Contains the image_view class.
 * An image view provides a way to access and modify image data.
 */

#pragma once

#include <aeon/imaging/image_descriptor.h>
#include <aeon/imaging/image_view_base.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>
#include <cstdint>
#include <cstddef>

namespace aeon::imaging
{

/*!
 * An image view provides a way to access and modify image data.
 * An image_view does not own the data that it provides a view on.
 */
template <typename T>
class image_view : public image_view_base<T>
{
public:
    /*!
     * Create a null (empty) image view (all values will be set to 0)
     */
    image_view() noexcept;

    /*!
     * Create a view based on the given descriptor and data pointer.
     * The data must match the pixel type, stride and sizes in the given descriptor.
     * \param[in] descriptor - An image descriptor
     * \param[in] data - Raw image data
     */
    explicit image_view(const image_descriptor<T> &descriptor, std::byte *data) noexcept;

    /*!
     * Create a view based on the given descriptor and data pointer.
     * The data must match the pixel type, stride and sizes in the given descriptor.
     * \param[in] descriptor - An image descriptor
     * \param[in] data - Raw image data
     */
    explicit image_view(const image_descriptor<T> &descriptor, const std::byte *data) noexcept;

    virtual ~image_view() noexcept;

    image_view(const image_view<T> &) = default;
    auto operator=(const image_view<T> &) -> image_view<T> & = default;

    image_view(image_view<T> &&) noexcept = default;
    auto operator=(image_view<T> &&) noexcept -> image_view<T> & = default;

    /*!
     * Get a pointer to the raw image data.
     * The descriptor should be used to get information about the layout in memory.
     * \return Pointer to raw image data.
     */
    auto data() noexcept -> T *;

    /*!
     * Get a pointer to the raw image data.
     * The descriptor should be used to get information about the layout in memory.
     * \return Pointer to raw image data.
     */
    auto data() const noexcept -> const T *;

    /*!
     * Get a pointer to the raw image data.
     * The descriptor should be used to get information about the layout in memory.
     * \return Pointer to raw image data.
     */
    template <typename U>
    auto data() noexcept -> U *;

    /*!
     * Get a pointer to the raw image data.
     * The descriptor should be used to get information about the layout in memory.
     * \return Pointer to raw image data.
     */
    template <typename U>
    auto data() const noexcept -> const U *;

    /*!
     * Get a pointer to the raw image data at the pixel offset of the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * The descriptor should be used to get information about the layout in memory.
     * \param[in] coord - A pixel coordinate
     * \return Pointer to raw image data.
     */
    auto data(const math::vector2<dimension> coord) noexcept -> T *;

    /*!
     * Get a pointer to the raw image data at the pixel offset of the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * The descriptor should be used to get information about the layout in memory.
     * \param[in] coord - A pixel coordinate
     * \return Pointer to raw image data.
     */
    auto data(const math::vector2<dimension> coord) const noexcept -> const T *;

    /*!
     * Get a pointer to the raw image data at the pixel offset of the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * The descriptor should be used to get information about the layout in memory.
     * \param[in] coord - A pixel coordinate
     * \return Pointer to raw image data.
     */
    template <typename U>
    auto data(const math::vector2<dimension> coord) noexcept -> U *;

    /*!
     * Get a pointer to the raw image data at the pixel offset of the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * The descriptor should be used to get information about the layout in memory.
     * \param[in] coord - A pixel coordinate
     * \return Pointer to raw image data.
     */
    template <typename U>
    auto data(const math::vector2<dimension> coord) const noexcept -> const U *;

    /*!
     * Get a reference to a pixel at the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * \param[in] coord - A pixel coordinate
     * \return A reference to a pixel at the given coordinate.
     */
    auto at(const math::vector2<dimension> coord) noexcept -> T &;

    /*!
     * Get a reference to a pixel at the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * \param[in] coord - A pixel coordinate
     * \return A reference to a pixel at the given coordinate.
     */
    auto at(const math::vector2<dimension> coord) const noexcept -> const T &;

protected:
    /*!
     * Internal constructor used by image<T>. This constructor is used
     * when the data pointer is not known up front since the data needs to
     * be copied first. The image class will set the data pointer after copying
     * the image data.
     */
    explicit image_view(const image_descriptor<T> &descriptor) noexcept;

    std::byte *data_ptr_;
};

/*!
 * Returns true if the image view is null. An image view is null when
 * all it's internal values (width, height, stride) are set to 0.
 * \param[in] view - An image view
 * \return Returns true if the image view is null.
 */
template <typename T>
inline auto null(const image_view<T> &view) noexcept -> bool;

/*!
 * Returns true if the image view is valid. An image view is valid when it is not null.
 * \see null(const image_descriptor<T> &descriptor)
 * \param[in] view - An image view
 * \return Returns true if the image view is valid.
 */
template <typename T>
inline auto valid(const image_view<T> &view) noexcept -> bool;

/*!
 * Create a new view on an existing view based on a given rectangle. This will essentially
 * crop the view on the image data without modifying or copying the data itself.
 * The given rectangle must fit within the dimensions of the view.
 * \param[in] view - An image view
 * \param[in] rect - A rectangle to 'crop' the view.
 * \return Returns A new view
 */
template <typename T>
inline auto make_view(const image_view<T> &view, const math::rectangle<int> &rect) noexcept -> image_view<T>;

} // namespace aeon::imaging

#include <aeon/imaging/impl/image_view_impl.h>
