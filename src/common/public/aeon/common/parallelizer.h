// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/dispatcher.h>
#include <functional>
#include <vector>

namespace aeon::Common
{

class Parallelizer
{
public:
    using Task = std::function<void()>;
    using TaskVector = std::vector<Task>;

    Parallelizer()
        : m_dispatcher(DispatcherStopMode::StopOnEmptyQueue)
    {
    }

    explicit Parallelizer(const TaskVector &tasks)
        : m_dispatcher(DispatcherStopMode::StopOnEmptyQueue)
    {
        AddJobs(tasks);
    }

    ~Parallelizer() = default;

    Parallelizer(Parallelizer &&) = delete;
    auto operator=(Parallelizer &&) -> Parallelizer & = delete;

    Parallelizer(const Parallelizer &) = delete;
    auto operator=(const Parallelizer &) -> Parallelizer & = delete;

    void AddJob(const Task &task)
    {
        m_dispatcher.Post(task);
    }

    void AddJobs(const TaskVector &tasks)
    {
        for (auto &task : tasks)
        {
            m_dispatcher.Post(task);
        }
    }

    void Run(const int concurrency)
    {
        std::vector<std::thread> threads;
        threads.reserve(concurrency);

        for (int i = 0; i < concurrency; ++i)
        {
            threads.emplace_back([this]() { m_dispatcher.Run(); });
        }

        for (auto &thread : threads)
        {
            thread.join();
        }
    }

private:
    Dispatcher m_dispatcher;
};

} // namespace aeon::Common
