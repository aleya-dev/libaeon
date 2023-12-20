# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    AUTO_GLOB_SOURCES
    TARGET test_libaeon_streams
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_streams
    FOLDER dep/libaeon/tests
)
