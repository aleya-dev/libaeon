// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/literals.h>
#include <vector>
#include <memory>
#include <array>
#include <iterator>
#include <algorithm>

namespace aeon::Common::Container
{

template <class ContainerT>
class BackEmplaceIterator
{
public:
    using ContainerType = ContainerT;

    explicit BackEmplaceIterator(ContainerType &x)
        : m_container{&x}
    {
    }

    template <typename T>
    BackEmplaceIterator<ContainerType> &operator=(const T &args)
    {
        m_container->emplace_back(args);
        return *this;
    }

    BackEmplaceIterator &operator*()
    {
        return *this;
    }

    BackEmplaceIterator &operator++()
    {
        return *this;
    }

    BackEmplaceIterator &operator++(int)
    {
        return *this;
    }

private:
    ContainerType *m_container;
};

template <typename T>
[[nodiscard]] inline auto BackEmplacer(T &container)
{
    return BackEmplaceIterator{container};
}

template <typename U, typename T, typename PredT>
[[nodiscard]] inline auto Transform(const std::vector<T> &vec, PredT pred) -> std::vector<U>
{
    std::vector<U> transVec;
    transVec.reserve(std::size(vec));

    std::transform(std::begin(vec), std::end(vec), std::back_inserter(transVec), pred);
    return transVec;
}

template <typename U, typename T>
[[nodiscard]] inline auto AutoTransform(const std::vector<T> &vec) -> std::vector<U>
{
    std::vector<U> transVec;
    transVec.reserve(std::size(vec));

    std::transform(std::begin(vec), std::end(vec), BackEmplacer(transVec),
                   [](const auto &v) { return static_cast<U>(v); });
    return transVec;
}

template <typename ContainerT, typename UnaryPredicateT>
void EraseIf(ContainerT &items, const UnaryPredicateT &predicate)
{
    for (auto itr = std::begin(items); itr != std::end(items);)
    {
        if (predicate(*itr))
            itr = items.erase(itr);
        else
            ++itr;
    }
}

template <typename T, std::size_t N>
[[nodiscard]] inline constexpr auto MakeArray(T &&value) noexcept
{
    std::array<T, N> arr;
    arr.fill(std::forward<T>(value));
    return arr;
}

template <typename... T>
[[nodiscard]] inline constexpr auto MakeArray2(T &&...values)
    -> std::array<typename std::decay<typename std::common_type<T...>::type>::type, sizeof...(T)>
{
    return std::array<typename std::decay<typename std::common_type<T...>::type>::type, sizeof...(T)>{
        std::forward<T>(values)...};
}

template <typename InputItrT, typename UnaryPredicateT>
[[nodiscard]] inline auto CountUntil(InputItrT first, InputItrT last, UnaryPredicateT p) noexcept
{
    auto count = 0_size_t;

    for (; first != last; ++first, ++count)
    {
        if (p(*first))
            return count;
    }

    return count;
}

template <typename MapTypeT, typename ValueTypeT>
[[nodiscard]] inline auto FindInMapByValue(const MapTypeT &map, const ValueTypeT &value) noexcept
{
    return std::find_if(map.begin(), map.end(), [&value](const auto &pair) { return pair.second == value; });
}

/*!
 * Execute a predicate for every two adjacent items in a collection. Similar to adjacent_find, but does not
 * actually search for something. If the predicate returns false, the loop is aborted.
 * The signature of the predicate should be equivalent to bool(const type1 &left, const type2 &right);
 */
template <typename ForwardItrT, typename PredT>
inline void AdjacentExecute(ForwardItrT first, ForwardItrT last, PredT p) noexcept
{
    if (first == last)
        return;

    auto next = first;
    ++next;

    for (; next != last; ++next, ++first)
    {
        if (!p(*first, *next))
            return;
    }
}

template <typename IteratorT, typename ValueT>
inline auto Contains(IteratorT first, IteratorT last, const ValueT &value) noexcept -> bool
{
    if (first == last)
        return false;

    for (; first != last; ++first)
    {
        if (*first == value)
            return true;
    }

    return false;
}

} // namespace aeon::Common::container
