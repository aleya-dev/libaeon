# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    AUTO_GLOB_SOURCES
    TARGET test_libaeon_imaging
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_imaging aeon_testing
    FOLDER dep/libaeon/tests
)

set(AEON_IMAGING_UNITTEST_DATA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/data/)
configure_file(imaging_unittest_data.h.in imaging_unittest_data.h @ONLY)
