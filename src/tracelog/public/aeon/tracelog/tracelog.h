// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/preprocessor.h>
#include <filesystem>

namespace aeon::Tracelog
{

namespace Internal
{

struct TraceLogEntry;

auto AddEntry(const char *func) -> TraceLogEntry *;
void AddExit(TraceLogEntry *entry);
void AddEvent(const char *func);

class [[nodiscard]] ScopedTraceLog
{
public:
    ScopedTraceLog(const char *func)
    {
        m_entry = Internal::AddEntry(func);
    }

    ~ScopedTraceLog()
    {
        Internal::AddExit(m_entry);
    }

    ScopedTraceLog(ScopedTraceLog &&) = delete;
    auto operator=(ScopedTraceLog &&) -> ScopedTraceLog & = delete;

    ScopedTraceLog(const ScopedTraceLog &) = delete;
    auto operator=(const ScopedTraceLog &) -> ScopedTraceLog & = delete;

private:
    TraceLogEntry *m_entry;
};

} // namespace detail

/*!
 * Must be called at the start of each thread before using aeon_scoped_tracelog.
 */
void Initialize();

/*!
 * Should be called at the end of tracing. This will clear all current tracing buffers.
 * The file may not already exist.
 */
void Write(const std::filesystem::path &file);

#define AeonTracelogScoped() aeon::Tracelog::Internal::ScopedTraceLog AeonAnonymousVariable(trace)(__FUNCTION__)

#define AeonEvent() aeon::Tracelog::Internal::AddTraceLogEvent(__FUNCTION__)

} // namespace aeon::tracelog
