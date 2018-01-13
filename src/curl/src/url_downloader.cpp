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

#include <aeon/curl/url_downloader.h>
#include <aeon/curl/exceptions.h>
#include <aeon/streams/file_stream.h>

namespace aeon
{
namespace curl
{

url_downloader::url_downloader() = default;
url_downloader::~url_downloader() = default;

void url_downloader::download(const std::string &url, const std::string &dest_path)
{
    streams::file_stream f(dest_path, streams::access_mode::write | streams::access_mode::truncate);

    if (!f.good())
        throw url_downloader_exception();

    wrapper_.get(url, [&f](void *buffer, const std::size_t size) -> std::size_t {
        auto result = f.write(static_cast<std::uint8_t *>(buffer), size);

        if (result != size)
            throw url_downloader_exception();

        return size;
    });

    f.flush();
}

} // namespace curl
} // namespace aeon
