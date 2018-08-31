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

#pragma once

#include <aeon/fonts/glyph.h>
#include <aeon/streams/stream_fwd.h>
#include <memory>
#include <vector>

// Forward declare for FreeType.
struct FT_LibraryRec_;

namespace aeon::fonts
{

class face_wrapper;

class face
{
    friend class font_manager;

public:
    ~face();

    face(const face &) = delete;
    auto operator=(const face &) -> face & = delete;

    face(face &&) noexcept = default;
    auto operator=(face &&) noexcept -> face & = default;

    /*!
     * Load a glyph. Loading the next glyph will re-use the same buffer,
     * so be sure to copy the image somewhere first before loading the next glyph.
     */
    auto load_glyph(const char32_t control_code) const -> glyph;

private:
    face(FT_LibraryRec_ *library, streams::stream &stream, const float points, const int dpi);
    face(FT_LibraryRec_ *library, const std::vector<std::reference_wrapper<streams::stream>> &streams,
         const float points, const int dpi);

    std::vector<std::unique_ptr<face_wrapper>> faces_;
};

} // namespace aeon::fonts
