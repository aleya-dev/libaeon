// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <initializer_list>
#include <stdexcept>

namespace aeon::Common::Containers
{

template <typename key_type_t, typename value_type_t>
class UnorderedFlatmap final
{
public:
    using key_type = key_type_t;
    using value_type = value_type_t;
    using pair_type = std::pair<key_type, value_type>;
    using map_type = std::vector<pair_type>;
    using iterator = typename map_type::iterator;

    UnorderedFlatmap() = default;

    UnorderedFlatmap(std::initializer_list<pair_type> init)
        : m_map{}
    {
        for (auto &&val : init)
        {
            Insert(std::move(val));
        }
    }

    ~UnorderedFlatmap() = default;

    UnorderedFlatmap(const UnorderedFlatmap &) = default;
    auto operator=(const UnorderedFlatmap &) -> UnorderedFlatmap & = default;
    UnorderedFlatmap(UnorderedFlatmap &&) noexcept = default;
    auto operator=(UnorderedFlatmap &&) noexcept -> UnorderedFlatmap & = default;

    auto Insert(key_type key, value_type value) -> iterator
    {
        return Insert({key, value});
    }

    auto Emplace(key_type &&key, value_type &&value) -> iterator
    {
        return Emplace({std::move(key), std::move(value)});
    }

    auto Insert(pair_type pair) -> iterator
    {
        auto itr = Find(pair.first);

        if (itr == std::end(m_map))
            return m_map.insert(std::end(m_map), std::move(pair));

        itr->second = std::move(pair.second);
        return itr;
    }

    auto Emplace(pair_type &&pair) -> iterator
    {
        auto itr = Find(pair.first);

        if (itr == std::end(m_map))
            return m_map.insert(std::end(m_map), std::move(pair));

        itr->second = std::move(pair.second);
        return itr;
    }

    void PushBack(const key_type &key, const value_type &value)
    {
        PushBack({key, value});
    }

    void PushBack(const pair_type &pair)
    {
        m_map.push_back(std::move(pair));
    }

    [[nodiscard]] auto &At(const key_type &key)
    {
        auto itr = Find(key);
        if (itr == std::end(m_map))
            throw std::out_of_range{"aeon UnorderedFlatmap key out of range."};

        return itr->second;
    }

    [[nodiscard]] const auto &At(const key_type &key) const
    {
        auto itr = Find(key);
        if (itr == std::end(m_map))
            throw std::out_of_range{"aeon UnorderedFlatmap key out of range."};

        return itr->second;
    }

    auto &operator[](const key_type &key)
    {
        auto itr = Find(key);

        if (itr == std::end(m_map))
            itr = Insert(key, value_type{});

        return itr->second;
    }

    auto &operator[](key_type &&key)
    {
        auto itr = Find(key);

        if (itr == std::end(m_map))
            itr = Emplace(std::move(key), value_type{});

        return itr->second;
    }

    [[nodiscard]] auto Contains(const key_type &key) const noexcept -> bool
    {
        return std::find_if(std::begin(m_map), std::end(m_map), [key](const auto &s) { return s.first == key; }) !=
               std::end(m_map);
    }

    [[nodiscard]] auto Find(const key_type &key) noexcept
    {
        return std::find_if(std::begin(m_map), std::end(m_map), [key](const auto &s) { return s.first == key; });
    }

    [[nodiscard]] auto Find(const key_type &key) const noexcept
    {
        return std::find_if(std::begin(m_map), std::end(m_map), [key](const auto &s) { return s.first == key; });
    }

    [[nodiscard]] auto begin() noexcept
    {
        return std::begin(m_map);
    }

    [[nodiscard]] auto end() noexcept
    {
        return std::end(m_map);
    }

    [[nodiscard]] auto begin() const noexcept
    {
        return std::begin(m_map);
    }

    [[nodiscard]] auto end() const noexcept
    {
        return std::end(m_map);
    }

    auto Erase(const key_type &key)
    {
        auto itr = Find(key);

        if (itr != std::end(m_map))
            return Erase(itr);

        return itr;
    }

    void EraseIf(std::function<bool(const pair_type &)> predicate)
    {
        for (auto obj = std::begin(m_map); obj != std::end(m_map);)
        {
            if (predicate(*obj))
            {
                obj = m_map.erase(obj);
            }
            else
            {
                ++obj;
            }
        }
    }

    auto Erase(typename map_type::iterator itr)
    {
        return m_map.erase(itr);
    }

    [[nodiscard]] auto Empty() const
    {
        return std::empty(m_map);
    }

    void Clear()
    {
        m_map.clear();
    }

    [[nodiscard]] auto Size() const noexcept
    {
        return std::size(m_map);
    }

    void Reserve(const std::size_t size)
    {
        m_map.reserve(size);
    }

    auto operator==(const UnorderedFlatmap<key_type, value_type> &other) const noexcept -> bool
    {
        if (Size() != other.Size())
            return false;

        for (const auto &[key, val] : m_map)
        {
            const auto result = other.Find(key);

            if (result == std::end(other))
                return false;

            if (result->second != val)
                return false;
        }

        return true;
    }

    auto operator!=(const UnorderedFlatmap<key_type, value_type> &other) const noexcept -> bool
    {
        return !(*this == other);
    }

private:
    map_type m_map;
};

} // namespace aeon::Common::containers
