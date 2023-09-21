// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <ios>

namespace aeon::Common
{

template <typename StreamT>
class ScopedFmtFlags final
{
public:
    explicit ScopedFmtFlags(StreamT &stream)
        : m_stream{stream}
        , m_flags{m_stream.flags()}
    {
    }

    ~ScopedFmtFlags()
    {
        m_stream.flags(m_flags);
    }

    ScopedFmtFlags(const ScopedFmtFlags &) = delete;
    auto operator=(const ScopedFmtFlags &) -> ScopedFmtFlags & = delete;

    ScopedFmtFlags(ScopedFmtFlags &&) noexcept = delete;
    auto operator=(ScopedFmtFlags &&) noexcept -> ScopedFmtFlags & = delete;

private:
    StreamT &m_stream;
    std::ios_base::fmtflags m_flags;
};

} // namespace aeon::Common
