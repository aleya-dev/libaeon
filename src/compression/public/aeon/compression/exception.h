// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <stdexcept>

namespace aeon::compression
{

class zlib_compress_exception : public std::exception
{
};

class zlib_decompress_exception : public std::exception
{
};

} // namespace aeon::compression
