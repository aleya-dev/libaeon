// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <turbojpeg.h>

namespace aeon::imaging::file::jpg::detail
{

class [[nodiscard]] tjhandle_wrapper
{
public:
    tjhandle_wrapper(tjhandle handle);

    tjhandle_wrapper(const tjhandle_wrapper &) = delete;
    auto operator=(const tjhandle_wrapper &) -> tjhandle_wrapper & = delete;

    tjhandle_wrapper(tjhandle_wrapper &&) = delete;
    auto operator=(tjhandle_wrapper &&) -> tjhandle_wrapper & = delete;

    [[nodiscard]] auto handle() const noexcept;

protected:
    ~tjhandle_wrapper();

private:
    tjhandle handle_;
};

inline tjhandle_wrapper::tjhandle_wrapper(tjhandle handle)
    : handle_(handle)
{
}

inline tjhandle_wrapper::~tjhandle_wrapper()
{
    if (handle_)
        tjDestroy(handle_);
}

[[nodiscard]] inline auto tjhandle_wrapper::handle() const noexcept
{
    return handle_;
}

class [[nodiscard]] tjhandle_decompress_wrapper final : public tjhandle_wrapper
{
public:
    tjhandle_decompress_wrapper();
    ~tjhandle_decompress_wrapper() = default;

    tjhandle_decompress_wrapper(const tjhandle_decompress_wrapper &) = delete;
    auto operator=(const tjhandle_decompress_wrapper &) -> tjhandle_decompress_wrapper & = delete;

    tjhandle_decompress_wrapper(tjhandle_decompress_wrapper &&) = delete;
    auto operator=(tjhandle_decompress_wrapper &&) -> tjhandle_decompress_wrapper & = delete;
};

inline tjhandle_decompress_wrapper::tjhandle_decompress_wrapper()
    : tjhandle_wrapper(tjInitDecompress())
{
}

class [[nodiscard]] tjhandle_compress_wrapper final : public tjhandle_wrapper
{
public:
    tjhandle_compress_wrapper();
    ~tjhandle_compress_wrapper() = default;

    tjhandle_compress_wrapper(const tjhandle_compress_wrapper &) = delete;
    auto operator=(const tjhandle_compress_wrapper &) -> tjhandle_compress_wrapper & = delete;

    tjhandle_compress_wrapper(tjhandle_compress_wrapper &&) = delete;
    auto operator=(tjhandle_compress_wrapper &&) -> tjhandle_compress_wrapper & = delete;
};

inline tjhandle_compress_wrapper::tjhandle_compress_wrapper()
    : tjhandle_wrapper(tjInitCompress())
{
}

} // namespace aeon::imaging::file::jpg::detail
