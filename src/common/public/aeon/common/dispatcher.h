// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <functional>
#include <mutex>
#include <future>
#include <queue>
#include <atomic>

namespace aeon::Common
{

/*!
 * Determines how the dispatcher should stop. Either by calling stop manually (ManualStop) or automaticly
 * when the queue is determined to be empty. Be sure all jobs are queued before calling run when using this mode to
 * prevent race conditions.
 */
enum DispatcherStopMode
{
    ManualStop,
    StopOnEmptyQueue
};

class Dispatcher
{
public:
    static constexpr int SignalWaitTimeoutMs = 100;

    explicit Dispatcher(const DispatcherStopMode stopMode = DispatcherStopMode::ManualStop)
        : m_running{false}
        , m_stopMode{stopMode}
    {
    }

    ~Dispatcher() = default;

    Dispatcher(const Dispatcher &) noexcept = delete;
    auto operator=(const Dispatcher &) noexcept -> Dispatcher & = delete;
    Dispatcher(Dispatcher &&) noexcept = delete;
    auto operator=(Dispatcher &&) noexcept -> Dispatcher & = delete;

    void RunOne()
    {
        std::function<void()> func;
        {
            std::unique_lock lock(m_mutex);
            m_signalCv.wait(lock, [this]() { return !m_queue.empty() || !m_running; });

            if (!m_queue.empty())
            {
                func = std::move(m_queue.front());
                m_queue.pop();
            }

            if (m_stopMode == DispatcherStopMode::StopOnEmptyQueue)
            {
                if (m_queue.empty())
                    m_running = false;
            }
        }

        if (func)
            func();
    }

    void Run()
    {
        m_running = true;

        while (m_running)
        {
            RunOne();
        }
    }

    void Post(std::function<void()> &&job)
    {
        std::scoped_lock lock(m_mutex);
        m_queue.push(std::move(job));
        m_signalCv.notify_one();
    }

    void Call(std::function<void()> &&job)
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        Post(
            [job = std::move(job), &promise]()
            {
                try
                {
                    job();
                    promise.set_value();
                }
                catch (...)
                {
                    promise.set_exception(std::current_exception());
                }
            });

        return future.get();
    }

    template <typename T, std::enable_if_t<!std::is_void_v<T>> * = nullptr>
    T Call(std::function<T()> &&job)
    {
        std::promise<T> promise;
        auto future = promise.get_future();

        Post(
            [job = std::move(job), &promise]()
            {
                try
                {
                    promise.set_value(job());
                }
                catch (...)
                {
                    promise.set_exception(std::current_exception());
                }
            });

        return future.get();
    }

    void SyncFence()
    {
        std::promise<void> promise;
        auto future = promise.get_future();
        Post([&promise]() { promise.set_value(); });
        future.get();
    }

    void Stop()
    {
        std::scoped_lock guard(m_mutex);
        m_running = false;
        m_signalCv.notify_all();
    }

    void Reset()
    {
        std::scoped_lock guard(m_mutex);
        m_queue = std::queue<std::function<void()>>();
    }

private:
    std::mutex m_mutex;
    std::condition_variable m_signalCv;
    std::queue<std::function<void()>> m_queue;
    std::atomic<bool> m_running;
    DispatcherStopMode m_stopMode;
};

} // namespace aeon::Common
