// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/signals.h>
#include <gtest/gtest.h>
#include <array>
#include <thread>

using namespace aeon;

TEST(test_signals, test_signals_connect)
{
    Common::Signal<> Signal;
    auto connection = Signal.Connect([]() {});
    EXPECT_GT(connection.Handle(), 0);
}

TEST(test_signals, test_signals_connection_default_zero)
{
    Common::SignalConnection<> connection;
    EXPECT_EQ(0, connection.Handle());
}

TEST(test_signals, test_signals_connect_parameters)
{
    Common::Signal<int, int> Signal;
    auto connection = Signal.Connect([](int, int) {});
    EXPECT_GT(connection.Handle(), 0);
}

TEST(test_signals, test_signals_connect_one_and_call)
{
    Common::Signal<> Signal;

    bool signal_called = false;
    auto connection = Signal.Connect([&signal_called]() { signal_called = true; });

    Signal();

    EXPECT_TRUE(signal_called);
}

TEST(test_signals, test_signals_connect_multiple_and_call)
{
    Common::Signal<> Signal;

    bool signal_called = false;
    bool signal_called2 = false;
    bool signal_called3 = false;

    auto connection1 = Signal.Connect([&signal_called]() { signal_called = true; });
    auto connection2 = Signal.Connect([&signal_called2]() { signal_called2 = true; });
    auto connection3 = Signal.Connect([&signal_called3]() { signal_called3 = true; });

    Signal();

    EXPECT_TRUE(signal_called);
    EXPECT_TRUE(signal_called2);
    EXPECT_TRUE(signal_called3);
}

TEST(test_signals, test_signals_connect_one_and_call_parameters)
{
    Common::Signal<int, int> Signal;

    bool signal_called = false;
    int value1 = 0;
    int value2 = 0;
    auto connection = Signal.Connect(
        [&signal_called, &value1, &value2](int val1, int val2)
        {
            signal_called = true;
            value1 = val1;
            value2 = val2;
        });

    Signal(42, 1337);

    EXPECT_TRUE(signal_called);
    EXPECT_EQ(42, value1);
    EXPECT_EQ(1337, value2);
}

TEST(test_signals, test_signals_connect_multiple_and_call_with_disconnect)
{
    Common::Signal<> Signal;

    bool signal_called = false;
    bool signal_called2 = false;
    bool signal_called3 = false;

    auto connection1 = Signal.Connect([&signal_called]() { signal_called = true; });
    auto connection2 = Signal.Connect([&signal_called2]() { signal_called2 = true; });
    auto connection3 = Signal.Connect([&signal_called3]() { signal_called3 = true; });

    Signal();

    EXPECT_TRUE(signal_called);
    EXPECT_TRUE(signal_called2);
    EXPECT_TRUE(signal_called3);

    signal_called = false;
    signal_called2 = false;
    signal_called3 = false;

    Signal.Disconnect(connection2);

    Signal();

    EXPECT_TRUE(signal_called);
    EXPECT_FALSE(signal_called2);
    EXPECT_TRUE(signal_called3);
}

TEST(test_signals, test_signals_connect_multiple_and_call_scoped_disconnect)
{
    Common::Signal<> Signal;

    bool signal_called = false;
    bool signal_called2 = false;
    bool signal_called3 = false;

    Common::ScopedSignalConnection<> connection1;
    Common::ScopedSignalConnection<> connection3;

    {
        connection1 = Signal.Connect([&signal_called]() { signal_called = true; });
        auto connection2 = Signal.Connect([&signal_called2]() { signal_called2 = true; });
        connection3 = Signal.Connect([&signal_called3]() { signal_called3 = true; });

        Signal();

        EXPECT_TRUE(signal_called);
        EXPECT_TRUE(signal_called2);
        EXPECT_TRUE(signal_called3);

        signal_called = false;
        signal_called2 = false;
        signal_called3 = false;
    }

    Signal();

    EXPECT_TRUE(signal_called);
    EXPECT_FALSE(signal_called2);
    EXPECT_TRUE(signal_called3);
}

TEST(test_signals, test_signals_mt_sync_execution)
{
    Common::SignalMt<> Signal;
    std::array<int, 200> destination{};

    int index = 0;
    auto connection = Signal.Connect([&index, &destination] { destination[index++]++; });

    std::vector<std::thread> threads;
    auto thread_func = [&Signal]
    {
        for (int i = 0; i < 100; ++i)
        {
            Signal();
            std::this_thread::sleep_for(std::chrono::microseconds(0));
        }
    };
    threads.emplace_back(thread_func);
    threads.emplace_back(thread_func);

    for (auto &itr : threads)
        itr.join();

    for (auto &itr : destination)
        EXPECT_EQ(itr, 1);
}
