// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <chrono>

namespace aeon::Common
{

class Timer
{
public:
    using ClockType = std::chrono::high_resolution_clock;

    Timer() noexcept
    {
        Reset();
    }

    ~Timer() = default;

    Timer(Timer &&) = delete;
    auto operator=(Timer &&) -> Timer & = delete;

    Timer(const Timer &) = delete;
    auto operator=(const Timer &) -> Timer & = delete;

    void Reset() noexcept
    {
        m_startTime = ClockType::now();
    }

    template <typename T = float>
    [[nodiscard]] auto GetTimeDifference() const noexcept
    {
        const auto now = ClockType::now();
        const std::chrono::duration<T> elapsedSeconds = now - m_startTime;
        return elapsedSeconds.count();
    }

private:
    std::chrono::time_point<ClockType> m_startTime;
};

} // namespace aeon::Common
