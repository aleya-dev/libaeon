// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/platform/window_create_info.h>
#include <aeon/platform/context.h>
#include "common/base_window.h"
#include "sdl2_context.h"
#include <SDL2/SDL.h>

namespace aeon::platform
{

class sdl2_window final : public base_window
{
public:
    static constexpr auto this_ptr_key = "sdl2_window";

    explicit sdl2_window(const window_create_info &info, sdl2_context &context);
    ~sdl2_window() final;

    sdl2_window(const sdl2_window &) noexcept = delete;
    auto operator=(const sdl2_window &) noexcept -> sdl2_window & = delete;

    sdl2_window(sdl2_window &&) noexcept = delete;
    auto operator=(sdl2_window &&) noexcept -> sdl2_window & = delete;

    [[nodiscard]] auto state_flags() noexcept -> window_state_flags final;
    void reset_state_flags() noexcept final;

    [[nodiscard]] auto position() const noexcept -> math::vector2<std::int32_t> final;
    void position(const math::vector2<std::int32_t> &pos) final;

    void title(const Common::String &str) final;

    [[nodiscard]] auto dimensions() const noexcept -> math::size2d<std::uint32_t> final;
    void dimensions(const math::size2d<std::uint32_t> &size) final;

    [[nodiscard]] auto framebuffer_dimensions() const noexcept -> math::size2d<std::uint32_t> final;

    [[nodiscard]] auto iconification_state() const noexcept -> window_iconification_state final;

    void set_visible(const bool visible) const noexcept final;
    [[nodiscard]] auto is_visible() const noexcept -> bool final;

    void close() final;

    [[nodiscard]] auto closed() noexcept -> bool final;

    [[nodiscard]] auto native_handles() const noexcept -> platform::native_handles final;

    [[nodiscard]] auto context() const noexcept -> const platform::context & final;

    void on_closing();

private:
    sdl2_context &context_;
    SDL_Window *window_;
    window_state_flags flags_;
};

} // namespace aeon::platform
