// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include "base_context.h"
#include <aeon/platform/platform_config.h>

#if (defined(AEON_PLATFORM_BACKEND_GLFW))
#include "platforms/glfw/glfw_context.h"
#endif

#if (defined(AEON_PLATFORM_BACKEND_SDL2))
#include "platforms/sdl2/sdl2_context.h"
#endif

namespace aeon::platform
{

[[nodiscard]] AEON_PLATFORM_EXPORT auto create_context(backend backend) -> std::unique_ptr<context>
{
    switch (backend)
    {
#if (defined(AEON_PLATFORM_BACKEND_GLFW))
        case backend::glfw:
            return std::make_unique<glfw_context>();
#endif

#if (defined(AEON_PLATFORM_BACKEND_SDL2))
        case backend::sdl2:
            return std::make_unique<sdl2_context>();
#endif
    }

    std::abort();
}

base_context::base_context() noexcept
    : input_listeners_{}
{
}

base_context::~base_context() = default;

void base_context::attach_input_listener(input_events &events)
{
    input_listeners_.Attach(events);
}

void base_context::detach_input_listener(input_events &events)
{
    input_listeners_.Detach(events);
}

void base_context::detach_all_input_listeners()
{
    input_listeners_.DetachAll();
}

} // namespace aeon::platform
