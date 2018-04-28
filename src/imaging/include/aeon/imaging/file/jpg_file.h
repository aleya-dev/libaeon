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

#include <aeon/imaging/image.h>
#include <aeon/imaging/exceptions.h>
#include <aeon/streams/stream_fwd.h>
#include <aeon/common/stdfilesystem.h>

namespace aeon::imaging::file::jpg
{

class load_exception : public imaging_exception
{
};

auto load(const std::filesystem::path &path) -> image;
auto load(streams::stream &stream) -> image;

class save_exception : public imaging_exception
{
};

enum class subsample_mode
{
    subsample_444,
    subsample_440,
    subsample_422,
    subsample_420,
    subsample_411,
    subsample_grayscale
};

void save(const image &image, const subsample_mode subsample, int quality, const std::filesystem::path &path);
void save(const image &image, const subsample_mode subsample, int quality, streams::stream &stream);

} // namespace aeon::imaging::file::jpg