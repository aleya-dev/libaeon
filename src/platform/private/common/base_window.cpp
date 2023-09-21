// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include "base_window.h"

namespace aeon::platform
{

base_window::base_window() noexcept
    : window_listeners_{}
{
}

base_window::~base_window() = default;

void base_window::attach_window_listener(window_events &events)
{
    window_listeners_.Attach(events);
}

void base_window::detach_window_listener(window_events &events)
{
    window_listeners_.Detach(events);
}

void base_window::detach_all_window_listeners()
{
    window_listeners_.DetachAll();
}

} // namespace aeon::platform
