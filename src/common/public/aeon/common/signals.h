// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <functional>
#include <list>
#include <mutex>
#include <atomic>

namespace aeon::Common
{

template <class... Args>
using SignalFunc = std::function<void(Args...)>;

template <class... Args>
class SignalConnection
{
public:
    SignalConnection()
        : m_handle(0)
        , m_func()
        , m_disconnect()
    {
    }

    explicit SignalConnection(const int handle, SignalFunc<Args...> func, std::function<void()> disconnect)
        : m_handle(handle)
        , m_func(func)
        , m_disconnect(disconnect)
    {
    }

    SignalConnection(SignalConnection<Args...> &&other) noexcept
        : m_handle(other.m_handle)
        , m_func(std::move(other.m_func))
        , m_disconnect(std::move(other.m_disconnect))
    {
        other.m_handle = 0;
    }

    ~SignalConnection() = default;

    auto operator=(SignalConnection<Args...> &&other) noexcept -> SignalConnection &
    {
        m_handle = other.m_handle;
        m_func = std::move(other.m_func);
        m_disconnect = std::move(other.m_disconnect);

        other.m_handle = 0;
        return *this;
    }

    SignalConnection(const SignalConnection<Args...> &) = default;
    auto operator=(const SignalConnection<Args...> &) -> SignalConnection & = default;

    [[nodiscard]] auto Handle() const
    {
        return m_handle;
    }

    void Emit(Args... args)
    {
        m_func(args...);
    }

    void Disconnect()
    {
        if (m_disconnect)
            m_disconnect();

        m_handle = 0;
    }

    explicit operator bool() const
    {
        return m_handle != 0;
    }

private:
    int m_handle;
    SignalFunc<Args...> m_func;
    std::function<void()> m_disconnect;
};

template <class... Args>
class [[nodiscard]] ScopedSignalConnection
{
public:
    ScopedSignalConnection()
        : m_signal()
    {
    }

    ScopedSignalConnection(SignalConnection<Args...> &&signal)
        : m_signal(std::move(signal))
    {
    }

    ~ScopedSignalConnection()
    {
        if (m_signal)
            m_signal.Disconnect();
    }

    ScopedSignalConnection(ScopedSignalConnection<Args...> &&other)
        : m_signal(std::move(other.m_signal))
    {
    }

    ScopedSignalConnection &operator=(ScopedSignalConnection &&other)
    {
        m_signal = std::move(other.m_signal);
        return *this;
    }

    ScopedSignalConnection(const ScopedSignalConnection<Args...> &other) = delete;
    ScopedSignalConnection &operator=(const ScopedSignalConnection &other) = delete;

    [[nodiscard]] auto Handle() const
    {
        return m_signal.Handle();
    }

    void Emit(Args... args)
    {
        m_signal.Emit(args...);
    }

    void Disconnect() const
    {
        m_signal.Disconnect();
    }

private:
    SignalConnection<Args...> m_signal;
};

template <class... Args>
class Signal
{
public:
    Signal()
        : m_lastHandle(0)
        , m_connections()
    {
    }

    ~Signal() = default;

    ScopedSignalConnection<Args...> Connect(SignalFunc<Args...> f)
    {
        auto handle = ++m_lastHandle;
        auto disconnectFunc = [this, handle]() { Disconnect(handle); };
        auto connection = SignalConnection<Args...>(handle, f, disconnectFunc);
        m_connections.push_back(connection);
        return connection;
    }

    void Disconnect(const ScopedSignalConnection<Args...> &c)
    {
        Disconnect(c.Handle());
    }

    void Disconnect(const int c)
    {
        m_connections.remove_if([c](const SignalConnection<Args...> &other) { return other.Handle() == c; });
    }

    void operator()(Args... args)
    {
        for (auto &c : m_connections)
        {
            c.Emit(args...);
        }
    }

private:
    int m_lastHandle = 0;
    std::list<SignalConnection<Args...>> m_connections;
};

template <class... Args>
class SignalMt
{
    using MutexType = std::mutex;
    using HandleType = std::atomic<int>;
    using ListType = std::list<SignalConnection<Args...>>;

public:
    SignalMt() = default;
    ~SignalMt()
    {
        /* \note This does not solve the 'destruction' while signal is executing problem.
         * Reasoning:
         * Thread a is the owner (he creates and destroys) and thread b executes the signal multiple times. Then
         * while the signal is being destroyed from thread a, thread b tries to execute the signal. Thread a will
         * acquire the mutex and execute the signal destructor. When the signal is destroyed it will release the
         * mutex and allow thread b to execute the signal that does not exist. Which will result in havoc.
         */
        std::lock_guard<MutexType> guard(m_lock);
        m_connections.clear();
    }

    ScopedSignalConnection<Args...> Connect(SignalFunc<Args...> f)
    {
        int handle = ++m_lastHandle;
        auto disconnectFunc = [this, handle]() { Disconnect(handle); };
        auto connection = SignalConnection<Args...>(++m_lastHandle, f, disconnectFunc);
        {
            std::lock_guard<MutexType> guard(m_lock);
            m_connections.push_back(connection);
        }

        return connection;
    }

    void Disconnect(const ScopedSignalConnection<Args...> &c)
    {
        disconnect(c.get_handle());
    }

    void Disconnect(const int handle)
    {
        std::lock_guard<MutexType> guard(m_lock);
        m_connections.remove_if([&handle](const SignalConnection<Args...> &other)
                               { return other.Handle() == handle; });
    }

    void operator()(Args... args)
    {
        std::lock_guard<MutexType> guard(m_lock);
        for (auto &c : m_connections)
            c.Emit(args...);
    }

private:
    HandleType m_lastHandle{0};
    ListType m_connections;
    MutexType m_lock;
};

} // namespace aeon::Common
