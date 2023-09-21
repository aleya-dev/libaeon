// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <mutex>
#include <condition_variable>

namespace aeon::Common
{

/*!
 * A synchronization primitive that can be used to synchronize exactly two threads.
 * Trying to synchronize more than two threads with this class leads to undefined behavior.
 */
class Fence final
{
public:
    Fence() noexcept
        : m_waiting{false}
    {
    }

    ~Fence() = default;

    Fence(const Fence &) noexcept = delete;
    auto operator=(const Fence &) noexcept -> Fence & = delete;

    Fence(Fence &&) noexcept = delete;
    auto operator=(Fence &&) noexcept -> Fence & = delete;

    /*!
     * Wait for the other thread to call wait().
     */
    void Wait() noexcept
    {
        std::unique_lock lock{m_mutex};
        if (!m_waiting)
        {
            m_waiting = true;
            m_cv.wait(lock, [this] { return !m_waiting; });
        }
        else
        {
            m_waiting = false;
            m_cv.notify_all();
        }
    }

private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_waiting;
};

} // namespace aeon::Common
