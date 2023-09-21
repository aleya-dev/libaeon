// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <initializer_list>

namespace aeon::Common::Containers
{

template <typename KeyTypeT>
class UnorderedFlatset final
{
public:
    using key_type = KeyTypeT;
    using value_type = KeyTypeT;
    using set_type = std::vector<key_type>;
    using iterator = typename set_type::iterator;

    UnorderedFlatset() = default;

    UnorderedFlatset(std::initializer_list<key_type> init)
        : m_set{}
    {
        for (auto &&val : init)
        {
            insert(std::move(val));
        }
    }

    ~UnorderedFlatset() = default;

    UnorderedFlatset(const UnorderedFlatset &) = default;
    auto operator=(const UnorderedFlatset &) -> UnorderedFlatset & = default;
    UnorderedFlatset(UnorderedFlatset &&) noexcept = default;
    auto operator=(UnorderedFlatset &&) noexcept -> UnorderedFlatset & = default;

    auto Insert(key_type key) -> iterator
    {
        auto itr = Find(key);

        if (itr == std::end(m_set))
            return m_set.insert(std::end(m_set), std::move(key));

        *itr = std::move(key);
        return itr;
    }

    auto Emplace(key_type &&key) -> iterator
    {
        auto itr = Find(key);

        if (itr == std::end(m_set))
            return m_set.insert(std::end(m_set), std::move(key));

        *itr = std::move(key);
        return itr;
    }

    [[nodiscard]] auto Contains(const key_type &key) const noexcept -> bool
    {
        return std::find_if(std::begin(m_set), std::end(m_set), [key](const auto &s) { return s == key; }) !=
               std::end(m_set);
    }

    [[nodiscard]] auto Find(const key_type &key) noexcept
    {
        return std::find_if(std::begin(m_set), std::end(m_set), [key](const auto &s) { return s == key; });
    }

    [[nodiscard]] auto Find(const key_type &key) const noexcept
    {
        return std::find_if(std::begin(m_set), std::end(m_set), [key](const auto &s) { return s == key; });
    }

    [[nodiscard]] auto begin() noexcept
    {
        return std::begin(m_set);
    }

    [[nodiscard]] auto end() noexcept
    {
        return std::end(m_set);
    }

    [[nodiscard]] auto begin() const noexcept
    {
        return std::begin(m_set);
    }

    [[nodiscard]] auto end() const noexcept
    {
        return std::end(m_set);
    }

    auto Erase(const key_type &key)
    {
        auto itr = Find(key);

        if (itr != std::end(m_set))
            return Erase(itr);

        return itr;
    }

    void EraseIf(std::function<bool(const key_type &)> predicate)
    {
        for (auto obj = std::begin(m_set); obj != std::end(m_set);)
        {
            if (predicate(*obj))
            {
                obj = m_set.erase(obj);
            }
            else
            {
                ++obj;
            }
        }
    }

    auto Erase(typename set_type::iterator itr)
    {
        return m_set.erase(itr);
    }

    [[nodiscard]] auto Empty() const
    {
        return std::empty(m_set);
    }

    void Clear()
    {
        m_set.clear();
    }

    [[nodiscard]] auto Size() const noexcept
    {
        return std::size(m_set);
    }

    void Reserve(const std::size_t size)
    {
        m_set.reserve(size);
    }

    auto operator==(const UnorderedFlatset<key_type> &other) const noexcept -> bool
    {
        if (Size() != other.Size())
            return false;

        for (const auto &val : m_set)
        {
            const auto result = other.Find(val);

            if (result == std::end(other))
                return false;

            if (*result != val)
                return false;
        }

        return true;
    }

    auto operator!=(const UnorderedFlatset<key_type> &other) const noexcept -> bool
    {
        return !(*this == other);
    }

private:
    set_type m_set;
};

} // namespace aeon::Common::containers
