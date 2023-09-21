// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/version.h>
#include <gtest/gtest.h>

TEST(test_version, test_version_create)
{
    aeon::Common::Version v;
    EXPECT_EQ(v.Major, 0);
    EXPECT_EQ(v.Minor, 0);
    EXPECT_EQ(v.Patch, 0);
    EXPECT_EQ(v.Build, 0);
}

TEST(test_version, test_version_create_major_minor)
{
    aeon::Common::Version v{2, 3};
    EXPECT_EQ(v.Major, 2);
    EXPECT_EQ(v.Minor, 3);
    EXPECT_EQ(v.Patch, 0);
    EXPECT_EQ(v.Build, 0);
}

TEST(test_version, test_version_create_major_minor_patch)
{
    aeon::Common::Version v{2, 3, 4};
    EXPECT_EQ(v.Major, 2);
    EXPECT_EQ(v.Minor, 3);
    EXPECT_EQ(v.Patch, 4);
    EXPECT_EQ(v.Build, 0);
}

TEST(test_version, test_version_create_major_minor_patch_build)
{
    aeon::Common::Version v{2, 3, 4, 5};
    EXPECT_EQ(v.Major, 2);
    EXPECT_EQ(v.Minor, 3);
    EXPECT_EQ(v.Patch, 4);
    EXPECT_EQ(v.Build, 5);
}

TEST(test_version, test_version_equals)
{
    aeon::Common::Version v{2, 3, 4, 5};
    aeon::Common::Version v2{3, 3, 4, 5};
    aeon::Common::Version v3{2, 3, 4, 5};

    EXPECT_FALSE(v == v2);
    EXPECT_TRUE(v != v2);
    EXPECT_TRUE(v == v3);
    EXPECT_FALSE(v != v3);
}

TEST(test_version, test_version_compare)
{
    aeon::Common::Version v{2, 3, 4, 5};
    aeon::Common::Version v2{2, 3, 4, 6};
    aeon::Common::Version v3{3, 3, 4, 5};
    aeon::Common::Version v4{3, 3, 4, 5};

    EXPECT_TRUE(v < v2);
    EXPECT_FALSE(v > v2);
    EXPECT_TRUE(v < v3);
    EXPECT_FALSE(v > v3);
    EXPECT_TRUE(v2 < v3);
    EXPECT_FALSE(v2 > v3);

    EXPECT_FALSE(v3 < v4);
    EXPECT_FALSE(v3 > v4);
    EXPECT_TRUE(v3 <= v4);
    EXPECT_TRUE(v3 >= v4);
}

TEST(test_version, test_version_string)
{
    aeon::Common::Version v{2, 3, 4, 5};
    aeon::Common::Version v2{2, 3, 4, 6};
    aeon::Common::Version v3{3, 3, 4, 5};

    EXPECT_EQ("2.3.4.5", v.Str());
    EXPECT_EQ("2.3.4.6", v2.Str());
    EXPECT_EQ("3.3.4.5", v3.Str());
}

TEST(test_version, test_version_convert)
{
    aeon::Common::Version4<int> v_orig{2, 3, 4, 5};
    aeon::Common::Version4<float> v_float{v_orig};
    aeon::Common::Version4<int> v_result{v_float};

    EXPECT_TRUE(v_orig == v_result);
}

TEST(test_version, test_version_convert_partial)
{
    aeon::Common::Version2<int> v_orig{2, 3};
    aeon::Common::Version4<float> v_float{v_orig, 4};
    aeon::Common::Version4<int> v_float2{v_orig, 4, 5};

    aeon::Common::Version4<int> v_result{v_float};
    aeon::Common::Version4<int> v_result2{v_float2};

    EXPECT_TRUE(v_orig == v_result);
    EXPECT_TRUE(v_float2 == v_result2);
}