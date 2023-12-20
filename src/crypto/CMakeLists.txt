# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
    "public/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_crypto STATIC
    ${SOURCES}
)

set_target_properties(aeon_crypto PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_crypto
    PUBLIC
        public
)

target_link_libraries(aeon_crypto
    aeon_common
    aeon_streams
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
