// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include "sdl2_context.h"
#include "sdl2_window.h"
#include "sdl2_exception.h"
#include <aeon/platform/native_handles.h>
#include <SDL2/SDL_syswm.h>

namespace aeon::platform
{

sdl2_window::sdl2_window(const window_create_info &info, sdl2_context &context)
    : context_{context}
{
    Uint32 sdl_flags = 0;

    if (info.resizable)
        sdl_flags |= SDL_WINDOW_RESIZABLE;

    if (info.visible)
        sdl_flags |= SDL_WINDOW_SHOWN;

    int x = SDL_WINDOWPOS_UNDEFINED;
    int y = SDL_WINDOWPOS_UNDEFINED;

    if (info.position)
    {
        x = info.position->x;
        y = info.position->y;
    }

    window_ = SDL_CreateWindow(info.title.CStr(), x, y, math::width(info.size), math::height(info.size), sdl_flags);

    if (!window_)
        throw sdl2_platform_exception{"Failed to create window."};

    SDL_SetWindowData(window_, this_ptr_key, this);
}

sdl2_window::~sdl2_window()
{
    SDL_DestroyWindow(window_);
}

auto sdl2_window::state_flags() noexcept -> window_state_flags
{
    return flags_;
}

void sdl2_window::reset_state_flags() noexcept
{
    flags_ = {};
}

auto sdl2_window::position() const noexcept -> math::vector2<std::int32_t>
{
    int x = 0;
    int y = 0;
    SDL_GetWindowPosition(window_, &x, &y);
    return {x, y};
}

void sdl2_window::position(const math::vector2<std::int32_t> &pos)
{
    SDL_SetWindowPosition(window_, pos.x, pos.y);
}

void sdl2_window::title(const Common::String &str)
{
    SDL_SetWindowTitle(window_, str.CStr());
}

auto sdl2_window::dimensions() const noexcept -> math::size2d<std::uint32_t>
{
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(window_, &w, &h);
    return math::size2d<std::uint32_t>{w, h};
}

void sdl2_window::dimensions(const math::size2d<std::uint32_t> &size)
{
    SDL_SetWindowSize(window_, static_cast<int>(size.width), static_cast<int>(size.height));
}

auto sdl2_window::framebuffer_dimensions() const noexcept -> math::size2d<std::uint32_t>
{
    int w = 0;
    int h = 0;
    SDL_GL_GetDrawableSize(window_, &w, &h);
    return math::size2d<std::uint32_t>{w, h};
}

auto sdl2_window::iconification_state() const noexcept -> window_iconification_state
{
    const auto state = SDL_GetWindowFlags(window_);

    if (state & SDL_WINDOW_MINIMIZED)
        return window_iconification_state::minimized;

    return window_iconification_state::normal;
}

void sdl2_window::set_visible(const bool visible) const noexcept
{
    if (visible)
        SDL_ShowWindow(window_);
    else
        SDL_HideWindow(window_);
}

auto sdl2_window::is_visible() const noexcept -> bool
{
    return SDL_GetWindowFlags(window_) & SDL_WINDOW_SHOWN;
}

void sdl2_window::close()
{
    SDL_DestroyWindow(window_);
    window_ = nullptr;
}

auto sdl2_window::closed() noexcept -> bool
{
    return flags_.closing;
}

auto sdl2_window::native_handles() const noexcept -> platform::native_handles
{
    // Get the HWND from SDL
    SDL_SysWMinfo wm_info;
    SDL_VERSION(&wm_info.version)
    SDL_GetWindowWMInfo(window_, &wm_info);

    platform::native_handles handles;

#if (AEON_PLATFORM_OS_WINDOWS)
    handles.hwnd = wm_info.info.win.window;
#elif (AEON_PLATFORM_OS_LINUX)
    handles.window = wm_info.info.x11.window;
    handles.display = wm_info.info.x11.display;
#endif

    return handles;
}

auto sdl2_window::context() const noexcept -> const platform::context &
{
    return context_;
}

void sdl2_window::on_closing()
{
    flags_.closing = true;
}

} // namespace aeon::platform
