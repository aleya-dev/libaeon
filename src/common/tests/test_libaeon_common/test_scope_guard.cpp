// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/scope_guard.h>
#include <gtest/gtest.h>

TEST(test_scope_guard, test_scope_guard_fail_discard)
{
    int a = 3;
    {
        AeonScopeFail
        {
            a = 4;
        };
    }

    ASSERT_EQ(a, 3);
}

TEST(test_scope_guard, test_scope_guard_fail_exception)
{
    int a = 3;

    try
    {
        AeonScopeFail
        {
            a = 4;
        };

        throw std::runtime_error("fail.");
    }
    catch (...)
    {
    }

    ASSERT_EQ(a, 4);
}

TEST(test_scope_guard, test_scope_guard_fail_exception_multiple)
{
    int a = 3;
    bool second_called = false;
    bool third_called = false;

    try
    {
        AeonScopeFail
        {
            a = 4;
        };

        AeonScopeFail
        {
            a = 5;
            second_called = true;
        };

        AeonScopeFail
        {
            a = 6;
            third_called = true;
        };

        throw std::runtime_error("fail.");
    }
    catch (...)
    {
    }

    ASSERT_EQ(a, 4);
    ASSERT_TRUE(second_called);
    ASSERT_TRUE(third_called);
}
