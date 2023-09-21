// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/singleton.h>
#include <gtest/gtest.h>

class TestSingleton : public aeon::Common::Singleton<TestSingleton>
{
};

TEST(test_singleton, test_singleton_create)
{
    EXPECT_NE(nullptr, &TestSingleton::GetSingleton());
}

TEST(test_singleton, test_singleton_is_same)
{
    const auto singletonPtr = &TestSingleton::GetSingleton();
    const auto singletonPtr2 = &TestSingleton::GetSingleton();
    const auto singletonPtr3 = &TestSingleton::GetSingleton();

    EXPECT_EQ(singletonPtr, singletonPtr2);
    EXPECT_EQ(singletonPtr, singletonPtr3);
}

TEST(test_singleton, test_singleton_ptr_is_same)
{
    const auto singletonPtr = &TestSingleton::GetSingleton();
    const auto singletonPtr2 = TestSingleton::GetSingletonPtr();
    const auto singletonPtr3 = TestSingleton::GetSingletonPtr();

    EXPECT_EQ(singletonPtr, singletonPtr2);
    EXPECT_EQ(singletonPtr, singletonPtr3);
}
