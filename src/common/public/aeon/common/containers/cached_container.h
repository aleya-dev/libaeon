// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/container.h>
#include <map>
#include <memory>

namespace aeon::Common::Containers
{

/*!
 * Generic templated base class for cachable objects, like assets. Objects are cached by key.
 * If an object is still referenced anywhere, 'get' will return the existing object,
 * otherwise it will return a nullptr.
 *
 * This class does not take ownership of the cached objects, as it merely stores weak pointers.
 */
template <typename KeyT, typename ValueT>
class CachedContainer
{
public:
    using CachedObjects = std::map<KeyT, std::weak_ptr<ValueT>>;

    CachedContainer() = default;
    ~CachedContainer() = default;

    CachedContainer(CachedContainer<KeyT, ValueT> &&other) noexcept
        : m_objects(other.m_objects)
    {
    }

    CachedContainer<KeyT, ValueT> &operator=(CachedContainer<KeyT, ValueT> &&other) noexcept
    {
        m_objects = std::move(other.m_objects);
        return *this;
    }

    CachedContainer(const CachedContainer<KeyT, ValueT> &) noexcept = delete;
    auto operator=(const CachedContainer<KeyT, ValueT> &) noexcept -> CachedContainer<KeyT, ValueT> & = delete;

    /*!
     * Get a cached object by name. This method will return a shared pointer to the requested object
     * or a nullptr. If the object was found to be expired, a garbage collection will be triggered to
     * clean up expired weak pointers.
     */
    [[nodiscard]] auto Get(const KeyT &name) -> std::shared_ptr<ValueT>
    {
        const auto result = m_objects.find(name);

        if (result == m_objects.end())
            return nullptr;

        auto object = result->second;

        if (object.expired())
        {
            GarbageCollect();
            return nullptr;
        }

        return object.lock();
    }

    /*!
     * Register a newly created object to be cached. If an object with the same name is found, which is not yet expired,
     * an object_cache_name_exception is thrown. This method will take a weak pointer of the given shared pointer to
     * store internally.
     */
    bool Add(const KeyT &name, const std::shared_ptr<ValueT> &obj)
    {
        const auto result = m_objects.find(name);

        if (result != m_objects.end())
        {
            if (!result->second.expired())
                return false;

            GarbageCollect();
        }

        m_objects[name] = obj;

        return true;
    }

    /*!
     * Garbage collect all expired cached objects.
     */
    void GarbageCollect()
    {
        Container::EraseIf(m_objects, [](const auto &obj) { return obj.second.expired(); });
    }

private:
    CachedObjects m_objects;
};

} // namespace aeon::Common
