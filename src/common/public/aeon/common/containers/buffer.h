// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/allocators/ansi_allocator.h>
#include <aeon/common/allocators/concept.h>
#include <cstddef>
#include <algorithm>

namespace aeon::Common::Containers
{

template <typename T>
struct BufferDefaultPair
{
    T *Data;
    std::size_t Capacity;
};

/*!
 * A simple raw buffer of data. This buffer does not automatically grow; like std::vector.
 * Neither does it call any constructors or destructors on the type. Depending on the given
 * allocator, the heap data is not even initialized with any value by default. Another thing
 * to consider is that there are no checks being done on the allocated memory. If for some
 * reason the allocation fails, you will not receive an exception. It's more likely the
 * program will crash. This class should only be used when performance is preferred over
 * programmer safety.
 *
 * Typically this should only be used for raw data; for example std::byte or char.
 */
template <typename T, Allocators::Allocator AllocatorT = Allocators::AnsiAllocator<T>,
          typename StoragePairT = BufferDefaultPair<T>>
class Buffer
{
public:
    using value_type = T;
    using allocator = AllocatorT;
    using storage_pair = StoragePairT;

    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

    Buffer()
    {
        // Do not default initialize the pair; as it may contain other values
        // or state that we shouldn't interfere with.
        m_pair.Data = nullptr;
        m_pair.Capacity = 0;
    }

    explicit Buffer(const size_type size)
        : Buffer{}
    {
        Resize(size);
    }

    Buffer(const Buffer<T, AllocatorT> &other)
    {
        // Do not default initialize the pair; as it may contain other values
        // or state that we shouldn't interfere with.
        m_pair.Data = nullptr;
        m_pair.Capacity = 0;

        Resize(other.Capacity());
        std::copy_n(other.Data(), other.Capacity(), m_pair.Data);
    }

    auto operator=(const Buffer<T, AllocatorT> &other) -> Buffer<T, AllocatorT> &
    {
        Reset();

        Resize(other.Capacity());
        std::copy_n(other.Data(), other.Capacity(), m_pair.Data);

        return *this;
    }

    Buffer(Buffer<T, AllocatorT> &&other) noexcept
    {
        m_pair.Data = other.m_pair.Data;
        m_pair.Capacity = other.m_pair.Capacity;

        other.m_pair.Data = nullptr;
        other.m_pair.Capacity = 0;
    }

    auto operator=(Buffer<T, AllocatorT> &&other) noexcept -> Buffer<T, AllocatorT> &
    {
        Reset();

        m_pair.Data = other.m_pair.Data;
        m_pair.Capacity = other.m_pair.Capacity;
        other.m_pair.Data = nullptr;
        other.m_pair.Capacity = 0;

        return *this;
    }

    ~Buffer()
    {
        Reset();
    }

    [[nodiscard]] auto begin() noexcept -> pointer
    {
        return m_pair.Data;
    }

    [[nodiscard]] auto end() noexcept -> pointer
    {
        return m_pair.Data + m_pair.Capacity;
    }

    [[nodiscard]] auto begin() const noexcept -> pointer
    {
        return m_pair.Data;
    }

    [[nodiscard]] auto end() const noexcept -> pointer
    {
        return m_pair.Data + m_pair.Capacity;
    }

    [[nodiscard]] auto cbegin() const noexcept -> pointer
    {
        return m_pair.data;
    }

    [[nodiscard]] auto cend() const noexcept -> pointer
    {
        return m_pair.Data + m_pair.Capacity;
    }

    [[nodiscard]] auto Capacity() const noexcept -> size_type
    {
        return m_pair.Capacity;
    }

    [[nodiscard]] auto Data() noexcept -> pointer
    {
        return m_pair.Data;
    }

    [[nodiscard]] auto Data() const noexcept -> const_pointer
    {
        return m_pair.Data;
    }

    void Resize(const size_type size)
    {
        m_pair.Data = allocator::reallocate(m_pair.Data, size);
        m_pair.Capacity = size;
    }

    void Reset()
    {
        // Note that data is not checked for nullptr here. It is up
        // to the allocator to handle this case.
        allocator::deallocate(m_pair.Data, m_pair.Capacity);
        m_pair.Data = nullptr;
        m_pair.Capacity = 0;
    }

    [[nodiscard]] auto Empty() const noexcept
    {
        return m_pair.Capacity == 0u;
    }

    [[nodiscard]] auto At(const size_type pos) noexcept -> reference
    {
        return m_pair.Data[pos];
    }

    [[nodiscard]] auto At(const size_type pos) const noexcept -> const_reference
    {
        return m_pair.Data[pos];
    }

    auto operator[](const size_type pos) noexcept -> reference
    {
        return At(pos);
    }

    auto operator[](const size_type pos) const noexcept -> const_reference
    {
        return At(pos);
    }

private:
    storage_pair m_pair;
};

} // namespace aeon::Common::containers
