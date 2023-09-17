// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <mutex>
#include <condition_variable>

namespace aeon::common
{

/*!
 * A synchronization primitive that can be used to synchronize exactly two threads.
 * Trying to synchronize more than two threads with this class leads to undefined behavior.
 */
class fence final
{
public:
    fence() noexcept
        : waiting_{false}
    {
    }

    ~fence() = default;

    fence(const fence &) noexcept = delete;
    auto operator=(const fence &) noexcept -> fence & = delete;

    fence(fence &&) noexcept = delete;
    auto operator=(fence &&) noexcept -> fence & = delete;

    /*!
     * Wait for the other thread to call wait().
     */
    void wait() noexcept
    {
        std::unique_lock lock{mutex_};
        if (!waiting_)
        {
            waiting_ = true;
            cv_.wait(lock, [this] { return !waiting_; });
        }
        else
        {
            waiting_ = false;
            cv_.notify_all();
        }
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    bool waiting_;
};

} // namespace aeon::common
