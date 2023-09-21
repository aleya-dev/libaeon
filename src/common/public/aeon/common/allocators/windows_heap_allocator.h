// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/platform.h>
#include <aeon/common/flags.h>
#include <cstdlib>

#if (!defined(AEON_PLATFORM_OS_WINDOWS))
static_assert(false, "This header can only be used on windows.");
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace aeon::Common::Allocators
{

enum class WindowsHeapAllocatorFlags : std::uint64_t
{
    NoSerialize = HEAP_NO_SERIALIZE,
    ZeroMemory = HEAP_ZERO_MEMORY,
    GenerateExceptions = HEAP_GENERATE_EXCEPTIONS,
    Align16 = HEAP_CREATE_ALIGN_16
};

AeonDeclareFlagOperators(WindowsHeapAllocatorFlags)

/*!
 * Simple base class for the heap allocator that does not contain the type, to avoid creating
 * a different heap for every type.
 */
template <Flags<WindowsHeapAllocatorFlags> Flags = WindowsHeapAllocatorFlags::NoSerialize,
          std::size_t InitialHeapSize = 0, std::size_t MaximumHeapSize = 0>
struct WindowsHeapAllocatorBase
{
protected:
    static auto GetHeap() noexcept -> HANDLE
    {
        static auto heap = HeapCreate(static_cast<DWORD>(Flags), InitialHeapSize, MaximumHeapSize);
        return heap;
    }
};

/*!
 * Wrapper around the windows HeapAlloc, HeapReAlloc and HeapFree functions.
 * By default this will create a thread unsafe heap. This means that an allocation
 * can only be allocated and deleted from the same thread unless manual synchronisation
 * is done. In a well designed implementation this should be the case anyway, as data
 * typically isn't owned by multiple threads at the same time; only read.
 *
 * Note that this allocator will only allocate memory. It will NOT
 * call any constructors. These should only be used for raw data,
 * not for arrays of objects.
 */
template <typename T, Flags<WindowsHeapAllocatorFlags> Flags = WindowsHeapAllocatorFlags::NoSerialize,
          std::size_t InitialHeapSize = 0, std::size_t MaximumHeapSize = 0>
struct WindowsHeapAllocator : WindowsHeapAllocatorBase<Flags, InitialHeapSize, MaximumHeapSize>
{
    static auto allocate(const std::size_t n) noexcept
    {
        return static_cast<T *>(
            HeapAlloc(WindowsHeapAllocatorBase<Flags, InitialHeapSize, MaximumHeapSize>::GetHeap(),
                      static_cast<DWORD>(Flags), n * sizeof(T)));
    }

    static auto allocate_at_least(const std::size_t n) noexcept
    {
        return allocate(n);
    }

    static auto reallocate(T *ptr, const std::size_t n) noexcept
    {
        if (!ptr)
            return allocate(n);

        return static_cast<T *>(
            HeapReAlloc(WindowsHeapAllocatorBase<Flags, InitialHeapSize, MaximumHeapSize>::GetHeap(),
                        static_cast<DWORD>(Flags), ptr, n * sizeof(T)));
    }

    static void deallocate(T *ptr, [[maybe_unused]] const std::size_t n) noexcept
    {
        HeapFree(WindowsHeapAllocatorBase<Flags, InitialHeapSize, MaximumHeapSize>::GetHeap(),
                 static_cast<DWORD>(Flags), ptr);
    }
};

} // namespace aeon::Common::allocators
