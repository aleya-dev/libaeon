// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <stdexcept>
#include <string>

namespace aeon::platform
{

class platform_exception : public std::exception
{
public:
    explicit platform_exception(std::u8string msg) noexcept
        : msg_{std::move(msg)}
    {
    }

    ~platform_exception() = default;

    platform_exception(const platform_exception &) = default;
    auto operator=(const platform_exception &) -> platform_exception & = default;

    platform_exception(platform_exception &&) noexcept = default;
    auto operator=(platform_exception &&) noexcept -> platform_exception & = default;

    [[nodiscard]] const auto &message() const noexcept
    {
        return msg_;
    }

private:
    std::u8string msg_;
};

} // namespace aeon::platform
