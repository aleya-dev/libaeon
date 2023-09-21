// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <type_traits>
#include <limits>
#include <vector>
#include <forward_list>

namespace aeon::Common::Containers
{

namespace Internal
{

struct GeneralTreeLeafData
{
    static constexpr auto Npos = std::numeric_limits<std::size_t>::max();

    std::size_t Parent = Npos;
    std::size_t Left = Npos;
    std::size_t Right = Npos;
};

} // namespace internal

template <typename T>
class GeneralTreeLeaf;

template <typename T>
class GeneralTreeIterator
{
    using TreeLeafDataType = Internal::GeneralTreeLeafData;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = GeneralTreeLeaf<T>;
    using difference_type = std::size_t;
    using pointer = value_type *;
    using reference = value_type &;

    explicit GeneralTreeIterator(std::vector<TreeLeafDataType> *leafs, std::vector<T> *values,
                                 const std::size_t currentIndex) noexcept;

    auto operator++() -> GeneralTreeIterator<T> &;

    auto operator++(int) -> GeneralTreeIterator<T> &;

    [[nodiscard]] auto operator==(const GeneralTreeIterator<T> &other) const -> bool;

    [[nodiscard]] auto operator!=(const GeneralTreeIterator<T> &other) const -> bool;

    auto operator*() -> value_type;

    auto operator*() const -> value_type;

private:
    std::vector<TreeLeafDataType> *m_leafs;
    std::vector<T> *m_values;
    std::size_t m_currentIndex;
};

template <typename T>
class GeneralTreeLeaf final
{
    template <typename>
    friend class GeneralTree;

    template <typename>
    friend class GeneralTreeIterator;

    using TreeLeafDataType = Internal::GeneralTreeLeafData;

public:
    using value_type = T;
    using pointer = value_type *;
    using reference = value_type &;
    using iterator_type = GeneralTreeIterator<value_type>;

    GeneralTreeLeaf(const GeneralTreeLeaf<value_type> &) = delete;
    auto operator=(const GeneralTreeLeaf<value_type> &) -> GeneralTreeLeaf<value_type> & = delete;

    GeneralTreeLeaf(GeneralTreeLeaf<value_type> &&) noexcept = delete;
    auto operator=(GeneralTreeLeaf<value_type> &&) noexcept -> GeneralTreeLeaf<value_type> & = delete;

    void Reserve(const std::size_t size) const;

    auto EmplaceChild(const value_type &value) -> GeneralTreeLeaf<value_type>;

    auto EmplaceChild(value_type &&value) -> GeneralTreeLeaf<value_type>;

    void AddChild(const value_type &value);

    void AddChild(value_type &&value);

    [[nodiscard]] auto Parent() -> GeneralTreeLeaf<value_type>;

    [[nodiscard]] auto Parent() const -> GeneralTreeLeaf<value_type>;

    [[nodiscard]] auto IsRoot() const noexcept -> bool;

    [[nodiscard]] auto At(const std::size_t i) -> GeneralTreeLeaf<value_type>;

    [[nodiscard]] auto At(const std::size_t i) const -> GeneralTreeLeaf<value_type>;

    [[nodiscard]] auto ChildCount() const noexcept -> std::size_t;

    [[nodiscard]] auto begin() noexcept -> iterator_type;

    [[nodiscard]] auto end() noexcept -> iterator_type;

    [[nodiscard]] auto begin() const noexcept -> iterator_type;

    [[nodiscard]] auto end() const noexcept -> iterator_type;

    [[nodiscard]] auto cbegin() const noexcept -> iterator_type;

    [[nodiscard]] auto cend() const noexcept -> iterator_type;

    [[nodiscard]] auto operator*() noexcept -> reference;

    [[nodiscard]] auto operator*() const noexcept -> reference;

private:
    explicit GeneralTreeLeaf(std::vector<TreeLeafDataType> *leafs, std::vector<value_type> *values,
                             const std::size_t index) noexcept;

    void UpdateIndices(const std::size_t newIndex) const noexcept;

    std::vector<TreeLeafDataType> *m_leafs;
    std::vector<value_type> *m_values;
    std::size_t m_index;
};

/*!
 * A general tree implemented as left-child right-sibling (LCRS).
 */
template <typename T>
class GeneralTree final
{
    using TreeLeafDataType = Internal::GeneralTreeLeafData;

public:
    using value_type = T;
    using TreeLeafType = GeneralTreeLeaf<value_type>;

    explicit GeneralTree(value_type &&rootValue);

    explicit GeneralTree(const value_type &rootValue);

    ~GeneralTree() = default;

    GeneralTree(const GeneralTree &) = default;
    auto operator=(const GeneralTree &) -> GeneralTree & = default;

    GeneralTree(GeneralTree &&) noexcept = default;
    auto operator=(GeneralTree &&) noexcept -> GeneralTree & = default;

    void Reserve(const std::size_t size);

    void Clear() noexcept;

    [[nodiscard]] auto Root() -> TreeLeafType;

private:
    std::vector<TreeLeafDataType> m_leafs;
    std::vector<value_type> m_values;
};

} // namespace aeon::Common::containers

#include <aeon/common/containers/impl/general_tree_impl.h>
