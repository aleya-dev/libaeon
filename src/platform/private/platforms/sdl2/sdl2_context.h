// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include "common/base_context.h"

namespace aeon::platform
{

class sdl2_context final : public base_context
{
public:
    sdl2_context();
    ~sdl2_context() final;

    sdl2_context(const sdl2_context &) noexcept = delete;
    auto operator=(const sdl2_context &) noexcept -> sdl2_context & = delete;

    sdl2_context(sdl2_context &&) noexcept = delete;
    auto operator=(sdl2_context &&) noexcept -> sdl2_context & = delete;

    [[nodiscard]] auto create_window(const window_create_info &info) -> std::unique_ptr<window> final;
    void poll_events() noexcept final;

    void handle_key(const keyboard_key key, const std::uint32_t scan_code,
                    const keyboard_key_state state) const noexcept;

    void handle_mouse_move(const math::vector2<double> position) const noexcept;
    void handle_mouse_button(const mouse_button button, const mouse_button_state state) const noexcept;
    void handle_mouse_scroll(const double delta) const noexcept;
};

} // namespace aeon::platform
