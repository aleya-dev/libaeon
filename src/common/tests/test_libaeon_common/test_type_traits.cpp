// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/type_traits.h>
#include <gtest/gtest.h>

TEST(test_type_traits, test_preserve_const)
{
    EXPECT_TRUE((std::is_same_v<aeon::Common::TypeTraits::PreserveConstT<int, float>, float>));
    EXPECT_TRUE((std::is_same_v<aeon::Common::TypeTraits::PreserveConstT<const int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveConstT<int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveConstT<const int, float>, float>));

    EXPECT_TRUE((std::is_same_v<aeon::Common::TypeTraits::PreserveConstT<volatile int, float>, float>));
    EXPECT_TRUE((std::is_same_v<aeon::Common::TypeTraits::PreserveConstT<volatile const int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveConstT<volatile int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveConstT<volatile const int, float>, float>));
}

TEST(test_type_traits, test_preserve_volatile)
{
    EXPECT_TRUE((std::is_same_v<aeon::Common::TypeTraits::PreserveVolatileT<int, float>, float>));
    EXPECT_TRUE((std::is_same_v<aeon::Common::TypeTraits::PreserveVolatileT<volatile int, float>, volatile float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveVolatileT<int, float>, volatile float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveVolatileT<volatile int, float>, float>));

    EXPECT_TRUE((std::is_same_v<aeon::Common::TypeTraits::PreserveVolatileT<const int, float>, float>));
    EXPECT_TRUE(
        (std::is_same_v<aeon::Common::TypeTraits::PreserveVolatileT<const volatile int, float>, volatile float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveVolatileT<const int, float>, volatile float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveVolatileT<const volatile int, float>, float>));
}

TEST(test_type_traits, test_preserve_cv)
{
    EXPECT_TRUE((std::is_same_v<aeon::Common::TypeTraits::PreserveCvt<int, float>, float>));
    EXPECT_TRUE((std::is_same_v<aeon::Common::TypeTraits::PreserveCvt<const int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveCvt<int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveCvt<const int, float>, float>));

    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveCvt<int, float>, volatile float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveCvt<volatile int, float>, float>));

    EXPECT_TRUE((std::is_same_v<aeon::Common::TypeTraits::PreserveCvt<volatile int, float>, volatile float>));
    EXPECT_TRUE(
        (std::is_same_v<aeon::Common::TypeTraits::PreserveCvt<volatile const int, float>, volatile const float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveCvt<volatile int, float>, volatile const float>));
    EXPECT_FALSE((std::is_same_v<aeon::Common::TypeTraits::PreserveCvt<volatile const int, float>, volatile float>));
}
