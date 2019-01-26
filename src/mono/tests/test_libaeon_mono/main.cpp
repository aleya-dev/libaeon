// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include "mono_jit_fixture.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new mono_jit_fixture());
    return RUN_ALL_TESTS();
}
