// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/tribool.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_tribool, test_tribool_default_false)
{
    EXPECT_FALSE(Common::Tribool{});
}

TEST(test_tribool, test_tribool_boolean_constructor)
{
    EXPECT_TRUE(Common::Tribool{true});
    EXPECT_FALSE(Common::Tribool{false});
}

TEST(test_tribool, test_tribool_indeterminate_constructor)
{
    EXPECT_FALSE(Common::Tribool{Common::Indeterminate});

    Common::Tribool val{Common::Indeterminate};

    EXPECT_FALSE(val);
    EXPECT_TRUE(Common::Indeterminate(val));
    EXPECT_TRUE(val.IsIndeterminate());
}

TEST(test_tribool, test_tribool_and)
{
    Common::Tribool val1{true};
    Common::Tribool val2{true};
    Common::Tribool val3{false};
    Common::Tribool val4{Common::Indeterminate};
    Common::Tribool val5{Common::Indeterminate};

    EXPECT_TRUE(val1 && val2);
    EXPECT_FALSE(val1 && val3);
    EXPECT_FALSE(val1 && val2 && val3);
    EXPECT_FALSE(val1 && val4);
    EXPECT_FALSE(val1 && val2 && val4);
    EXPECT_FALSE(val4 && val5);

    EXPECT_FALSE(val1 && val2 && Common::Indeterminate);
    EXPECT_FALSE(Common::Indeterminate && val1 && val2);
    EXPECT_FALSE(val1 && Common::Indeterminate);
    EXPECT_FALSE(Common::Indeterminate && val1);
}

TEST(test_tribool, test_tribool_or)
{
    Common::Tribool val1{true};
    Common::Tribool val2{true};
    Common::Tribool val3{false};
    Common::Tribool val4{false};
    Common::Tribool val5{Common::Indeterminate};
    Common::Tribool val6{Common::Indeterminate};

    EXPECT_TRUE(val1 || val2);
    EXPECT_TRUE(val1 || val3);
    EXPECT_TRUE(val2 || val3);
    EXPECT_TRUE(val1 || val6);
    EXPECT_FALSE(val3 || val4);
    EXPECT_FALSE(val4 || val5);
    EXPECT_FALSE(val5 || val6);
    EXPECT_FALSE(val3 || val6);

    EXPECT_TRUE(val1 || val3 || val5);
    EXPECT_TRUE(val2 || val5 || val6);
    EXPECT_FALSE(val3 || val5 || val6);

    EXPECT_TRUE(val1 || val2 || Common::Indeterminate);
    EXPECT_TRUE(val1 || val3 || Common::Indeterminate);
    EXPECT_TRUE(val2 || val3 || Common::Indeterminate);
    EXPECT_TRUE(val1 || val6 || Common::Indeterminate);
}

TEST(test_tribool, test_tribool_equals_tribool)
{
    Common::Tribool val1{true};
    Common::Tribool val2{true};
    Common::Tribool val3{false};
    Common::Tribool val4{false};
    Common::Tribool val5{Common::Indeterminate};
    Common::Tribool val6{Common::Indeterminate};

    EXPECT_TRUE(val1 == val2);
    EXPECT_FALSE(val1 == val3);
    EXPECT_FALSE(val1 == val5);

    EXPECT_TRUE(val3 == val4);
    EXPECT_FALSE(val3 == val1);
    EXPECT_FALSE(val3 == val5);

    // Indeterminate does never equal another indeterminate
    EXPECT_FALSE(val5 == val6);
    EXPECT_FALSE(val5 == val1);
    EXPECT_FALSE(val5 == val3);
}

TEST(test_tribool, test_tribool_equals_bool)
{
    Common::Tribool val1{true};
    Common::Tribool val2{false};
    Common::Tribool val3{Common::Indeterminate};

    EXPECT_TRUE(val1 == true);
    EXPECT_FALSE(val1 == false);
    EXPECT_TRUE(true == val1);
    EXPECT_FALSE(false == val1);

    EXPECT_TRUE(val2 == false);
    EXPECT_FALSE(val2 == true);
    EXPECT_TRUE(false == val2);
    EXPECT_FALSE(true == val2);

    // Indeterminate does never equal true or false
    EXPECT_FALSE(val3 == false);
    EXPECT_FALSE(val3 == true);
    EXPECT_FALSE(false == val3);
    EXPECT_FALSE(true == val3);
}

TEST(test_tribool, test_tribool_equals_indeterminate)
{
    Common::Tribool val1{true};
    Common::Tribool val2{false};
    Common::Tribool val3{Common::Indeterminate};

    EXPECT_FALSE(val1 == Common::Indeterminate);
    EXPECT_FALSE(Common::Indeterminate == val1);

    EXPECT_FALSE(val2 == Common::Indeterminate);
    EXPECT_FALSE(Common::Indeterminate == val2);

    // Indeterminate does never equal another indeterminate
    EXPECT_FALSE(val3 == Common::Indeterminate);
    EXPECT_FALSE(Common::Indeterminate == val3);
}

TEST(test_tribool, test_tribool_not_equals_tribool)
{
    Common::Tribool val1{true};
    Common::Tribool val2{true};
    Common::Tribool val3{false};
    Common::Tribool val4{false};
    Common::Tribool val5{Common::Indeterminate};
    Common::Tribool val6{Common::Indeterminate};

    EXPECT_FALSE(val1 != val2);
    EXPECT_TRUE(val1 != val3);
    EXPECT_TRUE(val1 != val5);

    EXPECT_FALSE(val3 != val4);
    EXPECT_TRUE(val3 != val1);
    EXPECT_TRUE(val3 != val5);

    // Indeterminate does never equal another indeterminate
    EXPECT_TRUE(val5 != val6);
    EXPECT_TRUE(val5 != val1);
    EXPECT_TRUE(val5 != val3);
}

TEST(test_tribool, test_tribool_not_equals_bool)
{
    Common::Tribool val1{true};
    Common::Tribool val2{false};
    Common::Tribool val3{Common::Indeterminate};

    EXPECT_FALSE(val1 != true);
    EXPECT_FALSE(true != val1);
    EXPECT_TRUE(val1 != false);
    EXPECT_TRUE(false != val1);

    EXPECT_FALSE(val2 != false);
    EXPECT_FALSE(false != val2);
    EXPECT_TRUE(val2 != true);
    EXPECT_TRUE(true != val2);

    EXPECT_TRUE(val3 != false);
    EXPECT_TRUE(false != val3);
    EXPECT_TRUE(val3 != true);
    EXPECT_TRUE(true != val3);
}

TEST(test_tribool, test_tribool_not_equals_indeterminate)
{
    Common::Tribool val1{true};
    Common::Tribool val2{false};
    Common::Tribool val3{Common::Indeterminate};

    EXPECT_TRUE(val1 != Common::Indeterminate);
    EXPECT_TRUE(Common::Indeterminate != val1);

    EXPECT_TRUE(val2 != Common::Indeterminate);
    EXPECT_TRUE(Common::Indeterminate != val2);

    // Indeterminate does never equal another indeterminate
    EXPECT_TRUE(val3 != Common::Indeterminate);
    EXPECT_TRUE(Common::Indeterminate != val3);
}
