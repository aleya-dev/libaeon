// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/platform/platform_export.h>
#include <aeon/platform/platform_config.h>
#include <memory>

namespace aeon::platform
{

struct window_create_info;
class window;
class input_events;

enum class backend
{
#if (defined(AEON_PLATFORM_BACKEND_GLFW))
    glfw,
#endif

#if (defined(AEON_PLATFORM_BACKEND_SDL2))
    sdl2,
#endif
};

class context
{
public:
    context() noexcept = default;
    virtual ~context() = default;

    context(const context &) noexcept = delete;
    auto operator=(const context &) noexcept -> context & = delete;

    context(context &&) noexcept = delete;
    auto operator=(context &&) noexcept -> context & = delete;

    [[nodiscard]] virtual auto create_window(const window_create_info &info) -> std::unique_ptr<window> = 0;
    virtual void poll_events() noexcept = 0;

    virtual void attach_input_listener(input_events &events) = 0;
    virtual void detach_input_listener(input_events &events) = 0;
    virtual void detach_all_input_listeners() = 0;
};

[[nodiscard]] AEON_PLATFORM_EXPORT auto create_context(backend backend) -> std::unique_ptr<context>;

} // namespace aeon::platform
