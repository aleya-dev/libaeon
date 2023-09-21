// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <functional>
#include <algorithm>
#include <vector>

namespace aeon::Common
{

/*!
 * Subject of a observer pattern (listener class).
 */
template <typename T>
class ListenerSubject final
{
public:
    ListenerSubject() = default;
    ~ListenerSubject() = default;

    ListenerSubject(ListenerSubject<T> &&) = default;
    auto operator=(ListenerSubject<T> &&) -> ListenerSubject<T> & = default;

    ListenerSubject(const ListenerSubject<T> &) = default;
    auto operator=(const ListenerSubject<T> &) -> ListenerSubject<T> & = default;

    /*!
     * Attach a listener/observer to this subject.
     *
     * This does not take ownership of this pointer, so it's up to
     * the caller to keep this pointer alive, and delete it appropriately.
     */
    void Attach(T &listener)
    {
        m_listeners.push_back(&listener);
    }

    /*!
     * Remove a listener/observer from this subject. If this pointer was not previously attached, nothing happens.
     *
     * This will not delete the object, but merely detach it.
     */
    void Detach(T &listener)
    {
        m_listeners.erase(std::remove(std::begin(m_listeners), std::end(m_listeners), &listener), std::end(m_listeners));
    }

    /*!
     * Detach all attached listeners.
     *
     * This will not delete the objects, but merely detach them.
     */
    void DetachAll()
    {
        m_listeners.clear();
    }

    /*!
     * Invoke a method in every attached listener
     */
    template <typename FuncT, class... ArgsT>
    void InvokeEach(FuncT &&func, ArgsT &&...args)
    {
        for (const auto &listener : m_listeners)
            std::invoke(func, listener, std::forward<ArgsT>(args)...);
    }

    /*!
     * Invoke a method in every attached listener
     */
    template <typename FuncT, class... ArgsT>
    void InvokeEach(FuncT &&func, ArgsT &&...args) const
    {
        for (const auto &listener : m_listeners)
            std::invoke(func, listener, std::forward<ArgsT>(args)...);
    }

    /*!
     * Access all attached listeners
     */
    [[nodiscard]] const auto &Listeners() const noexcept
    {
        return m_listeners;
    }

private:
    std::vector<T *> m_listeners;
};

} // namespace aeon::Common
