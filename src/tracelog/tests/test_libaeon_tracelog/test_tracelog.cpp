// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/tracelog/tracelog.h>
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

static void TestFunc3([[maybe_unused]] float a, [[maybe_unused]] const char *str)
{
    AeonTracelogScoped();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
}

static void TestFunc2(int arg)
{
    AeonTracelogScoped();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    TestFunc3(static_cast<float>(arg), "Hello");
    TestFunc3(static_cast<float>(arg + 10), "Bye");
}

static void TestFunc1(int arg1, [[maybe_unused]] float arg2)
{
    AeonTracelogScoped();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    for (int i = 0; i < 10; ++i)
    {
        TestFunc2(arg1);
    }
}

TEST(test_tracelog, test_tracelog_basic_stack)
{
    aeon::Tracelog::Initialize();

    for (int i = 0; i < 10; ++i)
    {
        TestFunc1(1, 1.0f);
    }

    aeon::Tracelog::Write("test.trace");
}
