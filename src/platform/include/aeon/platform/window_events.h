// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/math/size2d.h>
#include <aeon/math/vector2.h>
#include <cstdint>

namespace aeon::platform
{

class context;

class window_events
{
public:
    window_events() noexcept = default;
    virtual ~window_events() = default;

    window_events(const window_events &) noexcept = default;
    auto operator=(const window_events &) noexcept -> window_events & = default;

    window_events(window_events &&) noexcept = default;
    auto operator=(window_events &&) noexcept -> window_events & = default;

    virtual void on_window_position_changed([[maybe_unused]] const context &context,
                                            [[maybe_unused]] const math::vector2<std::int32_t> &position) noexcept
    {
    }

    virtual void on_window_size_changed([[maybe_unused]] const context &context,
                                        [[maybe_unused]] const math::size2d<std::int32_t> &size) noexcept
    {
    }

    virtual void on_window_focus_changed([[maybe_unused]] const context &context,
                                         [[maybe_unused]] const bool focus) noexcept
    {
    }

    virtual void on_key_down([[maybe_unused]] const context &context, [[maybe_unused]] const std::uint32_t key_code,
                             [[maybe_unused]] const std::uint32_t character_code, [[maybe_unused]] const bool repeated)
    {
    }

    virtual void on_key_up([[maybe_unused]] const context &context, [[maybe_unused]] const std::uint32_t key_code,
                           [[maybe_unused]] const std::uint32_t character_code, [[maybe_unused]] const bool repeated)
    {
    }

    virtual void on_window_closed([[maybe_unused]] const context &context) noexcept
    {
    }
};

} // namespace aeon::platform
