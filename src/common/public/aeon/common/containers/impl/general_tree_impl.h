// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <stdexcept>

namespace aeon::Common::Containers
{

template <typename T>
inline GeneralTreeIterator<T>::GeneralTreeIterator(std::vector<TreeLeafDataType> *leafs, std::vector<T> *values,
                                                   const std::size_t currentIndex) noexcept
    : m_leafs{leafs}
    , m_values{values}
    , m_currentIndex{currentIndex}
{
}

template <typename T>
inline auto GeneralTreeIterator<T>::operator++() -> GeneralTreeIterator<T> &
{
    const auto &leaf = (*m_leafs)[m_currentIndex];
    m_currentIndex = leaf.Right;
    return *this;
}

template <typename T>
inline auto GeneralTreeIterator<T>::operator++(int) -> GeneralTreeIterator<T> &
{
    auto &val = *this;
    ++(*this);
    return val;
}

template <typename T>
inline auto GeneralTreeIterator<T>::operator==(const GeneralTreeIterator<T> &other) const -> bool
{
    return m_leafs == other.m_leafs && m_values == other.m_values && m_currentIndex == other.m_currentIndex;
}

template <typename T>
inline auto GeneralTreeIterator<T>::operator!=(const GeneralTreeIterator<T> &other) const -> bool
{
    return !(*this == other);
}

template <typename T>
inline auto GeneralTreeIterator<T>::operator*() -> value_type
{
    return value_type{m_leafs, m_values, m_currentIndex};
}

template <typename T>
inline auto GeneralTreeIterator<T>::operator*() const -> value_type
{
    return value_type{m_leafs, m_values, m_currentIndex};
}

template <typename T>
inline void GeneralTreeLeaf<T>::Reserve(const std::size_t size) const
{
    m_leafs->reserve(size);
    m_values->reserve(size);
}

template <typename T>
inline auto GeneralTreeLeaf<T>::EmplaceChild(const value_type &value) -> GeneralTreeLeaf<value_type>
{
    const auto newIndex = std::size(*m_leafs);
    m_leafs->push_back(TreeLeafDataType{m_index, TreeLeafDataType::Npos, TreeLeafDataType::Npos});
    m_values->emplace_back(value);
    UpdateIndices(newIndex);
    return GeneralTreeLeaf{m_leafs, m_values, newIndex};
}

template <typename T>
inline auto GeneralTreeLeaf<T>::EmplaceChild(value_type &&value) -> GeneralTreeLeaf<value_type>
{
    const auto newIndex = std::size(*m_leafs);
    m_leafs->push_back(TreeLeafDataType{m_index, TreeLeafDataType::Npos, TreeLeafDataType::Npos});
    m_values->emplace_back(std::move(value));
    UpdateIndices(newIndex);
    return GeneralTreeLeaf{m_leafs, m_values, newIndex};
}

template <typename T>
inline void GeneralTreeLeaf<T>::AddChild(const value_type &value)
{
    EmplaceChild(value);
}

template <typename T>
inline void GeneralTreeLeaf<T>::AddChild(value_type &&value)
{
    EmplaceChild(std::move(value));
}

template <typename T>
inline auto GeneralTreeLeaf<T>::Parent() -> GeneralTreeLeaf<value_type>
{
    const auto currentLeaf = &m_leafs->at(m_index);

    if (currentLeaf->Parent == TreeLeafDataType::Npos)
        throw std::out_of_range{"Leaf has no parent."};

    return GeneralTreeLeaf{m_leafs, m_values, currentLeaf->Parent};
}

template <typename T>
inline auto GeneralTreeLeaf<T>::Parent() const -> GeneralTreeLeaf<value_type>
{
    const auto currentLeaf = &m_leafs->at(m_index);

    if (currentLeaf->Parent == TreeLeafDataType::Npos)
        throw std::out_of_range{"Leaf has no parent."};

    return GeneralTreeLeaf{m_leafs, m_values, currentLeaf->Parent};
}

template <typename T>
inline auto GeneralTreeLeaf<T>::IsRoot() const noexcept -> bool
{
    const auto currentLeaf = &m_leafs->at(m_index);
    return currentLeaf->Parent == TreeLeafDataType::Npos;
}

template <typename T>
inline auto GeneralTreeLeaf<T>::At(const std::size_t i) -> GeneralTreeLeaf<value_type>
{
    const auto currentLeaf = &m_leafs->at(m_index);

    auto current = currentLeaf->Left;

    if (current == TreeLeafDataType::Npos)
        throw std::out_of_range{"Child index out of range"};

    for (auto count = 0u; count < i; ++count)
    {
        const auto &leaf = (*m_leafs)[current];
        current = leaf.Right;

        if (current == TreeLeafDataType::Npos)
            throw std::out_of_range{"Child index out of range"};
    }

    return GeneralTreeLeaf{m_leafs, m_values, current};
}

template <typename T>
inline auto GeneralTreeLeaf<T>::At(const std::size_t i) const -> GeneralTreeLeaf<value_type>
{
    const auto currentLeaf = &m_leafs->at(m_index);

    auto current = currentLeaf->Left;

    if (current == TreeLeafDataType::Npos)
        throw std::out_of_range{"Child index out of range"};

    for (auto count = 0u; count < i; ++count)
    {
        const auto &leaf = (*m_leafs)[current];
        current = leaf.Right;

        if (current == TreeLeafDataType::Npos)
            throw std::out_of_range{"Child index out of range"};
    }

    return GeneralTreeLeaf{m_leafs, m_values, current};
}

template <typename T>
inline auto GeneralTreeLeaf<T>::ChildCount() const noexcept -> std::size_t
{
    const auto currentLeaf = &m_leafs->at(m_index);

    auto current = currentLeaf->Left;

    std::size_t count = 0;

    while (current != TreeLeafDataType::Npos)
    {
        const auto &leaf = (*m_leafs)[current];
        current = leaf.Right;
        ++count;
    }

    return count;
}

template <typename T>
inline auto GeneralTreeLeaf<T>::begin() noexcept -> iterator_type
{
    const auto parentLeaf = &m_leafs->at(m_index);
    return iterator_type{m_leafs, m_values, parentLeaf->Left};
}

template <typename T>
inline auto GeneralTreeLeaf<T>::end() noexcept -> iterator_type
{
    return iterator_type{m_leafs, m_values, TreeLeafDataType::Npos};
}

template <typename T>
inline auto GeneralTreeLeaf<T>::begin() const noexcept -> iterator_type
{
    return begin();
}

template <typename T>
inline auto GeneralTreeLeaf<T>::end() const noexcept -> iterator_type
{
    return end();
}

template <typename T>
inline auto GeneralTreeLeaf<T>::cbegin() const noexcept -> iterator_type
{
    return begin();
}

template <typename T>
inline auto GeneralTreeLeaf<T>::cend() const noexcept -> iterator_type
{
    return end();
}

template <typename T>
inline auto GeneralTreeLeaf<T>::operator*() noexcept -> reference
{
    return (*m_values)[m_index];
}

template <typename T>
inline auto GeneralTreeLeaf<T>::operator*() const noexcept -> reference
{
    return (*m_values)[m_index];
}

template <typename T>
inline GeneralTreeLeaf<T>::GeneralTreeLeaf(std::vector<TreeLeafDataType> *leafs, std::vector<value_type> *values,
                                           const std::size_t index) noexcept
    : m_leafs{leafs}
    , m_values{values}
    , m_index{index}
{
}

template <typename T>
inline void GeneralTreeLeaf<T>::UpdateIndices(const std::size_t newIndex) const noexcept
{
    auto leaf = &m_leafs->at(m_index);

    if (leaf->Left == TreeLeafDataType::Npos)
    {
        leaf->Left = newIndex;
    }
    else
    {
        leaf = &m_leafs->at(leaf->Left);

        while (leaf->Right != TreeLeafDataType::Npos)
            leaf = &m_leafs->at(leaf->Right);

        leaf->Right = newIndex;
    }
}

template <typename T>
inline GeneralTree<T>::GeneralTree(value_type &&rootValue)
    : m_leafs{}
    , m_values{}
{
    m_leafs.push_back(
        TreeLeafDataType{TreeLeafDataType::Npos, TreeLeafDataType::Npos, TreeLeafDataType::Npos});
    m_values.emplace_back(std::move(rootValue));
}

template <typename T>
inline GeneralTree<T>::GeneralTree(const value_type &rootValue)
    : m_leafs{}
    , m_values{}
{
    m_leafs.push_back(
        TreeLeafDataType{TreeLeafDataType::Npos, TreeLeafDataType::Npos, TreeLeafDataType::Npos});
    m_values.emplace_back(rootValue);
}

template <typename T>
inline void GeneralTree<T>::Reserve(const std::size_t size)
{
    m_leafs.reserve(size);
    m_values.reserve(size);
}

template <typename T>
inline void GeneralTree<T>::Clear() noexcept
{
    m_leafs.clear();
    m_values.clear();
}

template <typename T>
inline auto GeneralTree<T>::Root() -> TreeLeafType
{
    return TreeLeafType{&m_leafs, &m_values, 0};
}

} // namespace aeon::Common::containers
