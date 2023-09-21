// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/preprocessor.h>
#include <aeon/common/assert.h>
#include <functional>
#include <exception>

namespace aeon::Common
{

namespace Internal
{

template <typename FunctionTypeT>
class ScopeGuardBase
{
public:
    void Dismiss() noexcept
    {
        m_dismissed = true;
    }

    template <typename T>
    static void Execute(T &func) noexcept
    {
        try
        {
            func();
        }
        catch (...)
        {
            AeonAssertFail("A scope guard callback should not throw.");
            std::terminate();
        }
    }

    explicit ScopeGuardBase(FunctionTypeT &&func) noexcept
        : m_dismissed{false}
        , m_function{std::forward<FunctionTypeT>(func)}
    {
    }

    ScopeGuardBase(ScopeGuardBase &&other) noexcept
        : m_function{std::move(other.m_function)}
    {
        m_dismissed = other.m_dismissed;
        other.m_dismissed = true;
    }

    ScopeGuardBase(const ScopeGuardBase<FunctionTypeT> &) noexcept = delete;
    auto operator=(const ScopeGuardBase<FunctionTypeT> &) noexcept -> ScopeGuardBase<FunctionTypeT> & = delete;

    ~ScopeGuardBase() noexcept
    {
        if (m_dismissed)
            return;

        execute(m_function);
    }

private:
    bool m_dismissed;
    FunctionTypeT m_function;
};

template <typename FunctionTypeT, bool ExecuteOnException>
class ScopeGuardImpl
{
public:
    explicit ScopeGuardImpl(const FunctionTypeT &fn)
        : m_function(fn)
    {
    }

    explicit ScopeGuardImpl(FunctionTypeT &&fn)
        : m_function(std::move(fn))
    {
    }

    ScopeGuardImpl(const ScopeGuardImpl &) = delete;
    auto operator=(const ScopeGuardImpl &) noexcept -> ScopeGuardImpl & = delete;

    ScopeGuardImpl(ScopeGuardImpl &&) = default;
    auto operator=(ScopeGuardImpl &&) noexcept -> ScopeGuardImpl & = default;

    ~ScopeGuardImpl() noexcept(ExecuteOnException)
    {
        if (ExecuteOnException == (m_exceptionCount < std::uncaught_exceptions()))
        {
            if (ExecuteOnException)
            {
                ScopeGuardBase<FunctionTypeT>::Execute(m_function);
            }
            else
            {
                m_function();
            }
        }
    }

private:
    FunctionTypeT m_function;
    int m_exceptionCount{std::uncaught_exceptions()};
};

class ScopeGuardOnFail
{
};

template <typename FunctionTypeT>
ScopeGuardImpl<typename std::decay<FunctionTypeT>::type, true> operator+(ScopeGuardOnFail, FunctionTypeT &&func)
{
    return ScopeGuardImpl<typename std::decay<FunctionTypeT>::type, true>(std::forward<FunctionTypeT>(func));
}

} // namespace detail

} // namespace aeon::Common

#define AeonScopeFail                                                                                                \
    auto AeonAnonymousVariable(__AeonScopeFail) = ::aeon::Common::Internal::ScopeGuardOnFail() + [&]() noexcept
