// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/tracelog/tracelog.h>
#include "context.h"

namespace aeon::Tracelog
{

namespace Internal
{

[[nodiscard]] auto AddEntry(const char *func) -> TraceLogEntry *
{
    return Internal::trace_log_context::GetSingleton().add_scoped_log_entry(func);
}

void AddExit(TraceLogEntry *entry)
{
    Internal::trace_log_context::GetSingleton().add_scoped_log_exit(entry);
}

void AddEvent(const char *func)
{
    Internal::trace_log_context::GetSingleton().add_event(func);
}

} // namespace detail

void Initialize()
{
    Internal::trace_log_context::GetSingleton().initialize();
}

void Write(const std::filesystem::path &file)
{
    Internal::trace_log_context::GetSingleton().write(file);
}

} // namespace aeon::tracelog
