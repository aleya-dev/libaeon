// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::Common
{

template <typename T>
class Delay
{
public:
    using TimeType = T;

    explicit Delay(const T timeout)
        : m_currentTime{}
        , m_timeout{timeout}
    {
    }

    ~Delay() = default;

    Delay(const Delay &) noexcept = default;
    auto operator=(const Delay &) noexcept -> Delay & = default;

    Delay(Delay &&) noexcept = default;
    auto operator=(Delay &&) noexcept -> Delay & = default;

    void Timeout(const TimeType timeout) noexcept
    {
        Reset();
        m_timeout = timeout;
    }

    [[nodiscard]] auto Timeout() const noexcept -> TimeType
    {
        return m_timeout;
    }

    void Reset() noexcept
    {
        m_currentTime = {};
    }

    [[nodiscard]] auto Expired(const TimeType dt) noexcept -> bool
    {
        m_currentTime += dt;

        if (m_currentTime >= m_timeout)
        {
            m_currentTime = 0;
            return true;
        }

        return false;
    }

private:
    TimeType m_currentTime;
    TimeType m_timeout;
};

} // namespace aeon::Common
