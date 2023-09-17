// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/platform/exception.h>

namespace aeon::platform
{

class sdl2_platform_exception final : public platform_exception
{
public:
    explicit sdl2_platform_exception(common::string msg) noexcept
        : platform_exception{std::move(msg)}
    {
    }

    ~sdl2_platform_exception() = default;

    sdl2_platform_exception(const sdl2_platform_exception &) = default;
    auto operator=(const sdl2_platform_exception &) -> sdl2_platform_exception & = default;

    sdl2_platform_exception(sdl2_platform_exception &&) noexcept = default;
    auto operator=(sdl2_platform_exception &&) noexcept -> sdl2_platform_exception & = default;
};

} // namespace aeon::platform
