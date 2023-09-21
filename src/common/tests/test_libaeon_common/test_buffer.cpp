// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/containers/buffer.h>
#include <aeon/common/platform.h>

#if (defined(AEON_PLATFORM_OS_WINDOWS))
#include <aeon/common/allocators/windows_heap_allocator.h>
#endif

#include <gtest/gtest.h>

using namespace aeon;

TEST(test_containers_buffer, test_containers_buffer_default_create)
{
    Common::Containers::Buffer<int> a;
    EXPECT_EQ(0, a.Capacity());
    EXPECT_EQ(nullptr, a.Data());

    Common::Containers::Buffer<float> b;
    EXPECT_EQ(0, b.Capacity());
    EXPECT_EQ(nullptr, b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_create_with_size)
{
    Common::Containers::Buffer<int> a{100};
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    Common::Containers::Buffer<float> b{100};
    EXPECT_EQ(100, b.Capacity());
    EXPECT_NE(nullptr, b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_resize_from_empty)
{
    Common::Containers::Buffer<int> a;
    EXPECT_EQ(0, a.Capacity());
    EXPECT_EQ(nullptr, a.Data());

    a.Resize(100);
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    Common::Containers::Buffer<float> b;
    EXPECT_EQ(0, b.Capacity());
    EXPECT_EQ(nullptr, b.Data());

    b.Resize(100);
    EXPECT_EQ(100, b.Capacity());
    EXPECT_NE(nullptr, b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_reset)
{
    Common::Containers::Buffer<int> a{100};
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    a.Reset();
    EXPECT_EQ(0, a.Capacity());
    EXPECT_EQ(nullptr, a.Data());

    Common::Containers::Buffer<float> b{100};
    EXPECT_EQ(100, b.Capacity());
    EXPECT_NE(nullptr, b.Data());

    b.Reset();
    EXPECT_EQ(0, b.Capacity());
    EXPECT_EQ(nullptr, b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_move_ctor)
{
    Common::Containers::Buffer<int> a(100);
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    const auto data_ptr = a.Data();

    Common::Containers::Buffer b{std::move(a)};
    EXPECT_EQ(100, b.Capacity());
    EXPECT_EQ(data_ptr, b.Data());

    EXPECT_EQ(0, a.Capacity());
    EXPECT_EQ(nullptr, a.Data());
}

TEST(test_containers_buffer, test_containers_buffer_move_assignment)
{
    Common::Containers::Buffer<int> a(100);
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    const auto data_ptr = a.Data();

    Common::Containers::Buffer<int> b(50);
    EXPECT_EQ(50, b.Capacity());
    EXPECT_NE(nullptr, b.Data());

    const auto b_data_ptr = b.Data();

    b = std::move(a);
    EXPECT_EQ(100, b.Capacity());
    EXPECT_EQ(data_ptr, b.Data());
    EXPECT_NE(b_data_ptr, b.Data());

    EXPECT_EQ(0, a.Capacity());
    EXPECT_EQ(nullptr, a.Data());
}

TEST(test_containers_buffer, test_containers_buffer_copy_ctor)
{
    Common::Containers::Buffer<int> a(100);
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    Common::Containers::Buffer b{a};
    EXPECT_EQ(100, b.Capacity());

    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(a.Data(), b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_copy_assignment)
{
    Common::Containers::Buffer<int> a(100);
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    Common::Containers::Buffer<int> b;
    b = a;

    EXPECT_EQ(100, b.Capacity());

    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(a.Data(), b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_iterators)
{
    Common::Containers::Buffer<int> a(10);

    int value = 0;
    for (auto &val : a)
        val = ++value;

    EXPECT_EQ(10, value);

    value = 0;
    for (auto &val : a)
        EXPECT_EQ(val, ++value);
}

TEST(test_containers_buffer, test_containers_data_is_copied)
{
    Common::Containers::Buffer<int> a(10);

    int value = 0;
    for (auto &val : a)
        val = ++value;

    EXPECT_EQ(10, value);

    Common::Containers::Buffer b(a);

    value = 0;
    for (auto &val : b)
        EXPECT_EQ(val, ++value);
}

#if (defined(AEON_PLATFORM_OS_WINDOWS))
TEST(test_containers_buffer, test_containers_buffer_default_create_windows_heap_allocator)
{
    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> a;
    EXPECT_EQ(0, a.Capacity());
    EXPECT_EQ(nullptr, a.Data());

    Common::Containers::Buffer<float, Common::Allocators::WindowsHeapAllocator<float>> b;
    EXPECT_EQ(0, b.Capacity());
    EXPECT_EQ(nullptr, b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_create_with_size_windows_heap_allocator)
{
    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> a{100};
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    Common::Containers::Buffer<float, Common::Allocators::WindowsHeapAllocator<float>> b{100};
    EXPECT_EQ(100, b.Capacity());
    EXPECT_NE(nullptr, b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_resize_from_empty_windows_heap_allocator)
{
    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> a;
    EXPECT_EQ(0, a.Capacity());
    EXPECT_EQ(nullptr, a.Data());

    a.Resize(100);
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    Common::Containers::Buffer<float, Common::Allocators::WindowsHeapAllocator<float>> b;
    EXPECT_EQ(0, b.Capacity());
    EXPECT_EQ(nullptr, b.Data());

    b.Resize(100);
    EXPECT_EQ(100, b.Capacity());
    EXPECT_NE(nullptr, b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_reset_windows_heap_allocator)
{
    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> a{100};
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    a.Reset();
    EXPECT_EQ(0, a.Capacity());
    EXPECT_EQ(nullptr, a.Data());

    Common::Containers::Buffer<float, Common::Allocators::WindowsHeapAllocator<float>> b{100};
    EXPECT_EQ(100, b.Capacity());
    EXPECT_NE(nullptr, b.Data());

    b.Reset();
    EXPECT_EQ(0, b.Capacity());
    EXPECT_EQ(nullptr, b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_move_ctor_windows_heap_allocator)
{
    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> a(100);
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    const auto data_ptr = a.Data();

    Common::Containers::Buffer b{std::move(a)};
    EXPECT_EQ(100, b.Capacity());
    EXPECT_EQ(data_ptr, b.Data());

    EXPECT_EQ(0, a.Capacity());
    EXPECT_EQ(nullptr, a.Data());
}

TEST(test_containers_buffer, test_containers_buffer_move_assignment_windows_heap_allocator)
{
    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> a(100);
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    const auto data_ptr = a.Data();

    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> b(50);
    EXPECT_EQ(50, b.Capacity());
    EXPECT_NE(nullptr, b.Data());

    const auto b_data_ptr = b.Data();

    b = std::move(a);
    EXPECT_EQ(100, b.Capacity());
    EXPECT_EQ(data_ptr, b.Data());
    EXPECT_NE(b_data_ptr, b.Data());

    EXPECT_EQ(0, a.Capacity());
    EXPECT_EQ(nullptr, a.Data());
}

TEST(test_containers_buffer, test_containers_buffer_copy_ctor_windows_heap_allocator)
{
    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> a(100);
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    Common::Containers::Buffer b{a};
    EXPECT_EQ(100, b.Capacity());

    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(a.Data(), b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_copy_assignment_windows_heap_allocator)
{
    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> a(100);
    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(nullptr, a.Data());

    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> b;
    b = a;

    EXPECT_EQ(100, b.Capacity());

    EXPECT_EQ(100, a.Capacity());
    EXPECT_NE(a.Data(), b.Data());
}

TEST(test_containers_buffer, test_containers_buffer_iterators_windows_heap_allocator)
{
    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> a(10);

    int value = 0;
    for (auto &val : a)
        val = ++value;

    EXPECT_EQ(10, value);

    value = 0;
    for (auto &val : a)
        EXPECT_EQ(val, ++value);
}

TEST(test_containers_buffer, test_containers_data_is_copied_windows_heap_allocator)
{
    Common::Containers::Buffer<int, Common::Allocators::WindowsHeapAllocator<int>> a(10);

    int value = 0;
    for (auto &val : a)
        val = ++value;

    EXPECT_EQ(10, value);

    Common::Containers::Buffer b(a);

    value = 0;
    for (auto &val : b)
        EXPECT_EQ(val, ++value);
}
#endif
