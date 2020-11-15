// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/platform/native_handles.h>
#include <aeon/math/size2d.h>
#include <aeon/math/vector2.h>
#include <string>
#include <cstdint>

namespace aeon::platform
{

class context;

class window
{
public:
    window() noexcept = default;
    virtual ~window() = default;

    window(const window &) noexcept = delete;
    auto operator=(const window &) noexcept -> window & = delete;

    window(window &&) noexcept = delete;
    auto operator=(window &&) noexcept -> window & = delete;

    [[nodiscard]] virtual auto position() const noexcept -> math::vector2<std::int32_t> = 0;
    virtual void position(const math::vector2<std::int32_t> &pos) = 0;

    virtual void title(const std::u8string &str) = 0;

    [[nodiscard]] virtual auto size() const noexcept -> math::size2d<std::int32_t> = 0;
    virtual void size(const math::size2d<std::int32_t> &size) = 0;

    virtual void close() = 0;

    [[nodiscard]] virtual auto closed() const noexcept -> bool = 0;

    [[nodiscard]] virtual auto native_handles() const noexcept -> platform::native_handles = 0;

    [[nodiscard]] virtual auto context() const noexcept -> const context & = 0;
};

} // namespace aeon::platform
