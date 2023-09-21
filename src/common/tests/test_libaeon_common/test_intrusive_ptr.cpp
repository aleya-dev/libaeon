// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/intrusive_ptr.h>
#include <gtest/gtest.h>

using namespace aeon;

struct TestObj
{
    int RefCount = 0;

    void IntrusivePtrAddRef()
    {
        RefCount++;
    }

    void IntrusivePtrRelease()
    {
        RefCount--;

        if (RefCount <= 0)
            delete this;
    }
};

TEST(test_intrusive_ptr, ref_count)
{
    auto var = Common::make_intrusive_ptr<TestObj>();
    EXPECT_EQ(var->RefCount, 1);

    auto var2 = var;
    EXPECT_EQ(var->RefCount, 2);
    EXPECT_EQ(var2->RefCount, 2);

    auto var3 = var2;
    EXPECT_EQ(var->RefCount, 3);
    EXPECT_EQ(var2->RefCount, 3);
    EXPECT_EQ(var3->RefCount, 3);

    var2.Reset();
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var->RefCount, 2);
    EXPECT_EQ(var3->RefCount, 2);

    var3 = nullptr;
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var3, nullptr);
    EXPECT_EQ(var->RefCount, 1);
}

struct AddReleaseCallCheck
{
    int IntrusivePtrAddRefCalls = 0;
    int IntrusivePtrReleaseCalls = 0;

    void IntrusivePtrAddRef()
    {
        IntrusivePtrAddRefCalls++;
    }

    void IntrusivePtrRelease()
    {
        IntrusivePtrReleaseCalls++;
    }
};

TEST(test_intrusive_ptr, add_release_calls)
{
    AddReleaseCallCheck check;

    {
        Common::IntrusivePtr<AddReleaseCallCheck> obj{&check};

        EXPECT_EQ(check.IntrusivePtrAddRefCalls, 1);
        EXPECT_EQ(check.IntrusivePtrReleaseCalls, 0);

        auto obj2 = obj;
        EXPECT_EQ(check.IntrusivePtrAddRefCalls, 2);
        EXPECT_EQ(check.IntrusivePtrReleaseCalls, 0);

        obj2.Reset();
        EXPECT_EQ(check.IntrusivePtrAddRefCalls, 2);
        EXPECT_EQ(check.IntrusivePtrReleaseCalls, 1);
    }

    EXPECT_EQ(check.IntrusivePtrAddRefCalls, 2);
    EXPECT_EQ(check.IntrusivePtrReleaseCalls, 2);
}

struct IntrusiveRefCounterTest : public Common::IntrusiveRefCounter<int, IntrusiveRefCounterTest>
{
};

TEST(test_intrusive_ptr, IntrusiveRefCounter)
{
    auto var = Common::make_intrusive_ptr<IntrusiveRefCounterTest>();
    EXPECT_EQ(var->IntrusivePtrRefCount(), 1);

    auto var2 = var;
    EXPECT_EQ(var->IntrusivePtrRefCount(), 2);
    EXPECT_EQ(var2->IntrusivePtrRefCount(), 2);

    auto var3 = var2;
    EXPECT_EQ(var->IntrusivePtrRefCount(), 3);
    EXPECT_EQ(var2->IntrusivePtrRefCount(), 3);
    EXPECT_EQ(var3->IntrusivePtrRefCount(), 3);

    var2.Reset();
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var->IntrusivePtrRefCount(), 2);
    EXPECT_EQ(var3->IntrusivePtrRefCount(), 2);

    var3 = nullptr;
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var3, nullptr);
    EXPECT_EQ(var->IntrusivePtrRefCount(), 1);
}

struct AtomicIntrusiveRefCounterTest
    : public Common::IntrusiveRefCounter<std::atomic<int>, AtomicIntrusiveRefCounterTest>
{
};

TEST(test_intrusive_ptr, atomic_intrusive_ref_counter)
{
    auto var = Common::make_intrusive_ptr<AtomicIntrusiveRefCounterTest>();
    EXPECT_EQ(var->IntrusivePtrRefCount(), 1);

    auto var2 = var;
    EXPECT_EQ(var->IntrusivePtrRefCount(), 2);
    EXPECT_EQ(var2->IntrusivePtrRefCount(), 2);

    auto var3 = var2;
    EXPECT_EQ(var->IntrusivePtrRefCount(), 3);
    EXPECT_EQ(var2->IntrusivePtrRefCount(), 3);
    EXPECT_EQ(var3->IntrusivePtrRefCount(), 3);

    var2.Reset();
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var->IntrusivePtrRefCount(), 2);
    EXPECT_EQ(var3->IntrusivePtrRefCount(), 2);

    var3 = nullptr;
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var3, nullptr);
    EXPECT_EQ(var->IntrusivePtrRefCount(), 1);
}
