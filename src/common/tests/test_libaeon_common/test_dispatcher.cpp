// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/dispatcher.h>
#include <gtest/gtest.h>
#include <thread>

using namespace aeon;

TEST(test_dispatcher, test_dispatcher_basic_run)
{
    Common::Dispatcher dispatcher;

    std::thread t([&]() { dispatcher.Run(); });

    bool called1 = false;
    dispatcher.Post(
        [&called1]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            called1 = true;
        });

    bool called2 = false;
    dispatcher.Post(
        [&called2]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            called2 = true;
        });

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    dispatcher.Stop();

    t.join();

    EXPECT_TRUE(called1);
    EXPECT_TRUE(called2);
}

TEST(test_dispatcher, test_dispatcher_call_void)
{
    Common::Dispatcher dispatcher;

    std::thread t([&]() { dispatcher.Run(); });

    bool called = false;
    dispatcher.Call(
        [&called]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            called = true;
        });

    EXPECT_TRUE(called);

    dispatcher.Stop();
    t.join();
}

TEST(test_dispatcher, test_dispatcher_call_int)
{
    Common::Dispatcher dispatcher;

    std::thread t([&]() { dispatcher.Run(); });

    auto called = false;
    const auto value = dispatcher.Call<int>(
        [&called]()
        {
            called = true;
            return 1337;
        });

    EXPECT_TRUE(called);
    EXPECT_EQ(1337, value);

    dispatcher.Stop();
    t.join();
}
